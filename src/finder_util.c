/*
** finder_util.c for  in /home/romain.pillot/projects/ADM_SBMLparser_2016/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Tue Jun 13 11:59:25 2017 romain pillot
** Last update Wed Jun 14 10:23:21 2017 romain pillot
*/

#include <stdlib.h>
#include <stdio.h>
#include "parser.h"
#include "util.h"

char		*property_getvalue(t_property *property, char const *key)
{
  int		i;
  t_pair	**pairs;

  pairs = (t_pair **) property->parameters->values;
  while (pairs && *pairs)
    if (str_equals((*pairs++)->key, key))
      return (pairs[-1]->value);
  return (NULL);
}

void		display_list(t_property *list, char const *param)
{
  int		i;
  t_array	*array;
  t_property	**properties;
  char		*species;

  properties = (t_property **) list->sub_properties->values;
  array = array_create();
  i = -1;
  while (properties[++i])
    {
      species = property_getvalue(properties[i], param);
      array_add(array, species);
    }
  tab_sort((char **) array->values);
  i = -1;
  while (array->values[++i])
    printf("----->%s\n", array->values[i]);
  array_destroy(&array, false);
}

char		*get_consumed(t_property **properties, char const *id)
{
  int		i;
  char		*value;
  t_property	*found;
  t_property	**props;

  if (!(found = property_findbytype(properties, LIST_REACTANTS)) ||
      !(props = (t_property **) found->sub_properties->values))
    return (NULL);
  i = -1;
  while (props && props[++i])
    {
      value = property_getvalue(props[i], "species");
      if (str_equals(value, id))
	return (property_getvalue(props[i], "stoichiometry"));
    }
  return (NULL);
}

t_property	*property_findby
(t_property **props, char const *key, char const *value)
{
  int		i;
  int		j;
  t_pair	**pairs;
  t_property	*found;

  i = -1;
  while (props && props[++i])
    {
      pairs = (t_pair **) props[i]->parameters->values;
      j = -1;
      while (++j < props[i]->parameters->length)
	if (str_equals(pairs[j]->key, key) &&
	    str_equals(pairs[j]->value, value))
	  return (props[i]);
      if ((found =
	   property_findby((t_property **)
			   props[i]->sub_properties->values, key, value)))
	return (found);
    }
  return (NULL);
}
