#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "types.h"
#include "server_logic.h"

int accept_connections(t_client *client, Socket sock)
{
  bzero(&client->addr, sizeof(client->addr));
  client->size = sizeof(client->addr);
  client->sock = accept(sock, (sockaddr_t *)&client->addr, &client->size);
  if (client->sock == -1)
  {
    if (errno != EAGAIN && errno != EWOULDBLOCK)
    {
      perror("");
      fprintf(stderr, "Error occured while accepting connection\n");
    }
    return (0);
  }
  printf("client socket accepted = %d\n", client->sock);
  write(client->sock, "220\r\n", 5);
  return (1);
}

int server_split(t_client *server, t_client *client, char *path)
{
  pid_t pid;

  pid = fork();
  if (!pid)
  {
    close(server->sock);
    _exit(server_logic(server, client, path));
  }
  else if (pid < 0)
  {
    perror("");
    fprintf(stderr, "Error occurred while forking");
    return (1);
  }
  close(client->sock);
  return (0);
}