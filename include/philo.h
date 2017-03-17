/*
** philo.h for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_philo
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Tue Mar 14 16:43:09 2017 Baptiste Veyssiere
** Last update Fri Mar 17 10:54:23 2017 Nathan Scutari
*/

#ifndef PHILO_H_
# define PHLIO_H_

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "extern.h"

#define USE "Usage: ./philo -p [NBR OF PHILOSOPHERS] -e [MAX EAT OCCURENCE]\n"

typedef struct	s_philo
{
  struct s_philo	*next;
  pthread_t		thread_philo;
  pthread_mutex_t	chopstick;
  int			eat;
  int			think;
  int			sleep;
  char			name;
} t_philo;

typedef struct	s_data
{
  t_philo		*list;
  pthread_mutex_t	global_lock_1;
  pthread_mutex_t	global_lock_2;
  pthread_mutex_t	counter_lock;
  int			a;
  int			b;
  int			max_eat;
  int			nbr;
  int			end;
} t_data;

int	philo(int, int);
t_philo	*create_list(int);
void	free_list(t_philo*, int);

#endif /* !PHILO_H_ */
