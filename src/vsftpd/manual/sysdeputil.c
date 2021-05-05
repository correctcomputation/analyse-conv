/*
 * Part of Very Secure FTPd
 * Licence: GPL v2
 * Author: Chris Evans
 * sysdeputil.c
 *
 * Highly system dependent utilities - e.g. authentication, capabilities.
 */

#include "sysdeputil.h"
#include "str.h"
#include "sysutil.h"
#include "utility.h"
#include "secbuf.h"
#include "defs.h"
#include "tunables.h"
#include "builddefs.h"

#include "hacks.h"

/* For Linux, this adds nothing :-) */
#include "port/porting_junk.h"

#if (defined(__FreeBSD__) && __FreeBSD__ >= 3)
  #define _FILE_OFFSET_BITS 64
  #define _LARGEFILE_SOURCE 1
  #define _LARGEFILE64_SOURCE 1
#endif

#ifdef __linux__
  #include <stdio.h>
  #include <sys/utsname.h>
#endif

/* For INT_MAX */
#include <limits.h>

/* For fd passing */
#include <sys/types.h>
#include <sys/socket.h>
/* For FreeBSD */
#include <sys/param.h>
#include <sys/uio.h>

#include <sys/prctl.h>
#include <signal.h>

/* Configuration.. here are the possibilities */
#undef VSF_SYSDEP_HAVE_CAPABILITIES
#undef VSF_SYSDEP_HAVE_SETKEEPCAPS
#undef VSF_SYSDEP_HAVE_SETPDEATHSIG
#undef VSF_SYSDEP_HAVE_LINUX_SENDFILE
#undef VSF_SYSDEP_HAVE_FREEBSD_SENDFILE
#undef VSF_SYSDEP_HAVE_HPUX_SENDFILE
#undef VSF_SYSDEP_HAVE_AIX_SENDFILE
#undef VSF_SYSDEP_HAVE_SETPROCTITLE
#undef VSF_SYSDEP_TRY_LINUX_SETPROCTITLE_HACK
#undef VSF_SYSDEP_HAVE_HPUX_SETPROCTITLE
#undef VSF_SYSDEP_HAVE_MAP_ANON
#undef VSF_SYSDEP_NEED_OLD_FD_PASSING
#undef VSF_SYSDEP_HAVE_LINUX_CLONE
#ifdef VSF_BUILD_PAM
  #define VSF_SYSDEP_HAVE_PAM
#endif
#define VSF_SYSDEP_HAVE_SHADOW
#define VSF_SYSDEP_HAVE_USERSHELL
#undef VSF_SYSDEP_HAVE_LIBCAP
#define VSF_SYSDEP_HAVE_UTMPX

#define __USE_GNU
#include <utmpx.h>

/* BEGIN config */
#if defined(__linux__) && !defined(__s390__)
  #include <errno.h>
  #include <syscall.h>
  #define VSF_SYSDEP_HAVE_LINUX_CLONE
  #include <sched.h>
  #ifndef CLONE_NEWPID
    #define CLONE_NEWPID 0x20000000
  #endif
  #ifndef CLONE_NEWIPC
    #define CLONE_NEWIPC 0x08000000
  #endif
  #ifndef CLONE_NEWNET
    #define CLONE_NEWNET 0x40000000
  #endif
  #include <linux/unistd.h>
  #include <errno.h>
  #include <syscall.h>
  #if defined(__alpha__)
    #define __NR_getpid  __NR_getxpid
  #endif
#endif

#if defined(__linux__) && !defined(__ia64__) && !defined(__s390__)
  #define VSF_SYSDEP_TRY_LINUX_SETPROCTITLE_HACK
  #include <linux/version.h>
  #if defined(LINUX_VERSION_CODE) && defined(KERNEL_VERSION)
    #if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,2,0))
      #define VSF_SYSDEP_HAVE_CAPABILITIES
      #define VSF_SYSDEP_HAVE_LINUX_SENDFILE
      #ifdef PR_SET_KEEPCAPS
        #define VSF_SYSDEP_HAVE_SETKEEPCAPS
      #endif
      #ifdef PR_SET_PDEATHSIG
        #define VSF_SYSDEP_HAVE_SETPDEATHSIG
      #endif
    #endif
  #endif
#endif

#if (defined(__FreeBSD__) && __FreeBSD__ >= 3)
  #define VSF_SYSDEP_HAVE_FREEBSD_SENDFILE
  #define VSF_SYSDEP_HAVE_SETPROCTITLE
#endif

#if defined(__FreeBSD_kernel__)
  #undef VSF_SYSDEP_HAVE_LIBCAP
#endif

#if defined(__NetBSD__)
  #include <stdlib.h>
  #define VSF_SYSDEP_HAVE_SETPROCTITLE
  #include <sys/param.h>
  #if __NetBSD_Version__ >= 106070000
    #define WTMPX_FILE _PATH_WTMPX
  #else
    #undef VSF_SYSDEP_HAVE_UTMPX
  #endif
#endif

#ifdef __hpux
  #include <sys/socket.h>
  #ifdef SF_DISCONNECT
    #define VSF_SYSDEP_HAVE_HPUX_SENDFILE
  #endif
  #include <sys/param.h>
  #include <sys/pstat.h>
  #ifdef PSTAT_SETCMD
    #define VSF_SYSDEP_HAVE_HPUX_SETPROCTITLE
  #endif
  #undef VSF_SYSDEP_HAVE_UTMPX
#endif

#include <unistd.h>
#include <sys/mman.h>
#ifdef MAP_ANON
  #define VSF_SYSDEP_HAVE_MAP_ANON
#endif

#ifdef __sgi
  #undef VSF_SYSDEP_HAVE_USERSHELL
  #undef VSF_SYSDEP_HAVE_LIBCAP
#endif

#ifdef _AIX
  #undef VSF_SYSDEP_HAVE_USERSHELL
  #undef VSF_SYSDEP_HAVE_LIBCAP
  #undef VSF_SYSDEP_HAVE_UTMPX
  #undef VSF_SYSDEP_HAVE_PAM
  #undef VSF_SYSDEP_HAVE_SHADOW
  #undef VSF_SYSDEP_HAVE_SETPROCTITLE
  #define VSF_SYSDEP_HAVE_AIX_SENDFILE
  #define VSF_SYSDEP_TRY_LINUX_SETPROCTITLE_HACK
  #define VSF_SYSDEP_HAVE_MAP_ANON
#endif

#ifdef __osf__
  #undef VSF_SYSDEP_HAVE_USERSHELL
#endif

#if (defined(__sgi) || defined(__hpux) || defined(__osf__))
  #define VSF_SYSDEP_NEED_OLD_FD_PASSING
