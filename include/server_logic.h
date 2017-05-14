/*
** server_logic.h for  in /home/brout_m/rendu/system/PSU_2016_myftp
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun May 14 16:25:45 2017 brout_m
** Last update Sun May 14 16:25:53 2017 brout_m
*/
#ifndef SERVER_LOGIC_H_
# define SERVER_LOGIC_H_

# include "types.h"

int server_logic(t_client *server,
                 t_client *client, char *path);

#endif /* !SERVER_LOGIC_H */
