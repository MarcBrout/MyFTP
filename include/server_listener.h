/*
** server_listener.h for  in /home/brout_m/rendu/system/PSU_2016_myftp
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun May 14 16:25:35 2017 brout_m
** Last update Sun May 14 16:39:41 2017 brout_m
*/
#ifndef SERVER_LISTENER_H_
# define SERVER_LISTENER_H_

#include "types.h"

int accept_connections(t_client *, Socket);
int server_split(t_client *, t_client *, char *);

#endif /* !SERVER_LISTENER_H_ */
