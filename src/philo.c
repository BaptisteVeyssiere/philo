/*
** philo.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_philo
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Tue Mar 14 17:18:17 2017 Baptiste Veyssiere
** Last update Fri Mar 17 11:18:07 2017 Nathan Scutari
*/

#include <stdio.h>
#include "philo.h"

static void	thread_order(t_data *data, int part)
{
  if (part == 1)
    {
      pthread_mutex_lock(&data->counter_lock);
      data->a += 1;
      if (data->a == data->nbr)
	{
	  data->a = 0;
	  pthread_mutex_unlock(&data->global_lock_1);
	}
      pthread_mutex_unlock(&data->counter_lock);
      pthread_mutex_lock(&data->global_lock_1);
      return ;
    }
  pthread_mutex_trylock(&data->global_lock_2);
  pthread_mutex_unlock(&data->global_lock_1);
  pthread_mutex_lock(&data->counter_lock);
  data->b += 1;
  if (data->b == data->nbr)
    {
      data->b = 0;
      pthread_mutex_unlock(&data->global_lock_2);
    }
  pthread_mutex_unlock(&data->counter_lock);
  pthread_mutex_lock(&data->global_lock_2);
  pthread_mutex_trylock(&data->global_lock_1);
  pthread_mutex_unlock(&data->global_lock_2);
}

static void	philo_action(t_data *data, t_philo *list)
{
  if (list->eat == list->sleep && list->eat == list->think)
    {
      lphilo_take_chopstick(&list->chopstick);
      lphilo_think();
      lphilo_release_chopstick(&list->chopstick);
      list->think += 1;
    }
  else if (list->eat == list->sleep)
    {
      lphilo_take_chopstick(&list->chopstick);
      lphilo_take_chopstick(&list->next->chopstick);
      lphilo_eat();
      lphilo_release_chopstick(&list->chopstick);
      lphilo_release_chopstick(&list->next->chopstick);
      if ((list->eat += 1) == data->max_eat)
	data->end = 1;
    }
  else
    {
      lphilo_sleep();
      list->sleep += 1;
    }
}

static void	*philosopher(void *ptr)
{
  t_philo	*list;
  t_data	*data;

  data = (t_data*)ptr;
  while (!data->end)
    {
      thread_order(data, 1);
      list = data->list;
      while (list->thread_philo != pthread_self())
	list = list->next;
      if (!data->end)
	philo_action(data, list);
      thread_order(data, 2);
    }
  return (NULL);
}

int	philo(int nbr, int max_eat)
{
  t_data	data;
  int		i;

  data.max_eat = max_eat;
  data.nbr = nbr;
  data.a = 0;
  data.b = 0;
  data.end = 0;
  data.global_lock_1 = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
  data.global_lock_2 = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
  data.counter_lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_lock(&data.global_lock_2);
  pthread_mutex_lock(&data.global_lock_1);
  if (!(data.list = create_list(nbr)))
    return (1);
  i = -1;
  while (++i < nbr)
    {
      if (pthread_create(&(data.list->thread_philo), NULL, philosopher, &data))
	{
	  fprintf(stderr, "Failed to create a thread\n");
	  return (1);
	}
      data.list = data.list->next;
    }
  i = -1;
  while (++i < nbr)
    {
      pthread_join(data.list->thread_philo, NULL);
      data.list = data.list->next;
    }
  free_list(data.list, nbr);
  RCFCleanup();
  return (0);
}
