//
// Created by brout_m on 11/05/17.
//

#include <unistd.h>
#include "server_init.h"
#include "replies.h"
#include "get_command.h"

char *replies[MAX_REPLIES];

int bind_client_socket(t_client *client, sockaddr_in_t *addr, uint16_t *port, Socket sock)
{
  socklen_t len;

  addr->sin_addr.s_addr = client->addr.sin_addr.s_addr;
  addr->sin_family = AF_INET;
  addr->sin_port = 0;
  if (bind(sock, (const sockaddr_t *)addr, sizeof(*addr)) < 0 ||
      listen(sock, 1) < 0)
    return (close(sock) < 0 || 1);
  len = sizeof(*addr);
  if (getsockname(sock, (sockaddr_t *)addr, &len) < 0)
    return (close(sock) < 0 || 1);
  *port = ntohs(addr->sin_port);
  return (0);
}

int exec_pasv_command(t_work *work, char *command)
{
  Socket data;
  sockaddr_in_t addr;
  uint16_t port;

  if (!work->user)
    return (send_message(CLI_SOCK(work), "%s %s", "530", replies[R530]));
  // TODO: check if i should use server or client addr
  if ((data = create_socket(0)) < 0 ||
      bind_client_socket(work->server, &addr, &port, data))
    return (send_message(CLI_SOCK(work), "%s %s", "421", replies[R421]));

  return (0);
}
