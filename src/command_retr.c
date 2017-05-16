/*
** command_retr.c for  in /home/brout_m/rendu/system/PSU_2016_myftp
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun May 14 16:05:47 2017 brout_m
** Last update Sun May 14 16:37:03 2017 brout_m
*/
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_command.h"
#include "replies.h"
#include "server_tools.h"

static int	start_upload_to_client(t_work *work, int fd)
{
  char		buff[4096];
  ssize_t	rd;

  if (send_message(CLI_SOCK(work), "%s %s", "125", replies[R125]))
    return (1);
  memset(buff, 0, 4096);
  while ((rd = read(fd, buff, 4095)) > 0)
    {
      if (write(work->data_socket, buff, rd) < 0)
	return (send_message(CLI_SOCK(work), "%s %s", "421", replies[R421])
		|| 1);
      memset(buff, 0, 4096);
    }
  close(fd);
  if (rd < 0)
    return (send_message(CLI_SOCK(work), "%s %s", "451", replies[R451]));
  return (send_message(CLI_SOCK(work), "%s %s", "226", replies[R226]));
}

static int	openFile(t_work *work, const char *file, int *fd)
{
  char		*fullpath;

  if (create_full_path(work, &fullpath, file))
    return (send_message(CLI_SOCK(work), "%s %s", "421", replies[R421]) || 1);
  if (access(fullpath, F_OK) == -1 ||
      ((*fd = open(fullpath, O_RDONLY)) < 0))
    {
      free(fullpath);
      return (send_message(CLI_SOCK(work), "%s %s", "550", replies[R550]));
    }
  free(fullpath);
  return (0);
}

int		exec_retr_command(t_work *work, char *command)
{
  char		*line;
  int		fd;

  if (work->user == -1)
    return (send_message(CLI_SOCK(work), "%s %s", "530", replies[R530]));
  if (!work->pasv_on && !work->port_on)
    return (send_message(CLI_SOCK(work), "%s %s", "425", replies[R425]));
  strtok(command, " ");
  line = strtok(NULL, " ");
  if (!line)
    return (send_message(CLI_SOCK(work), "%s %s", "501", replies[R501]));
  if (openFile(work, line, &fd) || start_upload_to_client(work, fd))
    return (close_datasocket(work) || 1);
  return (close_datasocket(work));
}
