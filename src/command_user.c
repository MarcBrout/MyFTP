#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "types.h"

int exec_password_command(t_work *work, char *command)
{
  (void)command;
  (void)work;
  return (0);
}

int exec_user_command(t_work *work, char *command)
{
  char *value;

  printf("USER TEST\n");
  strtok(command, " ");
  while ((value = strtok(NULL, " ")))
  {
    if (!strcmp(value, "Anonymous"))
    {
      printf("ANONYMOUS\n");
      if (write(work->client->sock, "230\r\n", 5) == -1)
        return (1);
    }
  }
  return (0);
}