//
// Created by brout_m on 11/05/17.
//

#include <string.h>
#include <stdlib.h>
#include "get_command.h"
#include "replies.h"

static char *parse_ip(char *command)
{
  char *line;
  char *token;
  size_t size;
  int i;

  i = 0;
  strtok(command, " ,");
  line = NULL;
  size = 0;
  while ((token = strtok(NULL, " ,")) && i < 4)
  {
    size += strlen(token);
    if (!(line = realloc(line, size + 1 + 1)))
      return (NULL);
    strcat(line, token);
    if (i < 3)
      strcat(line, ".");
    ++i;
  }
  if (i != 4)
  {
    free(line);
    return (NULL);
  }
  return (line);
}

int exec_port_command(t_work *work, char *command)
{
  char *ip;
  //uint16_t port;
  //Socket data;

  if (work->user == -1)
    return (send_message(CLI_SOCK(work), "%s %s", "530", replies[R530]));
  if (!(ip = parse_ip(command)))
    return (send_message(CLI_SOCK(work), "%s %s", "501", replies[R501]));

  return (0);
}
