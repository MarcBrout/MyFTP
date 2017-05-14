#include <string.h>
#include <unistd.h>
#include "replies.h"
#include "get_command.h"

char const *replies[MAX_REPLIES];
static t_account const users[2] = {
    {"Anonymous", ""},
    {"Dieu", "42"}
};

int exec_password_command(t_work *work, char *command)
{
  char *value;

  if (work->user < 0)
    return (send_message(CLI_SOCK(work), "%s %s", "332", replies[R332]));
  if (work->user == 0)
    return (send_message(CLI_SOCK(work), "%s %s", "230", replies[R230]));
  strtok(command, " ");
  value = strtok(NULL, " ");
  if (value)
  {
    if (!strcmp(value, users[work->user].password))
    {
      work->logged = true;
      return (send_message(CLI_SOCK(work), "%s %s", "230", replies[R230]));
    }
  }
  return (send_message(CLI_SOCK(work), "%s %s", "530", replies[R530]));
}

int exec_user_command(t_work *work, char *command)
{
  char *value;
  int user;

  strtok(command, " ");
  value = strtok(NULL, " ");
  work->logged = false;
  work->user = -1;
  if (value)
  {
    user = 0;
    while (user < 2)
    {
      if (!strcmp(value, users[user].user))
      {
        work->user = user;
        return (send_message(CLI_SOCK(work), "%s %s", "331", replies[R331]));
      }
     ++user;
    }
    return (send_message(CLI_SOCK(work), "%s %s", "530", replies[R530]));
  }
  return (send_message(CLI_SOCK(work), "%s %s", "332", replies[R332]));
}