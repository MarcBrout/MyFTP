/*
** command_list.c for  in /home/brout_m/rendu/system/PSU_2016_myftp
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun May 14 16:03:34 2017 brout_m
** Last update Fri May 19 11:29:37 2017 brout_m
*/
#define _GNU_SOURCE
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <pthread.h>
#include "server_tools.h"
#include "replies.h"
#include "get_command.h"

char const		*replies[MAX_REPLIES];

static int		list_folder(t_work *work, DIR *dir)
{
  struct dirent		*file;

  if (send_message(CLI_SOCK(work), "%s %s", "150", replies[R150]))
    return (1);
  while ((file = readdir(dir)))
    {
      if (strcmp(file->d_name, ".") && strcmp(file->d_name, ".."))
	{
	  if (write(work->data_socket, file->d_name, strlen(file->d_name)) < 0
	      || write(work->data_socket, "\r\n", 2) < 0)
	    return (send_message(CLI_SOCK(work),
				 "%s %s", "451", replies[R451]) || 1);
	}
    }
  closedir(dir);
  return (send_message(CLI_SOCK(work), "%s %s", "226", replies[R226]));
}

static int		list_file(t_work *work, const char *path)
{
  char			*msg;

  if (access(path, F_OK) != -1)
    msg = strrchr(path, '/') + 1;
  else
    msg = "No such file or directory.";
  if (send_message(CLI_SOCK(work), "%s %s", "125", replies[R150]))
    return (1);
  if (write(work->data_socket, msg, strlen(msg)) < 0 ||
      write(work->data_socket, "\r\n", 2) < 0)
    return (send_message(CLI_SOCK(work), "%s %s", "451", replies[R451]) || 1);
  return (send_message(CLI_SOCK(work), "%s %s", "226", replies[R226]));
}

static int		launch_list(t_work *work, const char *path)
{
  DIR			*dir;
  char			*fullpath;
  int			ret;

  fullpath = NULL;
  if (create_full_path(work, &fullpath, path))
    return (send_message(CLI_SOCK(work), "%s %s", "451", replies[R451]) || 1);
  if ((dir = opendir(fullpath)))
    {
      free(fullpath);
      return (list_folder(work, dir));
    }
  ret = list_file(work, fullpath);
  free(fullpath);
  return (ret);
}

static void		*launch_threaded_list(void *_thdata)
{
  t_thdata		*thdata;

  thdata = _thdata;
  strtok(thdata->command, " ");
  launch_list(thdata->work, strtok(NULL, " "));
  close_datasocket(thdata->work);
  free(thdata->command);
  pthread_exit(NULL);
}

int			exec_list_command(t_work *work, char *command)
{
  if (work->user < 0)
    return (send_message(CLI_SOCK(work), "%s %s", "530", replies[R530]));
  if (!work->pasv_on && !work->port_on)
    return (send_message(CLI_SOCK(work), "%s %s", "425", replies[R425]));
  if (work->pasv_on && accept_client(work))
    return (1);
  if (launch_thread(work, command, launch_threaded_list))
    return (close_datasocket(work) || 1);
  return (0);
}
