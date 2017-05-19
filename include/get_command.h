/*
** get_command.h for  in /home/brout_m/rendu/system/PSU_2016_myftp
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun May 14 16:23:54 2017 brout_m
** Last update Sun May 14 16:25:15 2017 brout_m
*/
#ifndef GET_COMMAND_H
# define GET_COMMAND_H

# define CLI_SOCK(work) work->client->sock

# include "types.h"

int send_message(Socket sock, const char *format, ...);
char *get_raw_command(Socket sock);
int add_raw_command(t_queue **root, char *raw);
char *find_command(t_queue **root);
int accept_client(t_work *work);
int launch_thread(t_work *work, char *command, thread_funct_t fn);
int lock();
int unlock();
int destroy_mutex();

#endif /* !GET_COMMAND_H */
