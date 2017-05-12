#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"

char *get_raw_command(Socket sock)
{
  ssize_t ret;
  char *cmd;
  size_t pos;

  if (!(cmd = calloc(MAX_PAGE_SIZE, 1)))
    return (NULL);
  pos = 0;
  while ((ret = read(sock, &cmd[pos], MAX_PAGE_SIZE - 1)) == MAX_PAGE_SIZE - 1)
  {
    pos += MAX_PAGE_SIZE;
    if (!(cmd = realloc(cmd, pos + MAX_PAGE_SIZE)))
      return (NULL);
    bzero(&cmd[pos], MAX_PAGE_SIZE);
    --pos;
  }
  if (ret == -1)
    return (NULL);
  return (cmd);
}

int add_raw_command(t_queue **root, char *str)
{
  t_queue *node;
  t_queue *cur;

  if (str)
  {
    if (!(node = malloc(sizeof(t_queue))))
      return (1);
    node->str = str;
    node->next = NULL;
    if (!*root)
    {
      *root = node;
    }
    else
    {
      cur = *root;
      while (cur->next)
        cur = cur->next;
      cur->next = node;
    }
  }
  return (0);
}
