/*
** command_help.c for  in /home/brout_m/rendu/system/PSU_2016_myftp
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun May 14 16:02:58 2017 brout_m
** Last update Sun May 14 16:35:17 2017 brout_m
*/
#include <string.h>
#include "get_command.h"
#include "replies.h"

const char		*replies[MAX_REPLIES];
static const char	*help_line =
  "USER PASS CWD CDUP QUIT DELE PWD PASV PORT "
  "HELP NOOP RETR STOR LIST";
static t_help		help_desc[14] =
  {
    {"USER", "USER <SP> <username> <CRLF> : Specify user for "
     "authentication"},
    {"PASS", "PASS <SP> <password> <CRLF> : Specify password for "
     "authentication"},
    {"CWD", "CWD <SP> <pathname> <CRLF> : Change working directory"},
    {"CDUP", "CDUP <CRLF> : Change working directory to parent directory"},
    {"QUIT", "QUIT <CRLF> : Disconnection"},
    {"DELE", "DELE <SP> <pathname> <CRLF> : Delete file on the server"},
    {"PWD", "PWD <CRLF> : Print working directory"},
    {"PASV", "PASV <CRLF> : Enable \"passive\" mode for data transfer"},
    {"PORT", "PORT <SP> <host-port> <CRLF> : Enable \"active\" "
     "mode for data transfer"},
    {"HELP", "HELP [<SP> <string>] <CRLF> : List available commands"},
    {"NOOP", "NOOP <CRLF> : Do nothing"},
    {"RETR", "RETR <SP> <pathname> <CRLF> : Download file from "
     "server to client"},
    {"STOR", "STOR <SP> <pathname> <CRLF> : Upload file from "
     "client to server"},
    {"LIST", "LIST [<SP> <pathname>] <CRLF> : List files in "
     "the current working directory"}
  };

int			exec_help_command(t_work *work, char *command)
{
  int			i;
  char			*cmd;

  strtok(command, " ");
  if (!(cmd = strtok(NULL, " ")))
    return (send_message(CLI_SOCK(work), "%s %s", "214", help_line));
  else
    {
      i = 0;
      while (i < 14)
	{
	  if (!strcmp(cmd, help_desc[i].cmd))
	    return (send_message(CLI_SOCK(work), "%s %s", "214",
				 help_desc[i].desc));
	  ++i;
	}
    }
  return (send_message(CLI_SOCK(work), "%s %s", "500", replies[R500]));
}
