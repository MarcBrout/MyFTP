#include <string.h>
#include <unistd.h>
#include "get_command.h"

int exec_password_command(t_work *work, char *command)
{
  (void)command;
  (void)work;
  return (0);
}

int exec_user_command(t_work *work, char *command)
{
  char *value;

  strtok(command, " ");
  value = strtok(NULL, " ");
  if (value)
  {
    if (!strcmp(value, "Anonymous"))
      return (send_message(CLI_SOCK(work), 2, "230",
                           "User logged in, proceed."));
  }
  else
    return (send_message(CLI_SOCK(work), 2, "501",
                         "Syntax error in parameters or arguments."));
  return (0);
}