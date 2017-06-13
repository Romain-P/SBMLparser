/*
** finder_util.c for  in /home/romain.pillot/projects/ADM_SBMLparser_2016/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Tue Jun 13 11:59:25 2017 romain pillot
** Last update Tue Jun 13 12:10:37 2017 romain pillot
*/

#include "parser.h"
#include "util.h"
#include <stdlib.h>

char		*property_getvalue(t_property *property, char const *key)
{
  int		i;
  t_pair	**pairs;

  pairs = (t_pair **) property->parameters->values;
  while (*pairs)
    if (str_equals((*pairs++)->key, key))
      return (pairs[-1]->value);
  return (NULL);
}