#endif

#ifdef __sun
  #define VSF_SYSDEP_HAVE_SOLARIS_SENDFILE
#endif
/* END config */

/* PAM support - we include our own dummy version if the system lacks this */
#include <security/pam_appl.h>

/* No PAM? Try getspnam() with a getpwnam() fallback */
#ifndef VSF_SYSDEP_HAVE_PAM
/* This may hit our own "dummy" include and undef VSF_SYSDEP_HAVE_SHADOW */
#include <shadow.h>
#include <pwd.h>
#include <unistd.h>
#include <crypt.h>
#endif

/* Prefer libcap based capabilities over raw syscall capabilities */
#include <sys/capability.h>

#if defined(VSF_SYSDEP_HAVE_CAPABILITIES) && !defined(VSF_SYSDEP_HAVE_LIBCAP)
#include <linux/unistd.h>
#include <linux/capability.h>
#include <errno.h>
#include <syscall.h>
int capset(cap_user_header_t header, const cap_user_data_t data)
{
  return syscall(__NR_capset, header, data);
}
/* Gross HACK to avoid warnings - linux headers overlap glibc headers */
#undef __NFDBITS
#undef __FDMASK
#endif /* VSF_SYSDEP_HAVE_CAPABILITIES */

#if defined(VSF_SYSDEP_HAVE_LINUX_SENDFILE) || \
    defined(VSF_SYSDEP_HAVE_SOLARIS_SENDFILE)
#include <sys/sendfile.h>
#elif defined(VSF_SYSDEP_HAVE_FREEBSD_SENDFILE)
#include <sys/types.h>
#include <sys/socket.h>
#elif defined(VSF_SYSDEP_HAVE_HPUX_SENDFILE)
#include <sys/socket.h>
#else /* VSF_SYSDEP_HAVE_LINUX_SENDFILE */
#include <unistd.h>
#endif /* VSF_SYSDEP_HAVE_LINUX_SENDFILE */

#ifdef VSF_SYSDEP_HAVE_SETPROCTITLE
#include <sys/types.h>
#include <unistd.h>
#endif

#pragma CHECKED_SCOPE on

#ifdef VSF_SYSDEP_TRY_LINUX_SETPROCTITLE_HACK
extern char** environ : itype(_Nt_array_ptr<_Nt_array_ptr<char>>);
static unsigned int s_proctitle_space = 0;
static int s_proctitle_inited = 0;
static _Nt_array_ptr<char> s_p_proctitle : count(s_proctitle_space) = 0;
#endif

#ifndef VSF_SYSDEP_HAVE_MAP_ANON
#pragma CHECKED_SCOPE off
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#pragma CHECKED_SCOPE on
static int s_zero_fd = -1;
#endif

/* File private functions/variables */
static int do_sendfile(const int out_fd, const int in_fd,
                       unsigned int num_send, filesize_t start_pos);
static void vsf_sysutil_setproctitle_internal(_Nt_array_ptr<const char> p_text : count(0));
static struct mystr s_proctitle_prefix_str;

/* These two aren't static to avoid OpenBSD build warnings. */
void vsf_insert_uwtmp(_Ptr<const struct mystr> p_user_str, _Ptr<const struct mystr> p_host_str);
void vsf_remove_uwtmp(void);

#ifndef VSF_SYSDEP_HAVE_PAM
int
vsf_sysdep_check_auth(_Ptr<struct mystr> p_user_str, _Ptr<const struct mystr> p_pass_str, _Ptr<const struct mystr> p_remote_host)
{
  _Nt_array_ptr<const char> p_crypted = 0;
  _Ptr<const struct passwd> p_pwd = getpwnam(str_getbuf(p_user_str));
  (void) p_remote_host;
  if (p_pwd == NULL)
  {
    return 0;
  }
  #ifdef VSF_SYSDEP_HAVE_USERSHELL
  if (tunable_check_shell)
  {
    _Nt_array_ptr<const char> p_shell = 0;
    _Unchecked {
      p_shell = _Assume_bounds_cast<_Nt_array_ptr<const char>>(getusershell(), count(0));
    }
    while (p_shell != NULL)
    {
      _Nt_array_ptr<char> p_pwd_shell = 0;
      _Unchecked {
        p_pwd_shell = _Assume_bounds_cast<_Nt_array_ptr<char>>(p_pwd->pw_shell, count(0));
      }
      if (!vsf_sysutil_strcmp(p_shell, p_pwd_shell))
      {
        break;
      }
      _Unchecked {
        p_shell = _Assume_bounds_cast<_Nt_array_ptr<const char>>(getusershell(), count(0));
      }
    }
    endusershell();
    if (p_shell == NULL)
    {
      return 0;
    }
  }
  #endif
  #ifdef VSF_SYSDEP_HAVE_SHADOW
  {
    _Ptr<const struct spwd> p_spwd = 0;
    _Unchecked {
      p_spwd = _Assume_bounds_cast<_Ptr<const struct spwd>>(getspnam((char*) str_getbuf(p_user_str)));
    }
    if (p_spwd != NULL)
    {
      long curr_time = vsf_sysutil_get_time_sec();
      int days;
      days = curr_time / (60 * 60 * 24);
      if (p_spwd->sp_expire > 0 && p_spwd->sp_expire < days)
      {
        return 0;
      }
      if (p_spwd->sp_lstchg > 0 && p_spwd->sp_max > 0 &&
          p_spwd->sp_lstchg + p_spwd->sp_max < days)
      {
        return 0;
      }
      _Nt_array_ptr<char> p_spwd_sp_pwdp = 0;
      _Unchecked {
        p_spwd_sp_pwdp = _Assume_bounds_cast<_Nt_array_ptr<char>>(p_spwd->sp_pwdp, count(0));
        p_crypted = _Assume_bounds_cast<_Nt_array_ptr<char>>(crypt((char*) str_getbuf(p_pass_str), (char*) p_spwd_sp_pwdp), count(0));
      }
      if (!vsf_sysutil_strcmp(p_crypted, p_spwd_sp_pwdp))
      {
        return 1;
      }
    }
  }
  #endif /* VSF_SYSDEP_HAVE_SHADOW */
  _Nt_array_ptr<char> p_pwd_pw = 0;
  _Unchecked {
    p_pwd_pw = _Assume_bounds_cast<_Nt_array_ptr<char>>(p_pwd->pw_passwd, count(0));
    p_crypted = _Assume_bounds_cast<_Nt_array_ptr<char>>(crypt((char*) str_getbuf(p_pass_str), (char*) p_pwd_pw), count(0));
  }

  if (!vsf_sysutil_strcmp(p_crypted, p_pwd_pw))
  {
    return 1;
  }
  return 0;
}

