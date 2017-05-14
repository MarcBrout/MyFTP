/*
** server_init.c for  in /home/brout_m/rendu/system/PSU_2016_myftp
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun May 14 16:19:25 2017 brout_m
** Last update Sun May 14 16:20:41 2017 brout_m
*/
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "server_init.h"

Socket			create_socket(int flag)
{
  Socket		sock;
  struct protoent	*pe;
  int			ok;

  ok = 1;
  pe = getprotobyname("TCP");
  if (pe == NULL)
    return (-1);
  if ((sock = socket(AF_INET, SOCK_STREAM | flag, pe->p_proto)) == -1)
    {
      perror("");
      fprintf(stderr, "Server Socket creation error occurred\n");
    }
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &ok, sizeof(int));
  return (sock);
}

int			close_socket(Socket sock)
{
  if (close(sock) == -1)
    {
      perror("");
      fprintf(stderr, "Error while closing server socket\n");
    }
  return (1);
}

static int		bind_socket(sockaddr_in_t const *addr, Socket sock)
{
  if (bind(sock, (sockaddr_t const *)addr, sizeof(sockaddr_in_t)) < 0)
    {
      perror("");
      fprintf(stderr, "Server Socket binding error occurred\n");
      return (close_socket(sock));
    }
  return (0);
}

static int		start_listening(Socket sock)
{
  if (listen(sock, LISTEN_QUEUE) < 0)
    {
      perror("");
      fprintf(stderr, "Cannot listen on socket\n");
      return (close_socket(sock));
    }
  return (0);
}

Socket			init_server(uint16_t port)
{
  sockaddr_in_t addr;
  Socket sock;

  bzero(&addr, sizeof(addr));
  sock = create_socket(SOCK_NONBLOCK);
  if (sock < 0)
    return (-1);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  if (bind_socket(&addr, sock) || start_listening(sock))
    return (-1);
  return (sock);
}
