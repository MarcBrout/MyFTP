/*
** server_tools.c for  in /home/brout_m/rendu/system/PSU_2016_myftp
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun May 14 16:22:45 2017 brout_m
** Last update Sun May 14 16:23:20 2017 brout_m
*/
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "types.h"

int		close_datasocket(t_work *work)
{
  if (close(work->data_socket))
    return (1);
  work->data_socket = -1;
  work->pasv_on = work->port_on = false;
  memset(&work->data.addr, 0, ADDR_SIZE);
  return (0);
}

int		create_full_path(t_work *work, char **out, const char *file)
{
  int		ret;

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
