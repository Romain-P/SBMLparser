/*
** parser.c for  in /home/romain.pillot/projects/SBMLparser/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Mon Jun 12 08:17:09 2017 romain pillot
** Last update Mon Jun 12 12:56:25 2017 romain pillot
*/

#include "parser.h"
#include "util.h"
#include <stdlib.h>

static void	load_parameters(char **split, t_property *prop)
{
  char		**pairs;
  int		i;
  t_pair	*pair;

  prop->name = str_dupl(split[0]);
  i = 0;
  while (split && split[++i])
    {
      pairs = str_split(str_dupl(split[i]), SEP_PAIR);
      pair = malloc(sizeof(t_pair));
      pair->key = str_dupl(pairs[0]);
      pair->value = str_dupl(pairs[1] + 1);
      pair->value[str_length(pair->value) - 1] = 0;
      array_add(prop->parameters, pair);
      TAB_FREE(pairs);
    }
}

static void	apply_strategy(char *str, t_property **addr)
{
  t_property	*prop;
  t_property	*new;
  char		**split;
  int		len;

  prop = *addr;
  if (*str == SEP_PROP_END)
    {
      *addr = prop->parent;
      return ;
    }
  new = property_create(NULL, prop);
  str = str_dupl(str);
  len = str_length(str);
  if (str[len - 2] != SEP_PROP_END)
    *addr = new;
  str[len - 2] = 0;
  load_parameters((split = str_split(str, ' ')), new);
  array_add(prop->sub_properties, new);
  TAB_FREE(split);
}

t_property	*load_data(const int fd)
{
  char		*str;
  t_property	*property;
  t_property	*data;

  data = (property = property_create(NULL, NULL));
  while ((str = scan_line(fd)))
    {
      str_reduce(str, 0);
      if (*str == SEP_PARAM_OPEN && !str_starts(str, HEADER))
	apply_strategy(str + 1, &property);
      FREE(str);
    }
  return (data);
}
