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
