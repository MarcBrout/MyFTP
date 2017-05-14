/*
** command_syst.c for  in /home/brout_m/rendu/system/PSU_2016_myftp
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun May 14 16:06:43 2017 brout_m
** Last update Sun May 14 16:07:12 2017 brout_m
*/
#include <unistd.h>
#include "types.h"

int exec_syst_command(t_work *work, char *command)
{
  (void)command;
  if (write(work->client->sock, "215 UNIX type: L8\r\n", 19) < 0)
    return (1);
  return (0);
}
