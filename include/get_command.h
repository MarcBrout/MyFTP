#ifndef GET_COMMAND_H
# define GET_COMMAND_H

#include "types.h"

char *get_raw_command(Socket sock);
int add_raw_command(t_queue **root, char *raw);
char *find_command(t_queue **root);

#endif /* !MYFTP_GET_COMMAND_H */
