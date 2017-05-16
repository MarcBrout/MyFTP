/*
** command_stor.c for  in /home/brout_m/rendu/system/PSU_2016_myftp
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun May 14 16:06:16 2017 brout_m
** Last update Sun May 14 16:37:28 2017 brout_m
*/
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_command.h"
#include "replies.h"
#include "server_tools.h"

const char *replies[MAX_REPLIES];

int		start_download_from_client(t_work *work, int fd)
{
  char		buff[4096];
  ssize_t	rd;

  if (fd < 0)
    return (send_message(CLI_SOCK(work), "%s %s", "550", replies[R550]));
  if (send_message(CLI_SOCK(work), "%s %s", "125", replies[R125]))
    return (1);
  memset(buff, 0, 4096);
  while ((rd = read(work->data_socket, buff, 4095)) > 0)
    {
      if (write(fd, buff, rd) < 0)
	return (send_message(CLI_SOCK(work), "%s %s", "421", replies[R421])
		|| 1);
      memset(buff, 0, 4096);
    }
  close(fd);
  if (rd < 0)
    return (send_message(CLI_SOCK(work), "%s %s", "421", replies[R421])
	    || 1);
  return (send_message(CLI_SOCK(work), "%s %s", "226", replies[R226]));
}

int		create_file(t_work *work, const char *file, int *fd)
{
  char		*fullpath;

  if (create_full_path(work, &fullpath, file))
    return (send_message(CLI_SOCK(work), "%s %s", "421", replies[R421])
	    || 1);
  *fd = creat(fullpath, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
  free(fullpath);
  return (0);
}

int		exec_stor_command(t_work *work, char *command)
{
  char		*file;
  int		fd;

  if (work->user == -1)
    return (send_message(CLI_SOCK(work), "%s %s", "530", replies[R530]));
  if (!work->pasv_on && !work->port_on)
    return (send_message(CLI_SOCK(work), "%s %s", "425", replies[R425]));
  strtok(command, " ");
  if (!(file = strtok(NULL, " ")))
    return (send_message(CLI_SOCK(work), "%s %s", "501", replies[R501]));
  if (create_file(work, file, &fd) ||
      start_download_from_client(work, fd))
    return (close_datasocket(work) || 1);
  return (close_datasocket(work));
}
