/*
** list.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_philo
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Wed Mar 15 10:13:36 2017 Baptiste Veyssiere
** Last update Wed Mar 15 14:45:44 2017 Baptiste Veyssiere
*/

#include "philo.h"

void	free_list(t_philo *list, int nbr)
{
  int		i;
  t_philo	*buf;

  i = -1;
  while (++i < nbr)
    {
      buf = list;
      list = list->next;
      free(buf);
    }
}

static t_philo	*create_new_elem()
{
  t_philo	*new;

  if ((new = malloc(sizeof(t_philo))) == NULL)
    {
      fprintf(stderr, "Error while allocating memory\n");
      return (NULL);
    }
  new->eat = 0;
  new->think = 0;
  new->sleep = 0;
  return (new);
}

t_philo	*create_list(int nbr)
{
  t_philo	*new;
  t_philo	*buf;
  int		i;

  if ((new = malloc(sizeof(t_philo))) == NULL)
    {
      fprintf(stderr, "Error while allocating memory\n");
      return (NULL);
    }
  new->eat = 0;
  new->think = 0;
  new->sleep = 0;
  i = 0;
  new->name = 'A';
  buf = new;
  while (++i < nbr)
    {
      if (!(new->next = create_new_elem()))
	return (NULL);
      new = new->next;
      new->name = 'A' + i;
    }
  new->next = buf;
  return (new->next);
}
