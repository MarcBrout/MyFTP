//
// Created by brout_m on 12/05/17.
//

#include <unistd.h>
#include "types.h"

int exec_syst_command(t_work *work, char *command)
{
  (void)command;
  if (write(work->client->sock, "215 UNIX type: L8\r\n", 19) < 0)
    return (1);
  return (0);
}