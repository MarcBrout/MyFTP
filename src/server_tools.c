//
// Created by brout_m on 14/05/17.
//

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "types.h"

int close_datasocket(t_work *work)
{
  if (close(work->data_socket))
    return (1);
  work->data_socket = -1;
  work->pasv_on = work->port_on = false;
  bzero(&work->data.addr, ADDR_SIZE);
  return (0);
}

int create_full_path(t_work *work, char **out, const char *file)
{
  int ret;

  if (file)
  {
    ret = file[0] == '/' ?
          asprintf(out, "%s%s", work->root_path, file) :
          strlen(work->path) == 1 ?
          asprintf(out, "%s%s%s", work->root_path, work->path, file) :
          asprintf(out, "%s%s/%s", work->root_path, work->path, file);
  }
  else
    ret = asprintf(out, "%s%s", work->root_path, work->path);
  if (ret < 0)
    return (1);
  return (0);
}