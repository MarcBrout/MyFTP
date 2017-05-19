/*
** get_command.c for  in /home/brout_m/rendu/system/PSU_2016_myftp
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun May 14 16:08:22 2017 brout_m
** Last update Fri May 19 11:32:09 2017 brout_m
*/
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "types.h"
#include "get_command.h"

int		send_message(Socket sock, const char *format, ...)
{
  int		ret;
  va_list	list;

  va_start(list, format);
  lock();
  if (vdprintf(sock, format, list) < 0)
    {
      va_end(list);
      unlock();
      return (1);
    }
  va_end(list);
  ret = write(sock, "\r\n", 2);
  unlock();
  return (ret < 0);
}

static char	*concat(t_queue **root, char **dest)
{
  t_queue	*save;
  size_t	len;
  char		*pos;

  if (*dest)
    {
      len = *dest ? strlen((*root)->str) + strlen(*dest) :
	strlen((*root)->str);
      if (!(*dest = realloc(*dest, len + 1)))
	return (NULL);
      strcat(*dest, (*root)->str);
      free((*root)->str);
    }
  else
    {
      *dest = (*root)->str;
    }
  save = (*root)->next;
  free((*root));
  *root = save;
  if ((pos = strstr(*dest, "\r\n")))
    *pos = 0;
  return (*dest);
}

static char	*cut_str(char **dest, char **str)
{
  char		*pos;
  char		*str1;
  char		*str2;
  size_t	len;

  pos = strstr(*str, "\r\n");
  len = *dest ? strlen(*dest) + strlen(*str) : strlen(*str);
  len -= strlen(pos);
  if (!(str1 = calloc(len + 1, 1)) || !(str2 = strdup(pos + 2)))
    return (NULL);
  if (*dest)
    strcpy(str1, *dest);
  strncat(str1, *str, strlen(*str) - strlen(pos));
  if (*dest)
    free(*dest);
  free(*str);
  *str = str2;
  *dest = str1;
  return (*dest);
}

static char	*build_command(t_queue **root, t_queue *pos)
{
  char		*str;

  str = NULL;
  while ((*root)->next != pos && *root != pos)
    {
      if (concat(root, &str))
	return (NULL);
    }
  if (strlen(strstr(pos->str, "\r\n")) == 2)
    return (concat(root, &str));
  return (cut_str(&str, &pos->str));
}

char		*find_command(t_queue **root)
{
  t_queue	*cur;

  cur = *root;
  while (cur)
    {
      if (strstr(cur->str, "\r\n"))
	return (build_command(root, cur));
      cur = cur->next;
    }
  return (NULL);
}
