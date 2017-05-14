/*
** server_init.h for  in /home/brout_m/rendu/system/PSU_2016_myftp
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun May 14 16:24:59 2017 brout_m
** Last update Sun May 14 16:25:03 2017 brout_m
*/
#ifndef SERVER_INIT_H_
# define SERVER_INIT_H_

# include <stdbool.h>
# include <stdint.h>
# include "types.h"

# define LISTEN_QUEUE 10

Socket create_socket(int);
int close_socket(Socket sock);
int init_server(uint16_t const);

#endif /* !SERVER_INIT_H_ */
