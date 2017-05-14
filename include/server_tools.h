/*
** server_tools.h for  in /home/brout_m/rendu/system/PSU_2016_myftp
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun May 14 16:26:00 2017 brout_m
** Last update Sun May 14 16:26:10 2017 brout_m
*/
#ifndef SERVER_TOOLS_H_
# define SERVER_TOOLS_H_
# include "types.h"

int close_datasocket(t_work *work);
int create_full_path(t_work *work, char **out, const char *file);

#endif /* !SERVER_TOOLS_H */