#else /* VSF_SYSDEP_HAVE_PAM */

#if (defined(__sun) || defined(__hpux)) && \
    !defined(LINUX_PAM) && !defined(_OPENPAM)
/* Sun's PAM doesn't use const here, while Linux-PAM and OpenPAM do */
#define lo_const
#else
#define lo_const const
#endif
typedef lo_const void* pam_item_t;

static pam_handle_t* s_pamh;
static struct mystr s_pword_str;
static int pam_conv_func(int nmsg, const struct pam_message** p_msg,
                         struct pam_response** p_reply, void* p_addata);
static void vsf_auth_shutdown(void);

int
vsf_sysdep_check_auth(struct mystr* p_user_str,
                      const struct mystr* p_pass_str,
                      const struct mystr* p_remote_host)
{
  int retval = -1;
  pam_item_t item;
  const char* pam_user_name = 0;
  struct pam_conv the_conv =
  {
    &pam_conv_func,
    0
  };
  if (s_pamh != 0)
  {
    bug("vsf_sysdep_check_auth");
  }
  str_copy(&s_pword_str, p_pass_str);
  if (tunable_pam_service_name)
  {
    retval = pam_start(tunable_pam_service_name,
                       str_getbuf(p_user_str), &the_conv, &s_pamh);
  }
  if (retval != PAM_SUCCESS)
  {
    s_pamh = 0;
    return 0;
  }
#ifdef PAM_RHOST
  retval = pam_set_item(s_pamh, PAM_RHOST, str_getbuf(p_remote_host));
  if (retval != PAM_SUCCESS)
  {
    (void) pam_end(s_pamh, retval);
    s_pamh = 0;
    return 0;
  }
#endif
#ifdef PAM_TTY
  retval = pam_set_item(s_pamh, PAM_TTY, "ftp");
  if (retval != PAM_SUCCESS)
  {
    (void) pam_end(s_pamh, retval);
    s_pamh = 0;
    return 0;
  }
#endif
#ifdef PAM_RUSER
  retval = pam_set_item(s_pamh, PAM_RUSER, str_getbuf(p_user_str));
  if (retval != PAM_SUCCESS)
  {
    (void) pam_end(s_pamh, retval);
    s_pamh = 0;
    return 0;
  }
#endif
  retval = pam_authenticate(s_pamh, 0);
  if (retval != PAM_SUCCESS)
  {
    (void) pam_end(s_pamh, retval);
    s_pamh = 0;
    return 0;
  }
#ifdef PAM_USER
  retval = pam_get_item(s_pamh, PAM_USER, &item);
  if (retval != PAM_SUCCESS)
  {
    (void) pam_end(s_pamh, retval);
    s_pamh = 0;
    return 0;
  }
  pam_user_name = item;
  str_alloc_text(p_user_str, pam_user_name);
#endif
  retval = pam_acct_mgmt(s_pamh, 0);
  if (retval != PAM_SUCCESS)
  {
    (void) pam_end(s_pamh, retval);
    s_pamh = 0;
    return 0;
  }
  retval = pam_setcred(s_pamh, PAM_ESTABLISH_CRED);
  if (retval != PAM_SUCCESS)
  {
    (void) pam_end(s_pamh, retval);
    s_pamh = 0;
    return 0;
  }
  if (!tunable_session_support)
  {
    /* You're in already! */
    (void) pam_end(s_pamh, retval);
    s_pamh = 0;
    return 1;
  }
  /* Must do this BEFORE opening a session for pam_limits to count us */
  vsf_insert_uwtmp(p_user_str, p_remote_host);
  retval = pam_open_session(s_pamh, 0);
  if (retval != PAM_SUCCESS)
  {
    vsf_remove_uwtmp();
    (void) pam_setcred(s_pamh, PAM_DELETE_CRED);
    (void) pam_end(s_pamh, retval);
    s_pamh = 0;
    return 0;
  }
  /* We MUST ensure the PAM session, utmp, wtmp etc. are cleaned up, however
   * we exit.
   */
  vsf_sysutil_set_exit_func(vsf_auth_shutdown);
  /* You're in dude */
  return 1;
}

static void
vsf_auth_shutdown(void)
{
  if (s_pamh == 0)
  {
    bug("vsf_auth_shutdown");
  }
  (void) pam_close_session(s_pamh, 0);
  (void) pam_setcred(s_pamh, PAM_DELETE_CRED);
  (void) pam_end(s_pamh, PAM_SUCCESS);
  s_pamh = 0;
  vsf_remove_uwtmp();
}

static int
pam_conv_func(int nmsg, const struct pam_message** p_msg,
              struct pam_response** p_reply, void* p_addata)
{
  int i;
  struct pam_response* p_resps = 0;
  (void) p_addata;
  if (nmsg < 0)
  {
    bug("dodgy nmsg in pam_conv_func");
  }
  p_resps = vsf_sysutil_malloc(sizeof(struct pam_response) * nmsg);
  for (i=0; i<nmsg; i++)
  {
    switch (p_msg[i]->msg_style)
    {
      case PAM_PROMPT_ECHO_OFF:
        p_resps[i].resp_retcode = PAM_SUCCESS;
        p_resps[i].resp = (char*) str_strdup(&s_pword_str);
        break;
      case PAM_TEXT_INFO:
      case PAM_ERROR_MSG:
        p_resps[i].resp_retcode = PAM_SUCCESS;
        p_resps[i].resp = 0;
        break;
      case PAM_PROMPT_ECHO_ON:
      default:
        vsf_sysutil_free(p_resps);
        return PAM_CONV_ERR;
        break;
    }
  }
  *p_reply = p_resps;
  return PAM_SUCCESS;
}

#endif /* VSF_SYSDEP_HAVE_PAM */

/* Capabilities support (or lack thereof) */
void
vsf_sysdep_keep_capabilities(void)
{
  if (!vsf_sysdep_has_capabilities_as_non_root())
  {
    bug("asked to keep capabilities, but no support exists");
  }
#ifdef VSF_SYSDEP_HAVE_SETKEEPCAPS
  {
    int retval = 0; 
    _Unchecked {
      retval = prctl(PR_SET_KEEPCAPS, 1);
    }
    if (vsf_sysutil_retval_is_error(retval))
    {
      die("prctl");
    }
  }
#endif /* VSF_SYSDEP_HAVE_SETKEEPCAPS */
}
#if !defined(VSF_SYSDEP_HAVE_CAPABILITIES) && !defined(VSF_SYSDEP_HAVE_LIBCAP)

