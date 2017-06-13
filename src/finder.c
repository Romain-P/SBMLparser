/*
** finder.c for  in /home/romain.pillot/projects/ADM_SBMLparser_2016/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Mon Jun 12 15:27:48 2017 romain pillot
** Last update Tue Jun 13 10:26:58 2017 romain pillot
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
      printf("%s\n", (*props)->name);
      while ((*props)->parameters->values[++i])
	printf("----->%s\n", ((t_pair *) (*props)->parameters->values[i])->key);
      props++;
    }
}

static bool	display_chemical_products(t_property *data)
{
  t_property	*found;

  return (true);
}

static bool	display_chemical_reactions(t_property *data)
{

  return (true);
}

static bool	display_reaction_infos(t_property *data)
{

  return (true);
}

void		display(t_property *data, t_options *options)
{
  t_array	*array;
  t_property	**properties;
  t_property	*found;

  array = array_create();
  properties = (t_property **) data->sub_properties->values;
  if (!options->id ||
      !(found = property_findbyid(properties, options->id)) ||
      !((found->tagtype == COMPARTMENT && display_chemical_products(data)) ||
	(found->tagtype == SPECIES && display_chemical_reactions(data)) ||
	(found->tagtype == REACTION && display_reaction_infos(data))))
    display_tags(data, array, true);
  array_destroy(&array, false);
}
