/*
** option.c for  in /home/romain.pillot/projects/SBMLparser/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Mon Jun 12 15:32:46 2017 romain pillot
** Last update Wed Jun 14 05:36:54 2017 romain pillot
*/

#include "parser.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "util.h"

static bool	parse_options(int ac, char **args, t_options *options)
{
  int		i;

  i = 1;
  while (args[++i])
    {
      if (str_equals(args[i], "-i"))
	if (!args[i + 1])
	  options->id = str_dupl("");
	else
	  options->id = str_dupl(args[++i]);
      else if (str_equals(args[i], "-e"))
	if (options->print_equation)
	  return (false);
	else
	  options->print_equation = true;
      else if (str_equals(args[i], "-json"))
	if (options->json)
	  return (false);
	else
	  options->json = true;
      else
	return (false);
    }
  return (true);
}

t_options	*load_options(int ac, char **args, bool debug)
{
  t_options	*options;

  if (!(options = malloc(sizeof(t_options))))
    return (NULL);
  options->id = NULL;
  options->print_equation = false;
  options->json = false;
  if (!parse_options(ac, args, options) && debug)
    {
      FREE(options->id);
      FREE(options);
      fprintf(stderr, "%s: invalid options format.\n", *args);
      return (NULL);
    }
  return (options);
}