int
vsf_sysdep_has_capabilities(void)
{
  return 0;
}

int
vsf_sysdep_has_capabilities_as_non_root(void)
{
  return 0;
}

void
vsf_sysdep_adopt_capabilities(unsigned int caps)
{
  (void) caps;
  bug("asked to adopt capabilities, but no support exists");
}

#else /* VSF_SYSDEP_HAVE_CAPABILITIES || VSF_SYSDEP_HAVE_LIBCAP */

static int do_checkcap(void);

int
vsf_sysdep_has_capabilities_as_non_root(void)
{
  static int s_prctl_checked;
  static int s_runtime_prctl_works;
  if (!s_prctl_checked)
  {
  #ifdef VSF_SYSDEP_HAVE_SETKEEPCAPS
    /* Clarity: note embedded call to prctl() syscall */
    int retval = 0;
    _Unchecked {
      retval = prctl(PR_SET_KEEPCAPS, 0);
    }
    if (!vsf_sysutil_retval_is_error(retval))
    {
      s_runtime_prctl_works = 1;
    }
  #endif /* VSF_SYSDEP_HAVE_SETKEEPCAPS */
    s_prctl_checked = 1;
  }
  return s_runtime_prctl_works;
}

int
vsf_sysdep_has_capabilities(void)
{
  /* Even though compiled with capabilities, the runtime system may lack them.
   * Also, RH7.0 kernel headers advertise a 2.4.0 box, but on a 2.2.x kernel!
   */
  static int s_caps_checked;
  static int s_runtime_has_caps;
  if (!s_caps_checked)
  {
    s_runtime_has_caps = do_checkcap();
    s_caps_checked = 1;
  }
  return s_runtime_has_caps;
}
  
  #ifndef VSF_SYSDEP_HAVE_LIBCAP
static int
do_checkcap(void)
{
  /* EFAULT (EINVAL if page 0 mapped) vs. ENOSYS */
  int retval = capset(0, 0);
  if (!vsf_sysutil_retval_is_error(retval) ||
      vsf_sysutil_get_error() != kVSFSysUtilErrNOSYS)
  {
    return 1;
  }
  return 0;
}

void
vsf_sysdep_adopt_capabilities(unsigned int caps)
{
  /* n.b. yes I know I should be using libcap!! */
  int retval;
  struct __user_cap_header_struct cap_head;
  struct __user_cap_data_struct cap_data;
  __u32 cap_mask = 0;
  if (!caps)
  {
    bug("asked to adopt no capabilities");
  }
  vsf_sysutil_memclr<struct __user_cap_header_struct>(&cap_head, sizeof(cap_head));
  vsf_sysutil_memclr<struct __user_cap_data_struct>(&cap_data, sizeof(cap_data));
  cap_head.version = _LINUX_CAPABILITY_VERSION;
  cap_head.pid = 0;
  if (caps & kCapabilityCAP_CHOWN)
  {
    cap_mask |= (1 << CAP_CHOWN);
  }
  if (caps & kCapabilityCAP_NET_BIND_SERVICE)
  {
    cap_mask |= (1 << CAP_NET_BIND_SERVICE);
  }
  cap_data.effective = cap_data.permitted = cap_mask;
  cap_data.inheritable = 0;
  _Unchecked {
    retval = capset((struct __user_cap_header_struct *) &cap_head, &cap_data);
  }
  if (retval != 0)
  {
    die("capset");
  }
}

  #else /* VSF_SYSDEP_HAVE_LIBCAP */
static int
do_checkcap(void)
{
  cap_t current_caps = cap_get_proc();
  cap_free(current_caps);
  if (current_caps != NULL)
  {
    return 1;
  }
  return 0;
}

void
vsf_sysdep_adopt_capabilities(unsigned int caps)
{
  int retval;
  cap_value_t cap_value;
  cap_t adopt_caps = cap_init();
  if (caps & kCapabilityCAP_CHOWN)
  {
    cap_value = CAP_CHOWN;
    cap_set_flag(adopt_caps, CAP_EFFECTIVE, 1, &cap_value, CAP_SET);
    cap_set_flag(adopt_caps, CAP_PERMITTED, 1, &cap_value, CAP_SET);
  }
  if (caps & kCapabilityCAP_NET_BIND_SERVICE)
  {
    cap_value = CAP_NET_BIND_SERVICE;
    cap_set_flag(adopt_caps, CAP_EFFECTIVE, 1, &cap_value, CAP_SET);
    cap_set_flag(adopt_caps, CAP_PERMITTED, 1, &cap_value, CAP_SET);
  }
  retval = cap_set_proc(adopt_caps);
  if (retval != 0)
  {
    die("cap_set_proc");
  }
  cap_free(adopt_caps);
}

  #endif /* !VSF_SYSDEP_HAVE_LIBCAP */
#endif /* VSF_SYSDEP_HAVE_CAPABILITIES || VSF_SYSDEP_HAVE_LIBCAP */

int
vsf_sysutil_sendfile(const int out_fd, const int in_fd, _Ptr<filesize_t> p_offset, filesize_t num_send, unsigned int max_chunk)
{
  /* Grr - why is off_t signed? */
  if (*p_offset < 0 || num_send < 0)
  {
    die("invalid offset or send count in vsf_sysutil_sendfile");
  }
  if (max_chunk == 0)
  {
    max_chunk = INT_MAX;
  }
  while (num_send > 0)
  {
    int retval;
    unsigned int send_this_time;
    if (num_send > max_chunk)
    {
      send_this_time = max_chunk;
    }
    else
    {
      send_this_time = (unsigned int) num_send;
    }
    /* Keep input file position in line with sendfile() calls */
    vsf_sysutil_lseek_to(in_fd, *p_offset);
    retval = do_sendfile(out_fd, in_fd, send_this_time, *p_offset);
    if (vsf_sysutil_retval_is_error(retval) || retval == 0)
    {
      return retval;
    }
    num_send -= retval;
    *p_offset += retval;
  }
  return 0;
}

