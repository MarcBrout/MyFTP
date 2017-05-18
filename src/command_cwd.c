/*
** command_cwd.c for myftp in /home/brout_m/rendu/system/PSU_2016_myftp
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun May 14 16:01:25 2017 brout_m
** Last update Sun May 14 16:35:33 2017 brout_m
*/
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include "get_command.h"
#include "replies.h"

char const *replies[MAX_REPLIES];

static int	check_dir(t_work *work, char *path)
{
  char		*fullpath;
  DIR		*dir;

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
	  return (send_message(CLI_SOCK(work), "%s %s", "451",
			       replies[R451]));
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

static int	compute_dir(t_work *work, char *path_to_add)
{
  char		*fullpath;
  int		ret;

  if (!(fullpath = calloc(strlen(work->path) + strlen(path_to_add) + 2, 1)))
    return (send_message(CLI_SOCK(work), "%s %s", "451", replies[R451]));
  strcat(fullpath, work->path);
  if (strlen(work->path) > 1)
    strcat(fullpath, "/");
  strcat(fullpath, path_to_add);
  ret = check_dir(work, fullpath);
  free(fullpath);
  return (ret);
}

int		cdup(t_work *work, char *command)
{
  char		*pos;

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

int		exec_cdup_command(t_work *work, char *command)
{
  if (work->user == -1)
    return (send_message(CLI_SOCK(work), "%s %s", "530", replies[R530]));
  if (cdup(work, command))
    return (1);
  return (send_message(CLI_SOCK(work), "%s %s", "250", replies[R250]));
}

int		exec_cwd_command(t_work *work, char *command)
{
  char		*path;

  if (work->user == -1)
    return (send_message(CLI_SOCK(work), "%s %s", "530", replies[R530]));
  strtok(command, " ");
  if ((path = strtok(NULL, " ")))
    {
      if (!strcmp(path, ".."))
	{
	  if (cdup(work, command))
	    return (1);
	  return (send_message(CLI_SOCK(work), "%s \"%s\"", "250", replies[R250]));
	}
      if (path[0] == '/')
	return (check_dir(work, path) == 1);
      return (compute_dir(work, path));
    }
  return (send_message(CLI_SOCK(work), "%s %s", "550", replies[R550]));
}
