/*
** command_error.c for  in /home/brout_m/rendu/system/PSU_2016_myftp
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun May 14 16:02:42 2017 brout_m
** Last update Sun May 14 16:10:53 2017 brout_m
*/
#include "replies.h"
#include "get_command.h"

char const *replies[MAX_REPLIES];

int	exec_unknown_command(t_work *work, char *command)
{
  (void)command;
  return (send_message(CLI_SOCK(work), "%s %s", "502", replies[R502]));
}

int	exec_error_command(t_work *work, char *command)
{
  (void)command;
  return (send_message(CLI_SOCK(work), "%s %s", "500", replies[R500]));
}