static int do_sendfile(const int out_fd, const int in_fd,
                       unsigned int num_send, filesize_t start_pos)
{
  /* Probably should one day be shared with instance in ftpdataio.c */
  static _Array_ptr<char> p_recvbuf : count(VSFTP_DATA_BUFSIZE);
  unsigned int total_written = 0;
  int retval;
  enum EVSFSysUtilError error;
  (void) start_pos;
  (void) error;
#if defined(VSF_SYSDEP_HAVE_LINUX_SENDFILE) || \
    defined(VSF_SYSDEP_HAVE_FREEBSD_SENDFILE) || \
    defined(VSF_SYSDEP_HAVE_HPUX_SENDFILE) || \
    defined(VSF_SYSDEP_HAVE_AIX_SENDFILE) || \
    defined(VSF_SYSDEP_HAVE_SOLARIS_SENDFILE)
  if (tunable_use_sendfile)
  {
    static int s_sendfile_checked;
    static int s_runtime_sendfile_works;
    if (!s_sendfile_checked || s_runtime_sendfile_works)
    {
      do
      {
  #ifdef VSF_SYSDEP_HAVE_LINUX_SENDFILE
        retval = sendfile(out_fd, in_fd, NULL, num_send);
  #elif defined(VSF_SYSDEP_HAVE_FREEBSD_SENDFILE)
        {
          /* XXX - start_pos will truncate on 32-bit machines - can we
           * say "start from current pos"?
           */
          off_t written = 0;
          retval = sendfile(in_fd, out_fd, start_pos, num_send, NULL,
                            &written, 0);
          /* Translate to Linux-like retval */
          if (written > 0)
          {
            retval = (int) written;
          }
        }
  #elif defined(VSF_SYSDEP_HAVE_SOLARIS_SENDFILE)
        {
          size_t written = 0;
          struct sendfilevec the_vec;
          vsf_sysutil_memclr(&the_vec, sizeof(the_vec));
          the_vec.sfv_fd = in_fd;
          the_vec.sfv_off = start_pos;
          the_vec.sfv_len = num_send;
          retval = sendfilev(out_fd, &the_vec, 1, &written);
          /* Translate to Linux-like retval */
          if (written > 0)
          {
            retval = (int) written;
          }
        }
  #elif defined(VSF_SYSDEP_HAVE_AIX_SENDFILE)
        {
          struct sf_parms sf_iobuf;
          vsf_sysutil_memclr(&sf_iobuf, sizeof(sf_iobuf));
          sf_iobuf.header_data = NULL;
          sf_iobuf.header_length = 0;
          sf_iobuf.trailer_data = NULL;
          sf_iobuf.trailer_length = 0;
          sf_iobuf.file_descriptor = in_fd;
          sf_iobuf.file_offset = start_pos;
          sf_iobuf.file_bytes = num_send;

          retval = send_file((int*)&out_fd, &sf_iobuf, 0);
          if (retval >= 0)
          {
            retval = sf_iobuf.bytes_sent;
          }
        }
  #else /* must be VSF_SYSDEP_HAVE_HPUX_SENDFILE */
        {
          retval = sendfile(out_fd, in_fd, start_pos, num_send, NULL, 0);
        }
  #endif /* VSF_SYSDEP_HAVE_LINUX_SENDFILE */
        error = vsf_sysutil_get_error();
        vsf_sysutil_check_pending_actions(kVSFSysUtilIO, retval, out_fd);
      }
      while (vsf_sysutil_retval_is_error(retval) &&
             error == kVSFSysUtilErrINTR);
      if (!s_sendfile_checked)
      {
        s_sendfile_checked = 1;
        if (!vsf_sysutil_retval_is_error(retval) ||
            error != kVSFSysUtilErrNOSYS)
        {
          s_runtime_sendfile_works = 1;
        }
      }
      if (!vsf_sysutil_retval_is_error(retval))
      {
        return retval;
      }
      if (s_runtime_sendfile_works && error != kVSFSysUtilErrINVAL &&
          error != kVSFSysUtilErrOPNOTSUPP)
      {
        return retval;
      }
      /* Fall thru to normal implementation. We won't check again. NOTE -
       * also falls through if sendfile() is OK but it returns EINVAL. For
       * Linux this means the file was not page cache backed. Original
       * complaint was trying to serve files from an NTFS filesystem!
       */
    }
  }
#endif /* VSF_SYSDEP_HAVE_LINUX_SENDFILE || VSF_SYSDEP_HAVE_FREEBSD_SENDFILE */
  if (p_recvbuf == 0)
  {
    vsf_secbuf_static_alloc(p_recvbuf, VSFTP_DATA_BUFSIZE);
  }
  while (1)
  {
    unsigned int num_read;
    unsigned int num_written;
    unsigned int num_read_this_time = VSFTP_DATA_BUFSIZE;
    if (num_read_this_time > num_send)
    {
      num_read_this_time = num_send;
    }

    _Array_ptr<char> tmp : count(num_read_this_time) = _Dynamic_bounds_cast<_Array_ptr<char>>(p_recvbuf, count(num_read_this_time));
    retval = vsf_sysutil_read<char>(in_fd, tmp, num_read_this_time);
    if (retval < 0)
    {
      return retval;
    }
    else if (retval == 0)
    {
      return -1;
    }
    num_read = (unsigned int) retval;
    _Array_ptr<char> tmp2 : count(num_read) = _Dynamic_bounds_cast<_Array_ptr<char>>(p_recvbuf, count(num_read));
    retval = vsf_sysutil_write_loop<char>(out_fd, tmp2, num_read);
    if (retval < 0)
    {
      return retval;
    }
    num_written = (unsigned int) retval;
    total_written += num_written;
    if (num_written != num_read)
    {
      return num_written;
    }
    if (num_written > num_send)
    {
      bug("num_written bigger than num_send in do_sendfile");
    }
    num_send -= num_written;
    if (num_send == 0)
    {
      /* Bingo! */
      return total_written;
    }
  }
}

void
vsf_sysutil_set_proctitle_prefix(_Ptr<const struct mystr> p_str)
{
  str_copy(&s_proctitle_prefix_str, p_str);
}

/* This delegation is common to all setproctitle() implementations */
void
vsf_sysutil_setproctitle_str(_Ptr<const struct mystr> p_str)
{
  vsf_sysutil_setproctitle(((_Nt_array_ptr<const char> )str_getbuf(p_str)));
}

void
vsf_sysutil_setproctitle(_Nt_array_ptr<const char> p_text : count(0))
{
  struct mystr proctitle_str = INIT_MYSTR;
  str_copy(&proctitle_str, &s_proctitle_prefix_str);
  if (!str_isempty(&proctitle_str))
  {
    str_append_text(&proctitle_str, ": ");
  }
  str_append_text(&proctitle_str, p_text);
  vsf_sysutil_setproctitle_internal(((_Nt_array_ptr<const char> )str_getbuf(&proctitle_str)));
  str_free(&proctitle_str);
}

#ifdef VSF_SYSDEP_HAVE_SETPROCTITLE
void
vsf_sysutil_setproctitle_init(int argc, const char* argv[])
{
  (void) argc;
  (void) argv;
}

