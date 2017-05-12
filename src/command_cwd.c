//
// Created by brout_m on 11/05/17.
//

#include <unistd.h>
#include <string.h>
#include "types.h"

int exec_cwd_command(t_work *work, char *command)
{
  char *path;

  strtok(command, " ");

  (void)work;
  return (0);
}

int exec_cdup_command(t_work *work, char *command)
{
  (void)command;
  (void)work;
  return (0);
}

int exec_pwd_command(t_work *work, char *command)
{
  (void)command;
  if (write(work->client->sock, "257 ", 4) < 0 ||
      write(work->client->sock, work->path, strlen(work->path)) < 0 ||
      write(work->client->sock, "\r\n", 2) < 0)
    return (1);
  return (0);
}
