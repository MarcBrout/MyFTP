//
// Created by brout_m on 11/05/17.
//

#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include "get_command.h"
#include "replies.h"

char *replies[MAX_REPLIES];

static int check_dir(t_work *work, char *path)
{
  char *fullpath;
  DIR *dir;

  if (!(fullpath = calloc(strlen(work->root_path) + strlen(path) + 1, 1)))
    return (send_message(CLI_SOCK(work), "%s %s", "451", replies[R451]));
  strcat(fullpath, work->root_path);
  strcat(fullpath, path);
  if ((dir = opendir(fullpath)))
  {
    free(fullpath);
    free(work->path);
    if (!(work->path = strdup(path)))
    {
      closedir(dir);
      return (send_message(CLI_SOCK(work), "%s %s", "451", replies[R451]));
    }
    if (path[strlen(path) - 1] == '/' && strlen(path) > 1)
      path[strlen(path) - 1] = 0;
    closedir(dir);
    return (send_message(CLI_SOCK(work), "%s \"%s\"", "257", path));
  }
  free(fullpath);
  closedir(dir);
  return (send_message(CLI_SOCK(work), "%s %s", "550", replies[R550]));
}

static int compute_dir(t_work *work, char *path_to_add)
{
  char *fullpath;

  if (!(fullpath = calloc(strlen(work->path) + strlen(path_to_add) + 2, 1)))
    return (send_message(CLI_SOCK(work), "%s %s", "451", replies[R451]));
  strcat(fullpath, work->path);
  if (strlen(work->path) > 1)
    strcat(fullpath, "/");
  strcat(fullpath, path_to_add);
  return (check_dir(work, fullpath));
}

int cdup(t_work *work, char *command)
{
  char *pos;

  (void)command;
  if (strlen(work->path) == 1)
    return (send_message(CLI_SOCK(work), "%s %s", "550", replies[R550]));
  pos = strrchr(work->path, '/');
  if (pos != NULL)
  {
    if (pos == work->path)
      pos[1] = 0;
    else
      *pos = 0;
  }
  return (0);
}

int exec_cdup_command(t_work *work, char *command)
{
  if (cdup(work, command))
    return (1);
  return (send_message(CLI_SOCK(work), "%s %s", "200", replies[R200]));
}

int exec_cwd_command(t_work *work, char *command)
{
  char *path;

  strtok(command, " ");
  if ((path = strtok(NULL, " ")))
  {
    if (!strcmp(path, ".."))
    {
      if (cdup(work, command))
        return (1);
      return (send_message(CLI_SOCK(work), "%s \"%s\"", "257", work->path));
    }
    if (path[0] == '/')
      return (check_dir(work, path) == 1);
    return (compute_dir(work, path));
  }
  return (send_message(CLI_SOCK(work), "%s %s", "501", replies[R501]));
}

int exec_pwd_command(t_work *work, char *command)
{
  (void)command;
  return (send_message(CLI_SOCK(work), "%s \"%s\"", "257", work->path));
}