void
vsf_sysutil_setproctitle_internal(const char* p_buf)
{
  setproctitle("%s", p_buf);
}
#elif defined(VSF_SYSDEP_HAVE_HPUX_SETPROCTITLE)
void
vsf_sysutil_setproctitle_init(int argc, const char* argv[])
{
  (void) argc;
  (void) argv;
}

void
vsf_sysutil_setproctitle_internal(const char* p_buf)
{
  struct mystr proctitle_str = INIT_MYSTR;
  union pstun p;
  str_alloc_text(&proctitle_str, "vsftpd: ");
  str_append_text(&proctitle_str, p_buf);
  p.pst_command = str_getbuf(&proctitle_str);
  pstat(PSTAT_SETCMD, p, 0, 0, 0);
  str_free(&proctitle_str);
}
#elif defined(VSF_SYSDEP_TRY_LINUX_SETPROCTITLE_HACK)
void
vsf_sysutil_setproctitle_init(int argc, _Array_ptr<_Nt_array_ptr<const char>> argv : count(argc))
{
  int i;
  _Nt_array_ptr<_Nt_array_ptr<char>> p_env = environ;
  if (s_proctitle_inited)
  {
    bug("vsf_sysutil_setproctitle_init called twice");
  }
  s_proctitle_inited = 1;
  if (argv[0] == 0)
  {
    die("no argv[0] in vsf_sysutil_setproctitle_init");
  }
  for (i=0; i<argc; i++)
  {
    s_proctitle_space += vsf_sysutil_strlen(argv[i]) + 1;
    if (i > 0)
    {
      argv[i] = 0;
    }
  }
  while (*p_env != 0)
  {
    s_proctitle_space += vsf_sysutil_strlen(*p_env) + 1;
    p_env++;
  }
  /* Oops :-) */
  environ = 0;

  _Unchecked {
    s_p_proctitle = _Assume_bounds_cast<_Nt_array_ptr<char>>(argv[0], count(s_proctitle_space));
  }
  vsf_sysutil_memclr<char>(s_p_proctitle, s_proctitle_space);
}

void
vsf_sysutil_setproctitle_internal(_Nt_array_ptr<const char> p_buf : count(0))
{
  struct mystr proctitle_str = INIT_MYSTR;
  unsigned int to_copy;
  if (!s_proctitle_inited)
  {
    bug("vsf_sysutil_setproctitle: not initialized");
  }
  vsf_sysutil_memclr<char>(s_p_proctitle, s_proctitle_space);
  if (s_proctitle_space < 32)
  {
    return;
  }

  str_alloc_text(&proctitle_str, "vsftpd: ");
  str_append_text(&proctitle_str, p_buf);
  unsigned int len = str_getlen(&proctitle_str);
  to_copy = len;
  unchecked_widen_bounds(_Nt_array_ptr<const char>, tmp, count(len), str_getbuf(&proctitle_str))
  if (to_copy > s_proctitle_space - 1)
  {
    to_copy = s_proctitle_space - 1;
  }
  checked_widen_bounds(_Nt_array_ptr<char>, tmp2, count(to_copy), s_p_proctitle);
  checked_widen_bounds(_Nt_array_ptr<char>, tmp3, count(to_copy), tmp);
  vsf_sysutil_memcpy<char>(tmp2, tmp3, to_copy);
  str_free(&proctitle_str);
  s_p_proctitle[to_copy] = '\0';
}
#else /* VSF_SYSDEP_HAVE_SETPROCTITLE */
void
vsf_sysutil_setproctitle_init(int argc, const char* argv[])
{
  (void) argc;
  (void) argv;
}

void
vsf_sysutil_setproctitle_internal(const char* p_buf)
{
  (void) p_buf;
}
#endif /* VSF_SYSDEP_HAVE_SETPROCTITLE */

#ifdef VSF_SYSDEP_HAVE_MAP_ANON
void
vsf_sysutil_map_anon_pages_init(void)
{
}

_Itype_for_any(T) void*
vsf_sysutil_map_anon_pages(unsigned int length) : itype(_Array_ptr<T>) byte_count(length)
{
  _Array_ptr<T> retval : byte_count(length) = 0;
  _Unchecked {
    retval = _Assume_bounds_cast<_Array_ptr<T>>(
      mmap(0, length, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0), byte_count(length));
  }
  int map_failed = 0;
  _Unchecked {
    map_failed = (retval == MAP_FAILED);
  }
  if (map_failed)
  {
    die("mmap");
  }
  return retval;
}
#else /* VSF_SYSDEP_HAVE_MAP_ANON */
void
vsf_sysutil_map_anon_pages_init(void)
{
  if (s_zero_fd != -1)
  {
    bug("vsf_sysutil_map_anon_pages_init called twice");
  }
  _Unchecked { s_zero_fd = open("/dev/zero", O_RDWR); }
  if (s_zero_fd < 0)
  {
    die("could not open /dev/zero");
  }
}

_Itype_for_any(T) void*
vsf_sysutil_map_anon_pages(unsigned int length) : itype(_Array_ptr<T>) byte_count(length)
{
  _Array_ptr<T> retval : byte_count(length) = 0;
  _Unchecked {
    retval = _Assume_bounds_cast<_Array_ptr<T>>(
        mmap(0, length, PROT_READ | PROT_WRITE, MAP_PRIVATE, s_zero_fd, 0), byte_count(length));
  }
  int map_failed = 0;
  _Unchecked {
    map_failed = (retval == MAP_FAILED);
  }
  if (map_failed)
  {
    die("mmap");
  }
  return retval;
}
#endif /* VSF_SYSDEP_HAVE_MAP_ANON */

#ifndef VSF_SYSDEP_NEED_OLD_FD_PASSING

void
vsf_sysutil_send_fd(int sock_fd, int send_fd)
{
  int retval;
  struct msghdr msg;
  _Ptr<struct cmsghdr> p_cmsg = 0;
  struct iovec vec;
  char cmsgbuf _Checked[CMSG_SPACE(sizeof(send_fd))];
  _Ptr<int> p_fds = 0;
  char sendchar = 0;
  _Unchecked { msg.msg_control = (void*) cmsgbuf; }
  msg.msg_controllen = sizeof(cmsgbuf);
  _Unchecked { p_cmsg = _Assume_bounds_cast<_Ptr<struct cmsghdr>>(CMSG_FIRSTHDR(&msg)); }
  p_cmsg->cmsg_level = SOL_SOCKET;
  p_cmsg->cmsg_type = SCM_RIGHTS;
  p_cmsg->cmsg_len = CMSG_LEN(sizeof(send_fd));
  _Unchecked { p_fds = _Assume_bounds_cast<_Ptr<int>>(CMSG_DATA(p_cmsg)); }
  *p_fds = send_fd;
  msg.msg_controllen = p_cmsg->cmsg_len;
  _Unchecked { msg.msg_name = NULL; }
  msg.msg_namelen = 0;
  _Unchecked { msg.msg_iov = &vec; }
  msg.msg_iovlen = 1;
  msg.msg_flags = 0;
  /* "To pass file descriptors or credentials you need to send/read at
   * least on byte" (man 7 unix)
   */
  _Unchecked { vec.iov_base = &sendchar; }
  vec.iov_len = sizeof(sendchar);
  retval = sendmsg(sock_fd, &msg, 0);
  if (retval != 1)
  {
    die("sendmsg");
  }
}

