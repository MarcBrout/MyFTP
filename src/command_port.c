/*
** command_port.c for  in /home/brout_m/rendu/system/PSU_2016_myftp
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun May 14 16:05:00 2017 brout_m
** Last update Sun May 14 17:04:06 2017 brout_m
*/
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "server_tools.h"
#include "server_init.h"
#include "get_command.h"
#include "replies.h"

static int	parse_ip(t_work *work,
			 char *command,
			 char **out,
			 uint16_t *port)
{
  uint16_t	ip[6];
  char		*token;
  int		i;

  i = 0;
  strtok(command, " ,");
  *out = NULL;
  while ((token = strtok(NULL, " ,")) && i < 6)
    {
      ip[i] = (uint16_t)atoi(token);
      if (ip[i] > 255)
	return (send_message(CLI_SOCK(work), "%s %s", "501", replies[R501]));
      ++i;
    }
  if (i != 6)
    return (send_message(CLI_SOCK(work), "%s %s", "501", replies[R501]));
  if (asprintf(out, "%u.%u.%u.%u", ip[0], ip[1], ip[2], ip[3]) < 1)
    return (send_message(CLI_SOCK(work), "%s %s", "421", replies[R421]) || 1);
  *port = ip[4] * (uint16_t)256 + ip[5];
  return (0);
}

int		go_active(t_work *work, char *ip, uint16_t port)
{
  if ((work->data_socket = create_socket(0)) < 0)
    return (send_message(CLI_SOCK(work), "%s %s", "421", replies[R421]) || 1);
  memset(&work->data.addr, 0, ADDR_SIZE);
  work->data.addr.sin_addr.s_addr = inet_addr(ip);
  work->data.addr.sin_port = htons(port);
  work->data.addr.sin_family = AF_INET;
  work->data.sock = work->data_socket;
  work->data.size = ADDR_SIZE;
  if (connect(work->data_socket,
	      (const sockaddr_t *)&work->data.addr, ADDR_SIZE) < 0)
    return (send_message(CLI_SOCK(work), "%s %s", "421", replies[R421]) || 1);
  work->port_on = true;
  return (send_message(CLI_SOCK(work), "%s %s", "200", replies[R200]));
}

int		exec_port_command(t_work *work, char *command)
{
  uint16_t	port;
  char		*dest;
  int		ret;

  if (work->user == -1)
    return (send_message(CLI_SOCK(work), "%s %s", "530", replies[R530]));
  if ((work->port_on || work->pasv_on) && close_datasocket(work))
    return (send_message(CLI_SOCK(work), "%s %s", "421", replies[R421]) || 1);
  if (parse_ip(work, command, &dest, &port))
    {
      free(dest);
      return (1);
    }
  if (!dest)
    return (0);
  ret = go_active(work, dest, port);
  free(dest);
  return (ret);
}
