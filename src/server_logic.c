/*
** server_logic.c in /home/brout_m/rendu/system/PSU_2016_myftp/src
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Mon May  8 13:54:27 2017 brout_m
** Last update Sun May 14 16:57:38 2017 brout_m
*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "commands.h"
#include "get_command.h"

static t_queue		*gl_root = NULL;

static void		free_list()
{
  t_queue		*cur;
  t_queue		*tmp;

  cur = gl_root;
  while (cur)
    {
      free(cur->str);
      tmp = cur->next;
      free(cur);
      cur = tmp;
    }
}

static int		process_read(t_client const *client)
{
  char			*raw_cmd;

  if (!(raw_cmd = get_raw_command(client->sock)))
    return (1);
  return (add_raw_command(&gl_root, raw_cmd));
}

static t_command gl_commands[35] =
  {
    {"QUIT", 4, exec_quit_command},
    {"USER", 4, exec_user_command},
    {"PASS", 4, exec_password_command},
    {"CWD", 3, exec_cwd_command},
    {"CDUP", 4, exec_cdup_command},
    {"DELE", 4, exec_delete_command},
    {"PWD", 3, exec_pwd_command},
    {"PASV", 4, exec_pasv_command},
    {"PORT", 4, exec_port_command},
    {"HELP", 4, exec_help_command},
    {"NOOP", 4, exec_noop_command},
    {"RETR", 4, exec_retr_command},
    {"STOR", 4, exec_stor_command},
    {"LIST", 4, exec_list_command},
    {"SYST", 4, exec_syst_command},
    {"ACCT", 4, exec_unknown_command},
    {"SMNT", 4, exec_unknown_command},
    {"REIN", 4, exec_unknown_command},
    {"TYPE", 4, exec_unknown_command},
    {"STRU", 4, exec_unknown_command},
    {"MODE", 4, exec_unknown_command},
    {"STOU", 4, exec_unknown_command},
    {"APPE", 4, exec_unknown_command},
    {"ALLO", 4, exec_unknown_command},
    {"RNFR", 4, exec_unknown_command},
    {"RNTO", 4, exec_unknown_command},
    {"SMNT", 4, exec_unknown_command},
    {"ABOR", 4, exec_unknown_command},
    {"SMNT", 4, exec_unknown_command},
    {"RMD", 3, exec_unknown_command},
    {"MKD", 3, exec_unknown_command},
    {"NLST", 4, exec_unknown_command},
    {"SITE", 4, exec_unknown_command},
    {"STAT", 4, exec_unknown_command},
    {"END", 3, NULL}
  };

static int		process_command(t_work *work)
{
  char			*cmd;
  int			i;
  int			ret;

  while ((cmd = find_command(&gl_root)))
    {
      i = 0;
      while (gl_commands[i].exec != NULL)
	{
	  if (!strncmp(gl_commands[i].command, cmd, gl_commands[i].len))
	    {
	      ret = gl_commands[i].exec(work, cmd);
	      free(cmd);
	      return (ret);
	    }
	  ++i;
	}
      free(cmd);
    }
  return (exec_error_command(work, NULL));
}

static int		init_work(t_client *server, t_client *client,
				  char *path, t_work *work)
{
  work->client = client;
  work->server = server;
  bzero(&work->data.addr, ADDR_SIZE);
  work->data.sock = -1;
  work->data.size = ADDR_SIZE;
  work->user = -1;
  if (!(work->path = strdup("/")))
    return (1);
  work->root_path = path;
  work->pasv_on = false;
  work->port_on = false;
  work->logged = false;
  work->quit = false;
  return (0);
}

int			server_logic(t_client *server,
				     t_client *client,
				     char *path)
{
  t_work		work;

  if (init_work(server, client, path, &work))
    return (EXIT_FAILURE);
  while (!work.quit)
    {
      if (process_read(client) || process_command(&work))
	return (EXIT_FAILURE);
    }
  free_list();
  free(work.path);
  return (EXIT_SUCCESS);
}
