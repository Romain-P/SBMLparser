/*
** main.c for  in /home/romain.pillot/bin
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Thu Nov 24 11:14:29 2016 romain pillot
** Last update Mon Jun 12 17:09:43 2017 romain pillot
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

int		main(int ac, char **args)
{
  int		fd;
  t_property	*data;
  t_options	*options;

  if ((fd = file_open(args[1], *args)) == -1 ||
      !(data = load_data(fd)) ||
      !(options = load_options(ac, args, false)))
    return (_EXIT_FAILURE);
  display(data, options);
  close(fd);
  property_destroy(data, true);
  FREE(options->id);
  FREE(options);
  return (_EXIT_SUCCESS);
}
