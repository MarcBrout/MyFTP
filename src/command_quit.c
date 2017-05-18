/*
** command_quit.c for  in /home/brout_m/rendu/system/PSU_2016_myftp
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun May 14 16:05:37 2017 brout_m
** Last update Thu May 18 16:16:48 2017 brout_m
*/
#include <unistd.h>
#include "types.h"
#include "get_command.h"
#include "replies.h"

const char *replies[MAX_REPLIES];

int exec_quit_command(t_work *work, char *command)
{
  (void)command;
  work->quit = true;
  return (send_message(CLI_SOCK(work), "%s %s", "221", replies[R221]));
}
