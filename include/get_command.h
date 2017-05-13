#ifndef GET_COMMAND_H
# define GET_COMMAND_H

# define CLI_SOCK(work) work->client->sock
# define SRV_SOCK(work) work->server->sock

# include "types.h"

int send_message(Socket sock, const char *format, ...);
char *get_raw_command(Socket sock);
int add_raw_command(t_queue **root, char *raw);
char *find_command(t_queue **root);

#endif /* !MYFTP_GET_COMMAND_H */
