//
// Created by brout_m on 14/05/17.
//

#ifndef SERVER_TOOLS_H_
# define SERVER_TOOLS_H_
# include "types.h"

int close_datasocket(t_work *work);
int create_full_path(t_work *work, char **out, const char *file);

#endif //MYFTP_SERVER_TOOLS_H
