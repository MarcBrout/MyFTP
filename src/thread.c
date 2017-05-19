/*
** thread.c for  in /home/brout_m/rendu/system/PSU_2016_myftp
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Fri May 19 11:33:00 2017 brout_m
** Last update Fri May 19 11:33:45 2017 brout_m
*/
#include <pthread.h>
#include <string.h>
#include "types.h"

static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_t	thread;
static t_thdata		thdata;

int			lock()
{
  return (pthread_mutex_lock(&mutex));
}

int			unlock()
{
  return (pthread_mutex_unlock(&mutex));
}

int			launch_thread(t_work *work,
				      char *command, thread_funct_t fn)
{
  pthread_attr_t	attr;

  thdata.work = work;
  thdata.command = strdup(command);
  if (pthread_attr_init(&attr) ||
      pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) ||
      pthread_create(&thread, &attr, fn, &thdata))
    {
      pthread_attr_destroy(&attr);
      return (1);
    }
  pthread_attr_destroy(&attr);
  return (0);
}

int			destroy_mutex()
{
  return pthread_mutex_destroy(&mutex);
}
