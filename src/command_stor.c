/*
** command_stor.c for  in /home/brout_m/rendu/system/PSU_2016_myftp
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun May 14 16:06:16 2017 brout_m
** Last update Fri May 19 11:31:44 2017 brout_m
*/
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <pthread.h>
#include "get_command.h"
#include "replies.h"
#include "server_tools.h"

const char	*replies[MAX_REPLIES];

static int	start_download_from_client(t_work *work, int fd)
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
	return (send_message(CLI_SOCK(work), "%s %s", "451", replies[R451])
		|| 1);
      memset(buff, 0, 4096);
    }
  close(fd);
  if (rd < 0)
    return (send_message(CLI_SOCK(work), "%s %s", "451", replies[R451])
	    || 1);
  return (send_message(CLI_SOCK(work), "%s %s", "226", replies[R226]));
}

static int	create_file(t_work *work, const char *file, int *fd)
{
  char		*fullpath;

  if (create_full_path(work, &fullpath, file))
    return (send_message(CLI_SOCK(work), "%s %s", "451", replies[R451])
	    || 1);
  *fd = creat(fullpath, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
  free(fullpath);
  return (0);
}

static void	*launch_threaded_stor(void *_thdata)
{
  char		*file;
  int		fd;
  t_thdata	*thdata;

  thdata = _thdata;
  strtok(thdata->command, " ");
  if (!(file = strtok(NULL, " ")))
    {
      send_message(CLI_SOCK(thdata->work), "%s %s", "501", replies[R501]);
      free(thdata->command);
      close_datasocket(thdata->work);
      pthread_exit(NULL);
    }
  if (!create_file(thdata->work, file, &fd))
    start_download_from_client(thdata->work, fd);
  free(thdata->command);
  close_datasocket(thdata->work);
  pthread_exit(NULL);
}

int		exec_stor_command(t_work *work, char *command)
{
  if (work->user == -1)
    return (send_message(CLI_SOCK(work), "%s %s", "530", replies[R530]));
  if (!work->pasv_on && !work->port_on)
    return (send_message(CLI_SOCK(work), "%s %s", "425", replies[R425]));
  if (work->pasv_on && accept_client(work))
    return (1);
  if (launch_thread(work, command, launch_threaded_stor))
    return (close_datasocket(work) || 1);
  return (0);
}
