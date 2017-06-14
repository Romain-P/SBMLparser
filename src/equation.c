/*
** reaction.c for  in /home/romain.pillot/projects/ADM_SBMLparser_2016/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Tue Jun 13 16:21:34 2017 romain pillot
** Last update Wed Jun 14 10:22:55 2017 romain pillot
*/

#include <stdlib.h>
#include <stdio.h>
#include "util.h"
#include "parser.h"

static void	print_list(t_property **properties, t_tagtype type)
{
  t_property	*list;
  t_property	**props;
  int		i;
  t_array	*array;

  list = property_findbytype(properties, type);
  props = (t_property **) list->sub_properties->values;
  array = array_create();
  i = -1;
  while (props[++i])
    array_add(array,
	      str_concat(str_concat(property_getvalue(props[i], "stoichiometry"),
				    " ", false), property_getvalue(props[i], "species"), true));
  tab_sort((char **) array->values);
  i = -1;
  while (++i < array->length)
    {
      printf(i ? " + %s" : "%s", array->values[i]);
      FREE(array->values[i]);
    }
  array_destroy(&array, false);
}

bool		print_equation(t_property *found, char const *id)
{
  bool		reversible;
  t_property	**props;
  int		i;

  if (!(props = (t_property **) found->sub_properties->values))
    return (false);
  i = -1;
  print_list((t_property **) found->sub_properties->values, LIST_REACTANTS);
  printf(str_equals(property_getvalue(found, "reversible"), "true") ?
	 " <-> " : " -> ");
  print_list((t_property **) found->sub_properties->values, LIST_PRODUCTS);
  printf("\n");
  return (true);
}
