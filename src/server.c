//
// Created by brout_m on 08/05/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "server_init.h"
#include "server_listener.h"

static bool isOver = false;

int parse_args(const char *path)
{
  DIR *dir;

  dir = opendir(path);
  if (!dir)
  {
    perror("");
    fprintf(stderr, "A problem occurred while opening folder: %s\n", path);
    return (1);
  }
  closedir(dir);
  return (0);
}

int start_server(uint16_t const port, char *path)
{
  t_client server;
  t_client new;

  if ((server.sock = init_server(port)) < 0)
    return (1);
  while (!isOver)
  {
    if (accept_connections(&new, server.sock))
    {
      printf("Splitting\n");
      server_split(&server, &new, path);
    }
    waitpid(-1, NULL, WNOHANG);
    usleep(500);
  }
  while (!waitpid(-1, NULL, WNOHANG));
  return (close_socket(server.sock));
}

static inline void setOver(int sig_no)
{
  (void)sig_no;
  isOver = true;
}

int main(int ac, char **av)
{
  uint16_t port;
  struct sigaction action;

  if (ac != 3)
  {
    fprintf(stderr, "Usage: %s [PORT] [PATH]\n", av[0]);
    return (EXIT_FAILURE);
  }
  port = (uint16_t)atoi(av[1]);
  bzero(&action, sizeof(struct sigaction));
  action.sa_handler = &setOver;
  action.sa_flags = SA_SIGINFO;
  sigaction(SIGINT, &action, NULL);
  signal(SIGPIPE, SIG_IGN);
  if (parse_args(av[2]) ||
      start_server(port, av[2]))
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}