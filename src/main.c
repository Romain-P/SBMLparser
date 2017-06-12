/*
** main.c for  in /home/romain.pillot/bin
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Thu Nov 24 11:14:29 2016 romain pillot
** Last update Mon Jun 12 14:33:48 2017 romain pillot
*/

#include "parser.h"
#include "util.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	file_open(const char *name, char *prog)
{
  int		fd;

  fd = -1;
  if (!name || (fd = open(name, O_RDONLY)) == -1)
    fprintf(stderr, "%s: can't open the file: %s\n", prog, name);
  return (fd);
}

static void	show(t_property *property, int lvl)
{
  int		i;
  int		j;

  i = -1;
  while (++i < lvl)
    printf("%c", '-');
  printf("> %s\n", property->name);
  j = -1;
  while (++j < property->parameters->length)
    {
      i = -1;
      while (++i < lvl + 1)
	printf("%c", '-');
      printf("> %s=%s\n", ((t_pair *)(property->parameters->values[j]))->key,
	     ((t_pair *)(property->parameters->values[j]))->value);
    }
  if (property->sub_properties->length)
    property_sort_full((t_property **) property->sub_properties->values);
  i = -1;
  while (++i < property->sub_properties->length)
    show((t_property *)property->sub_properties->values[i], lvl + 2);
}

int		main(int ac, char **args)
{
  int		fd;
  t_property	*data;

  if ((fd = file_open(args[1], *args)) == -1)
    return (_EXIT_FAILURE);
  data = load_data(fd);
  close(fd);
  show(data, 2);
  property_destroy(data, true);
  return (_EXIT_SUCCESS);
}
