#ifndef SERVER_LISTENER_H_
# define SERVER_LISTENER_H_

#include "types.h"

int accept_connections(t_client *, Socket);
int server_split(t_client *,t_client *, char *);

#endif /* MYFTP_SERVER_LISTENER_H_ */
