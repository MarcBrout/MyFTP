/*
** command_pwd.c for  in /home/brout_m/rendu/system/PSU_2016_myftp
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun May 14 16:32:03 2017 brout_m
** Last update Sun May 14 16:33:11 2017 brout_m
*/

#include "types.h"
#include "get_command.h"

int		exec_pwd_command(t_work *work, char *command)
{
  (void)command;
  return (send_message(CLI_SOCK(work), "%s \"%s\"", "257", work->path));
}
