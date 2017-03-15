/*
** philo.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_philo
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Tue Mar 14 17:18:17 2017 Baptiste Veyssiere
** Last update Wed Mar 15 18:06:49 2017 Baptiste Veyssiere
*/

#include "philo.h"

static void	*philosopher(void *ptr)
{
  t_data	*data;

  data = (t_data*)ptr;
  while (1)
    {
    }
  return (NULL);
}

int	philo(int nbr, int max_eat)
{
  t_data	data;
  int		i;

  data.max_eat = max_eat;
  data.nbr = nbr;
  data.global_lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
  if (!(data.list = create_list(nbr)))
    return (1);
  i = -1;
  while (++i < nbr)
    {
      if(pthread_create(&(data.list->thread_philo), NULL, philosopher, &data))
	{
	  fprintf(stderr, "Failed to create a thread\n");
	  return (1);
	}
      sleep(1);
      data.list = data.list->next;
    }
  i = -1;
  while (++i < nbr)
    {
      pthread_join(data.list->thread_philo, NULL);
      data.list = data.list->next;
    }
  free_list(data.list, nbr);
  return (0);
}
