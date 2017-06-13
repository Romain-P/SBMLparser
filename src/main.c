/*
** main.c for  in /home/romain.pillot/bin
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Thu Nov 24 11:14:29 2016 romain pillot
** Last update Tue Jun 13 12:54:26 2017 romain pillot
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

static int	free_and_exit(int status, int fd, t_property *data, t_options *opt)
{
  if (fd > 0)
    close(fd);
  if (data)
    property_destroy(data, true);
  FREE(opt->id);
  FREE(opt);
  return (status);
}

int		main(int ac, char **args)
{
  int		fd;
  t_property	*data;
  t_options	*options;

  if ((fd = file_open(args[1], *args)) == -1 ||
      !(data = load_data(fd)) ||
      !(options = load_options(ac, args, true)))
    return (free_and_exit(_EXIT_FAILURE, fd, data, options));
  display(data, options);
  return (free_and_exit(_EXIT_SUCCESS, fd, data, options));
}
