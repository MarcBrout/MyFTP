//
// Created by brout_m on 14/05/17.
//

#include <unistd.h>
#include <string.h>
#include "types.h"

int close_datasocket(t_work *work)
{
  if (close(work->data_socket))
    return (1);
  work->data_socket = -1;
  work->pasv_on = work->port_on = false;
  bzero(&work->data.addr, ADDR_SIZE);
  return (0);
}