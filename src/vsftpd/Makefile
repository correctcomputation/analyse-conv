PROG = vsftpd
SOURCES = 	main.c utility.c prelogin.c ftpcmdio.c postlogin.c privsock.c \
		tunables.c ftpdataio.c secbuf.c ls.c \
		postprivparent.c logging.c str.c netstr.c sysstr.c strlist.c \
    banner.c filestr.c parseconf.c secutil.c \
    ascii.c oneprocess.c twoprocess.c privops.c standalone.c hash.c \
    tcpwrap.c ipaddrparse.c access.c features.c readwrite.c opts.c \
    ssl.c sslslave.c ptracesandbox.c ftppolicy.c sysutil.c sysdeputil.c \
    seccompsandbox.c
HDRS = access.h     ftpcodes.h     oneprocess.h      readwrite.h       strlist.h \
	ascii.h      ftpdataio.h    opts.h            secbuf.h          sysdeputil.h \
	banner.h     ftppolicy.h    parseconf.h       seccompsandbox.h  sysstr.h \
	builddefs.h  hacks.h        postlogin.h       secutil.h         sysutil.h \
	defs.h       hash.h         postprivparent.h  session.h         tcpwrap.h \
	features.h   ipaddrparse.h  prelogin.h        ssl.h             tunables.h \
	filesize.h   logging.h      privops.h         sslslave.h        twoprocess.h \
	filestr.h    ls.h           privsock.h        standalone.h      utility.h \
	ftpcmdio.h   netstr.h       ptracesandbox.h   str.h             vsftpver.h \
	port/aix_bogons.h   port/dirfd_extras.h  port/irix_bogons.h   port/solaris_bogons.h \
	port/cmsg_extras.h  port/hpux_bogons.h   port/porting_junk.h  port/tru64_bogons.h

CFLAGS = -g -w -O0 -Wall -W -Wshadow -Werror -Wformat-security \
	-D_FORTIFY_SOURCE=2 -idirafter dummyinc
LDFLAGS = -Wl `./vsf_findlibs.sh`

RUN_OPTIONS =
OUTPUT =
STDIN_FILENAME = /dev/stdin

PATH_TO_SRC = ../

include $(PATH_TO_SRC)Makefile.common