int
vsf_sysutil_recv_fd(const int sock_fd)
{
  int retval;
  struct msghdr msg;
  char recvchar;
  struct iovec vec;
  int recv_fd;
  char cmsgbuf _Checked[CMSG_SPACE(sizeof(recv_fd))];
  _Ptr<struct cmsghdr> p_cmsg = 0;
  _Ptr<int> p_fd = 0;
  _Unchecked { vec.iov_base = &recvchar; }
  vec.iov_len = sizeof(recvchar);
  _Unchecked { msg.msg_name = NULL; }
  msg.msg_namelen = 0;
  _Unchecked { msg.msg_iov = &vec; }
  msg.msg_iovlen = 1;
  _Unchecked { msg.msg_control = (void*) cmsgbuf; }
  msg.msg_controllen = sizeof(cmsgbuf);
  msg.msg_flags = 0;
  /* In case something goes wrong, set the fd to -1 before the syscall */
  _Unchecked { p_fd = _Assume_bounds_cast<_Ptr<int>>(CMSG_DATA(CMSG_FIRSTHDR(&msg))); }
  *p_fd = -1;  
  retval = recvmsg(sock_fd, &msg, 0);
  if (retval != 1)
  {
    die("recvmsg");
  }
  _Unchecked { p_cmsg = _Assume_bounds_cast<_Ptr<struct cmsghdr>>(CMSG_FIRSTHDR(&msg)); }
  if (p_cmsg == NULL)
  {
    die("no passed fd");
  }
  /* We used to verify the returned cmsg_level, cmsg_type and cmsg_len here,
   * but Linux 2.0 totally uselessly fails to fill these in.
   */
  _Unchecked { p_fd = _Assume_bounds_cast<_Ptr<int>>(CMSG_DATA(p_cmsg)); }
  recv_fd = *p_fd;
  if (recv_fd == -1)
  {
    die("no passed fd");
  }
  return recv_fd;
}

#else /* !VSF_SYSDEP_NEED_OLD_FD_PASSING */

void
vsf_sysutil_send_fd(int sock_fd, int send_fd)
{
  int retval;
  char send_char = 0;
  struct msghdr msg;
  struct iovec vec;
  vec.iov_base = &send_char;
  vec.iov_len = 1;
  msg.msg_name = NULL;
  msg.msg_namelen = 0;
  msg.msg_iov = &vec;
  msg.msg_iovlen = 1;
  msg.msg_accrights = (caddr_t) &send_fd;
  msg.msg_accrightslen = sizeof(send_fd);
  retval = sendmsg(sock_fd, &msg, 0);
  if (retval != 1)
  {
    die("sendmsg");
  }
}

int
vsf_sysutil_recv_fd(int sock_fd)
{
  int retval;
  struct msghdr msg;
  struct iovec vec;
  char recv_char;
  int recv_fd = -1;
  vec.iov_base = &recv_char;
  vec.iov_len = 1;
  msg.msg_name = NULL;
  msg.msg_namelen = 0;
  msg.msg_iov = &vec;
  msg.msg_iovlen = 1;
  msg.msg_accrights = (caddr_t) &recv_fd;
  msg.msg_accrightslen = sizeof(recv_fd);
  retval = recvmsg(sock_fd, &msg, 0);
  if (retval != 1)
  {
    die("recvmsg");
  }
  if (recv_fd == -1)
  {
    die("no passed fd");
  }
  return recv_fd;
}

#endif /* !VSF_SYSDEP_NEED_OLD_FD_PASSING */

#ifndef VSF_SYSDEP_HAVE_UTMPX

void
vsf_insert_uwtmp(const struct mystr* p_user_str,
                 const struct mystr* p_host_str)
{
  (void) p_user_str;
  (void) p_host_str;
}

void
vsf_remove_uwtmp(void)
{
}

#else /* !VSF_SYSDEP_HAVE_UTMPX */

/* IMHO, the pam_unix module REALLY should be doing this in its SM component */
/* Statics */
static int s_uwtmp_inserted;
static struct utmpx s_utent;

void
vsf_insert_uwtmp(_Ptr<const struct mystr> p_user_str, _Ptr<const struct mystr> p_host_str)
{
  size_t ut_line_size = 0;
  _Unchecked {
    ut_line_size = sizeof(s_utent.ut_line);
  }
  if (ut_line_size < 16)
  {
    return;
  }
  if (s_uwtmp_inserted)
  {
    bug("vsf_insert_uwtmp");
  }
  {
    struct mystr line_str = INIT_MYSTR;
    str_alloc_text(&line_str, "vsftpd:");
    str_append_ulong(&line_str, vsf_sysutil_getpid());
    if (str_getlen(&line_str) >= ut_line_size)
    {
      str_free(&line_str);
      return;
    }

    _Nt_array_ptr<const char> str_buf = str_getbuf(&line_str);
    unsigned int str_buf_len = str_getlen(&line_str);
    unchecked_widen_bounds(_Nt_array_ptr<char>, str_buf_bounds, byte_count(str_buf_len), str_buf)
    checked_widen_bounds(_Array_ptr<char>, str_buf_line_bounds, byte_count(ut_line_size), str_buf_bounds)  
    unchecked_widen_bounds(_Array_ptr<char>, ut_line_bounds, byte_count(ut_line_size), s_utent.ut_line)
    vsf_sysutil_strcpy(ut_line_bounds, str_buf_line_bounds, ut_line_size);
    str_free(&line_str);
  }
  s_uwtmp_inserted = 1;
  s_utent.ut_type = USER_PROCESS;
  s_utent.ut_pid = vsf_sysutil_getpid();

  size_t ut_user_size = 0;
  _Unchecked {
    ut_user_size = sizeof(s_utent.ut_user);
  }

  _Nt_array_ptr<const char> user_str_buf = str_getbuf(p_user_str);
  unsigned int user_str_len = str_getlen(p_user_str);
  unchecked_widen_bounds(_Nt_array_ptr<char>, user_str_buf_bounds, byte_count(user_str_len), user_str_buf)
  checked_widen_bounds(_Array_ptr<char>, user_str_ut_user_bounds, byte_count(ut_user_size), user_str_buf_bounds)  
  unchecked_widen_bounds(_Array_ptr<char>, ut_user_bounds, byte_count(ut_user_size), s_utent.ut_user)
  vsf_sysutil_strcpy(ut_user_bounds, user_str_ut_user_bounds, ut_user_size);

  size_t ut_host_size = 0;
  _Unchecked {
    ut_host_size = sizeof(s_utent.ut_host);
  }

  _Nt_array_ptr<const char> host_str_buf = str_getbuf(p_host_str);
  unsigned int host_str_len = str_getlen(p_host_str);
  unchecked_widen_bounds(_Nt_array_ptr<char>, host_str_buf_bounds, byte_count(host_str_len), host_str_buf)
  checked_widen_bounds(_Array_ptr<char>, host_str_ut_host_bounds, byte_count(ut_host_size), host_str_buf_bounds)  
  unchecked_widen_bounds(_Array_ptr<char>, ut_host_bounds, byte_count(ut_host_size), s_utent.ut_host)
  vsf_sysutil_strcpy(ut_host_bounds, host_str_ut_host_bounds, ut_host_size);

  s_utent.ut_tv.tv_sec = vsf_sysutil_get_time_sec();
  setutxent();
  _Unchecked {
    (void) pututxline(&s_utent);
  }
  endutxent();
  _Unchecked {
    updwtmpx(WTMPX_FILE, &s_utent);
  }
}

