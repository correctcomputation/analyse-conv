/*
 * Part of Very Secure FTPd
 * Licence: GPL v2
 * Author: Chris Evans
 * access.c
 *
 * Routines to do very very simple access control based on filenames.
 */

#include "access.h"
#include "ls.h"
#include "tunables.h"
#include "str.h"

#pragma CHECKED_SCOPE on

static int
vsf_match_filter(const _Ptr<const struct mystr> p_filename_str, const _Ptr<const struct mystr> p_access_str) {

  unsigned  iters = 0;
  if (vsf_filename_passes_filter(p_filename_str, p_access_str, &iters))
  {
    return 1;
  }
  else
  {
    struct str_locate_result const loc_res =
      str_locate_str(p_filename_str, p_access_str);
    return  loc_res.found;
  }
}

int
vsf_access_check_file(_Ptr<const struct mystr> p_filename_str)
{
  static struct mystr s_access_str;

  if (!tunable_deny_file)
  {
    return 1;
  }
  if (str_isempty(&s_access_str))
  {
    str_alloc_text(&s_access_str, tunable_deny_file);
  }

  if (vsf_match_filter(p_filename_str, &s_access_str))
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

int
vsf_access_check_file_visible(_Ptr<const struct mystr> p_filename_str)
{
  static struct mystr s_access_str;

  if (!tunable_hide_file)
  {
    return 1;
  }
  if (str_isempty(&s_access_str))
  {
    str_alloc_text(&s_access_str, tunable_hide_file);
  }

  if (vsf_match_filter(p_filename_str, &s_access_str))
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

int
vsf_access_check_file_upload(_Ptr<const struct mystr> p_filename_str)
{
  static struct mystr s_access_str;

  if (!tunable_upload_file)
  {
    return 1;
  }
  if (str_isempty(&s_access_str))
  {
    str_alloc_text(&s_access_str, tunable_upload_file);
  }

  return  vsf_match_filter(p_filename_str, &s_access_str);
}

int
vsf_access_check_file_download(_Ptr<const struct mystr> p_filename_str)
{
  static struct mystr s_access_str;

  if (!tunable_download_file)
  {
    return 1;
  }
  if (str_isempty(&s_access_str))
  {
    str_alloc_text(&s_access_str, tunable_download_file);
  }

  return  vsf_match_filter(p_filename_str, &s_access_str);
}
