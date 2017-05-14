/*
** commands.h for  in /home/brout_m/rendu/system/PSU_2016_myftp
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun May 14 16:23:34 2017 brout_m
** Last update Sun May 14 16:25:23 2017 brout_m
*/
#ifndef COMMANDS_H_
# define COMMANDS_H_

# include <stdbool.h>
# include "types.h"

typedef int (*command_exec_t)(t_work *, char *);

typedef struct s_command
{
  char *command;
  size_t len;
  command_exec_t exec;
} t_command;

int exec_user_command(t_work *work, char *command);
int exec_password_command(t_work *work, char *command);
int exec_cwd_command(t_work *work, char *command);
int exec_cdup_command(t_work *work, char *command);
int exec_delete_command(t_work *work, char *command);
int exec_pwd_command(t_work *work, char *command);
int exec_pasv_command(t_work *work, char *command);
int exec_port_command(t_work *work, char *command);
int exec_help_command(t_work *work, char *command);
int exec_noop_command(t_work *work, char *command);
int exec_retr_command(t_work *work, char *command);
int exec_list_command(t_work *work, char *command);
int exec_stor_command(t_work *work, char *command);
int exec_error_command(t_work *work, char *command);
int exec_quit_command(t_work *work, char *command);
int exec_syst_command(t_work *work, char *command);
int exec_unknown_command(t_work *work, char *command);

#endif /* !COMMANDS_H_ */
