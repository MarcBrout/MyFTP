/*
** command_noop.c for  in /home/brout_m/rendu/system/PSU_2016_myftp
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun May 14 16:04:05 2017 brout_m
** Last update Sun May 14 16:07:46 2017 brout_m
*/
#include <unistd.h>
#include <get_command.h>
#include "types.h"

int exec_noop_command(t_work *work, char *command)
{
  (void)command;
  return (send_message(CLI_SOCK(work), "%s %s", "200", "noop"));
}
