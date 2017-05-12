//
// Created by brout_m on 11/05/17.
//

#include <unistd.h>
#include "types.h"

int exec_quit_command(t_work *work, char *command)
{
  (void)command;
  work->quit = true;
  if (write(work->client->sock, "221\r\n", 5) < 0)
    return (1);
  return (0);
}