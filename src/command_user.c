/*
** command_user.c for  in /home/brout_m/rendu/system/PSU_2016_myftp
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun May 14 16:06:55 2017 brout_m
** Last update Sun May 14 16:15:25 2017 brout_m
*/
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "replies.h"
#include "get_command.h"

char const		*replies[MAX_REPLIES];
static t_account const	users[2] = {
    {"Anonymous", ""},
    {"Dieu", "42"}
};

static int   get_user(t_work *work)
{
  int     user;

  user = 0;
  work->user = -1;
  while (user < 2)
  {
    if (!strcmp(work->user_name, users[user].user))
    {
      work->user = user;
      break;
    }
    ++user;
  }
  return (user);
}

int		exec_password_command(t_work *work, char *command)
{
  char		*value;
  int user;

  strtok(command, " ");
  value = strtok(NULL, " ");
  user = get_user(work);
  if (user == 2)
    return (send_message(CLI_SOCK(work), "%s %s", "530", replies[R530]));
  if (!user)
    return (send_message(CLI_SOCK(work), "%s %s", "230", replies[R230]));
  if (value && !strcmp(value, users[work->user].password))
    {
      work->logged = true;
      return (send_message(CLI_SOCK(work), "%s %s", "230", replies[R230]));
    }
  return (send_message(CLI_SOCK(work), "%s %s", "530", replies[R530]));
}

int		exec_user_command(t_work *work, char *command)
{
  char		*value;

  strtok(command, " ");
  value = strtok(NULL, " ");
  work->logged = false;
  if (value)
  {
    if (!(work->user_name = strdup(value)))
      return (send_message(CLI_SOCK(work), "%s %s", "421", replies[R421]));
  }
  return (send_message(CLI_SOCK(work), "%s %s", "331", replies[R331]));
}
