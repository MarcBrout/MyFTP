//
// Created by brout_m on 11/05/17.
//

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "replies.h"
#include "get_command.h"

const char *replies[MAX_REPLIES];

int start_delete(t_work*work, const char *path)
{
  char *fullpath;
  char *fstr;

  fstr = path[0] == '/' ? "%s%s" : "%s/%s";
  asprintf(&fullpath, fstr, work->root_path, path);
  if (access(fullpath, F_OK) != -1)
  {
    if (remove(fullpath))
      return (send_message(CLI_SOCK(work), "%s %s", "450", replies[R450]) || 1);
    return (send_message(CLI_SOCK(work), "%s %s", "250", replies[R250]));
  }
  return (send_message(CLI_SOCK(work), "%s %s", "550", replies[R550]));
}

int exec_delete_command(t_work *work, char *command)
{
  char *path;

  strtok(command, " ");
  if (work->user < 0)
    return (send_message(CLI_SOCK(work), "%s %s", "530", replies[R530]));
  if (!(path = strtok(NULL, " ")))
    return (send_message(CLI_SOCK(work), "%s %s%", "501", replies[R501]));
  if (start_delete(work, path))
    return (1);
  return (0);
}