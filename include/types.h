/*
** types.h for  in /home/brout_m/rendu/system/PSU_2016_myftp
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun May 14 16:26:14 2017 brout_m
** Last update Thu May 18 14:06:48 2017 brout_m
*/
#ifndef TYPES_H_
# define TYPES_H_
# define MAX_PAGE_SIZE 4096
# define ADDR_SIZE sizeof(sockaddr_in_t)

# include <netinet/in.h>
# include <stdbool.h>
# include <netdb.h>

typedef int			Socket;
typedef struct sockaddr_in	sockaddr_in_t;
typedef struct sockaddr		sockaddr_t;
typedef struct hostent		hostent_t;

typedef struct			s_account
{
  const char			*user;
  const char			*password;
}				t_account;

typedef struct			s_help
{
  const char			*cmd;
  const char			*desc;
}				t_help;

typedef struct			s_client
{
  Socket			sock;
  sockaddr_in_t			addr;
  socklen_t			size;
}				t_client;

typedef struct			s_queue
{
  char				*str;
  struct s_queue		*next;
}				t_queue;

typedef struct			s_work
{
  t_client			*server;
  t_client			*client;
  t_client			data;
  Socket			data_socket;
  int				user;
  char				*path;
  char				*root_path;
  bool				pasv_on;
  bool				port_on;
  bool				quit;
  bool				logged;
}				t_work;

#endif /* !TYPES_H_ */
