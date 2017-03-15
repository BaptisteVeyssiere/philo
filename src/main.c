/*
** main.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_philo
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Tue Mar 14 16:19:28 2017 Baptiste Veyssiere
** Last update Tue Mar 14 17:15:48 2017 Baptiste Veyssiere
*/

#include "philo.h"

int	print_error(int ret, char *nbr, char *msg)
{
  fprintf(stderr, msg, nbr);
  return (ret);
}

int	is_number(char *str)
{
  char	*buf;

  while (*str == ' ' || *str == '\t')
    ++str;
  if (*str == '-')
    return (print_error(0, str, "%s is not a positive number\n"));
  buf = str;
  while (*str)
    {
      if (*str > '9' || *str < '0')
	{
	  if (*str == ' ' || *str == '\t')
	    {
	      while (*(++str))
		if (*str != ' ' && *str != '\t')
		  return (print_error(0, buf, "%s is not a number\n"));
	      return (1);
	    }
	  else
	    return (print_error(0, buf, "%s is not a number\n"));
	}
      ++str;
    }
  return (1);
}

int	check_opt(char *opt, char *opt_)
{
  if (*opt != '-' || *opt_ != '-')
    return (1);
  if ((*(opt + 1) == 'p' && *(opt_ + 1) == 'e') ||
      (*(opt + 1) == 'e' && *(opt_ + 1) == 'p'))
    return (0);
  return (1);
}

int	check_limit(int nbr1, int nbr2, char c)
{
  int	check1;
  int	check2;

  if (c == 'p')
    {
      check1 = nbr1;
      check2 = nbr2;
    }
  else
    {
      check1 = nbr2;
      check2 = nbr1;
    }
  if (check1 < 2)
    {
      fprintf(stderr, "%d is too small\n", check1);
      return (1);
    }
  else if (check2 < 1)
    {
      fprintf(stderr, "%d is too small\n", check2);
      return (1);
    }
  return (0);
}

int	main(int ac, char **av)
{
  int	nbr1;
  int	nbr2;

  if (ac < 5 || check_opt(av[1], av[3]))
    {
      fprintf(stderr, USE);
      return (1);
    }
  if (is_number(av[2]) == 0 || is_number(av[4]) == 0)
    return (1);
  nbr1 = atoi(av[2]);
  nbr2 = atoi(av[4]);
  if (check_limit(nbr1, nbr2, av[1][1]))
    return (1);
  if (av[1][1] == 'p')
    return (philo(nbr1, nbr2));
  return (philo(nbr2, nbr1));
}
