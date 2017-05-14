/*
** command_quit.c for  in /home/brout_m/rendu/system/PSU_2016_myftp
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun May 14 16:05:37 2017 brout_m
** Last update Sun May 14 16:07:28 2017 brout_m
*/
#include <unistd.h>
#include "types.h"

int exec_quit_command(t_work *work, char *command)
{
  (void)command;
  work->quit = true;
  if (write(work->client->sock, "221\r\n", 5) < 0)
    return (1);
  return (0);
}
