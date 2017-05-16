/*
** command_pasv.c for  in /home/brout_m/rendu/system/PSU_2016_myftp
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun May 14 16:04:15 2017 brout_m
** Last update Sun May 14 16:30:29 2017 brout_m
*/
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include "server_tools.h"
#include "server_init.h"
#include "replies.h"
#include "get_command.h"

char const *replies[MAX_REPLIES];

static int	split_ip(char ips[4][4], char *ip)
{
  int		i;
  char		*token;

  i = 0;
  token = strtok(ip, ".");
  while (token && i < 4)
    {
      memset(ips[i], 0, 4);
      strcat(ips[i], token);
      token = strtok(NULL, ".");
      ++i;
    }
  return (i != 4);
}

static int	send_ip(t_work *work, char *ip, uint16_t port)
{
  char		ips[4][4];

  if (split_ip(ips, ip))
    return (send_message(CLI_SOCK(work), "%s %s", "421", replies[R421]) || 1);
  return (send_message(CLI_SOCK(work),
                       "%s %s (%s,%s,%s,%s,%d,%d)", "227", replies[R227],
                       ips[0], ips[1], ips[2], ips[3],
		       port / 256, port % 256));
}

static int	bind_client_socket(sockaddr_in_t *addr,
				   uint16_t *port,
				   Socket sock)
{
  socklen_t	len;

  addr->sin_addr.s_addr = htonl(INADDR_ANY);
  addr->sin_family = AF_INET;
  addr->sin_port = 0;
  if (bind(sock, (const sockaddr_t *)addr, sizeof(*addr)) < 0 ||
      listen(sock, 1) < 0)
    return (close(sock) < 0 || 1);
  len = sizeof(*addr);
  getsockname(sock, (sockaddr_t*)addr, &len);
  *port = ntohs(addr->sin_port);
  return (0);
}

static int	accept_client(t_work *work)
{
  work->data.size = ADDR_SIZE;
  if ((work->data_socket = accept(work->data.sock,
                                  (struct sockaddr*)&work->data.addr,
				  &work->data.size)) < 0)
    return (send_message(CLI_SOCK(work), "%s %s", "421", replies[R421]) ||
            close_datasocket(work) || 1);
  work->pasv_on = true;
  return (0);
}

int		exec_pasv_command(t_work *work, char *command)
{
  socklen_t	len;
  uint16_t	port;

  (void)command;
  if (work->user == -1)
    return (send_message(CLI_SOCK(work), "%s %s", "530", replies[R530]));
  if ((work->port_on || work->pasv_on) && close_datasocket(work))
    return (send_message(CLI_SOCK(work), "%s %s", "421", replies[R421]) || 1);
  if ((work->data.sock = create_socket(0)) < 0 ||
      bind_client_socket(&work->data.addr, &port, work->data.sock))
    return (send_message(CLI_SOCK(work), "%s %s", "421", replies[R421]) || 1);
  len = sizeof(work->client->addr);
  getsockname(CLI_SOCK(work), (sockaddr_t *)&work->client->addr, &len);
  if (send_ip(work, inet_ntoa(work->client->addr.sin_addr), port))
    return (close_datasocket(work) || 1);
  return (accept_client(work));
}
