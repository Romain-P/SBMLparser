/*
** finder.c for  in /home/romain.pillot/projects/ADM_SBMLparser_2016/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Mon Jun 12 15:27:48 2017 romain pillot
** Last update Tue Jun 13 08:39:48 2017 romain pillot
*/

#include "parser.h"
#include <stdio.h>

static void	display_tags(t_property *data, t_array *array, bool root)
{
  int		i;
  t_property	**props;

  props = (t_property **) data->sub_properties->values;
  i = -1;
  while (props && props[++i])
    {
      if (!property_exists((t_property **) array->values, props[i]))
	array_add(array, props[i]);
      if (props[i]->sub_properties->length)
	display_tags(props[i], array, false);
    }
  if (!root)
    return;
  property_sort_full((props = ((t_property **) array->values)));
  while (props && *props)
    {
      if (!(*props)->parameters->length && props++)
	continue;
      i = -1;
      printf("%s\n", (*props)->name, (*props)->parameters->length);
      while ((*props)->parameters->values[++i])
	printf("----->%s\n", ((t_pair *) (*props)->parameters->values[i])->key);
      props++;
    }
}

void	display(t_property *data, t_options *options)
{
  if (!options->id)
    display_tags(data, array_create(), true);
}
