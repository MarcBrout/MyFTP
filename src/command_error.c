//
// Created by brout_m on 11/05/17.
//

#include "replies.h"
#include "get_command.h"

char *replies[MAX_REPLIES];

int exec_unknown_command(t_work *work, char *command)
{
  (void)command;
  return (send_message(CLI_SOCK(work), "%s %s", "502", replies[R502]));
}

int exec_error_command(t_work *work, char *command)
{
  (void)command;
  return (send_message(CLI_SOCK(work), "%s %s", "500", replies[R500]));
}