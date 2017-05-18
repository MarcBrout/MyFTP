/*
** command_syst.c for  in /home/brout_m/rendu/system/PSU_2016_myftp
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun May 14 16:06:43 2017 brout_m
** Last update Thu May 18 16:12:17 2017 brout_m
*/
#include "get_command.h"

int exec_syst_command(t_work *work, char *command)
{
  (void)command;
  return (send_message(CLI_SOCK(work), "%s %s", "215", "UNIX type: L8"));
}