void
vsf_remove_uwtmp(void)
{
  if (!s_uwtmp_inserted)
  {
    return;
  }
  s_uwtmp_inserted = 0;
  s_utent.ut_type = DEAD_PROCESS;
  _Unchecked {
    vsf_sysutil_memclr<char>(s_utent.ut_user, sizeof(s_utent.ut_user));
    vsf_sysutil_memclr<char>(s_utent.ut_host, sizeof(s_utent.ut_host));
  }
  s_utent.ut_tv.tv_sec = 0;
  setutxent();
  _Unchecked {
    (void) pututxline(&s_utent);
  }
  endutxent();
  _Unchecked {
    s_utent.ut_tv.tv_sec = vsf_sysutil_get_time_sec();
    updwtmpx(WTMPX_FILE, &s_utent);
  }
}

#endif /* !VSF_SYSDEP_HAVE_UTMPX */

void
vsf_set_die_if_parent_dies(void)
{
#ifdef VSF_SYSDEP_HAVE_SETPDEATHSIG
  int res = 0;
  _Unchecked {
    res = prctl(PR_SET_PDEATHSIG, SIGKILL, 0, 0, 0);
  }
  if (res != 0)
  {
    die("prctl");
  }
#endif
}

void
vsf_set_term_if_parent_dies(void)
{
#ifdef VSF_SYSDEP_HAVE_SETPDEATHSIG

  int res = 0;
  _Unchecked {
    res = prctl(PR_SET_PDEATHSIG, SIGTERM, 0, 0, 0);
  }
  if (res != 0)
  {
    die("prctl");
  }
#endif
}

#ifdef VSF_SYSDEP_HAVE_LINUX_CLONE
/* On Linux versions <2.6.35, netns cleanup may be so slow that
 * creating a netns per connection allows a remote denial-of-service.
 * We therefore do not use CLONE_NEWNET on these versions.
 */
static int
vsf_sysutil_netns_cleanup_is_fast(void) _Unchecked
{
#ifdef __linux__
  struct utsname utsname;
  int r1, r2, r3 = 0;
  return (uname(&utsname) == 0 &&
	  sscanf(utsname.release, "%d.%d.%d", &r1, &r2, &r3) >= 2 &&
	  ((r1 << 16) | (r2 << 8) | r3) >= ((2 << 16) | (6 << 8) | 35));
#else
  /* Assume any other kernel that has the feature don't have this problem */
  return 1;
#endif
}
#endif

int
vsf_sysutil_fork_isolate_all_failok(void)
{
#ifdef VSF_SYSDEP_HAVE_LINUX_CLONE
  static int cloneflags_work = -1;
  if (cloneflags_work < 0)
  {
    cloneflags_work = vsf_sysutil_netns_cleanup_is_fast();
  }
  if (cloneflags_work)
  {
    int ret = 0;
    _Unchecked {
     ret =  syscall(__NR_clone,
                      CLONE_NEWIPC | CLONE_NEWNET | SIGCHLD,
                      NULL);
    }
    if (ret != -1 || (errno != EINVAL && errno != EPERM))
    {
      if (ret == 0)
      {
        vsf_sysutil_post_fork();
      }
      return ret;
    }
    cloneflags_work = 0;
  }
#endif
  return vsf_sysutil_fork_isolate_failok();
}

int
vsf_sysutil_fork_isolate_failok(void)
{
#ifdef VSF_SYSDEP_HAVE_LINUX_CLONE
  static int cloneflags_work = 1;
  if (cloneflags_work)
  {
    int ret = 0;
    _Unchecked {
      ret = syscall(__NR_clone, CLONE_NEWIPC | SIGCHLD, NULL);
    }
    if (ret != -1 || (errno != EINVAL && errno != EPERM))
    {
      if (ret == 0)
      {
        vsf_sysutil_post_fork();
      }
      return ret;
    }
    cloneflags_work = 0;
  }
#endif
  return vsf_sysutil_fork_failok();
}

int
vsf_sysutil_fork_newnet(void)
{
#ifdef VSF_SYSDEP_HAVE_LINUX_CLONE
  static int cloneflags_work = -1;
  if (cloneflags_work < 0)
  {
    cloneflags_work = vsf_sysutil_netns_cleanup_is_fast();
  }
  if (cloneflags_work)
  {
    int ret = 0;
    _Unchecked {
      ret = syscall(__NR_clone, CLONE_NEWNET | SIGCHLD, NULL);
    }
    if (ret != -1 || (errno != EINVAL && errno != EPERM))
    {
      if (ret == 0)
      {
        vsf_sysutil_post_fork();
      }
      return ret;
    }
    cloneflags_work = 0;
  }
#endif
  return vsf_sysutil_fork();
}

int
vsf_sysutil_getpid_nocache(void) _Unchecked
{
#ifdef VSF_SYSDEP_HAVE_LINUX_CLONE
  /* Need to defeat the glibc pid caching because we need to hit a raw
   * sys_clone() above.
   */
  return syscall(__NR_getpid);
#else
  return getpid();
#endif
}
