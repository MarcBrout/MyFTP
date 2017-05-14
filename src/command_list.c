//
// Created by brout_m on 11/05/17.
//

#define _GNU_SOURCE
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include "server_tools.h"
#include "replies.h"
#include "get_command.h"

char const *replies[MAX_REPLIES];

bool isReadable(const char *str)
{
  return (strcmp(str, ".") && strcmp(str, ".."));
}

int list_folder(t_work *work, DIR *dir)
{
  struct dirent *file;

  if (send_message(CLI_SOCK(work), "%s %s", "150", replies[R150]))
    return (1);
  while ((file = readdir(dir)))
  {
    if (isReadable(file->d_name))
    {
      if (write(work->data_socket, file->d_name, strlen(file->d_name)) < 0 ||
          write(work->data_socket, "\r\n", 2) < 0)
        return (send_message(CLI_SOCK(work), "%s %s", "451", replies[R451]) || 1);
    }
  }
  closedir(dir);
  return (send_message(CLI_SOCK(work), "%s %s", "226", replies[R226]));
}

int list_file(t_work *work, const char *path)
{
  char *msg;

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

int launch_list(t_work *work, const char *path)
{
  DIR *dir;
  char *fullpath;
  char *fstr;
  int ret;

  fullpath = NULL;
  if (path)
  {
    fstr = path[0] == '/' ? "%s%s" : "%s/%s";
    asprintf(&fullpath, fstr, work->root_path, path);
  }
  else
    asprintf(&fullpath, "%s%s", work->root_path, work->path);
  if (!fullpath)
    return (send_message(CLI_SOCK(work), "%s %s", "421", replies[R421]) || 1);
  if ((dir = opendir(fullpath)))
  {
    free(fullpath);
    return (list_folder(work, dir));
  }
  ret = list_file(work, fullpath);
  free(fullpath);
  return (ret);
}

int exec_list_command(t_work *work, char *command)
{
  if (work->user < 0)
    return (send_message(CLI_SOCK(work), "%s %s", "530", replies[R530]));
  if (!work->pasv_on && !work->port_on)
    return (send_message(CLI_SOCK(work), "%s %s", "425", replies[R425]));
  strtok(command, " ");
  if (launch_list(work, strtok(NULL, " ")))
    return (close_datasocket(work) || 1);
  return (close_datasocket(work));
}
