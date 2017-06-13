/*
** finder.c for  in /home/romain.pillot/projects/ADM_SBMLparser_2016/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Mon Jun 12 15:27:48 2017 romain pillot
** Last update Tue Jun 13 15:44:28 2017 romain pillot
*/

#include "parser.h"
#include "util.h"
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

static bool	display_products
(t_property *data, const char *id, t_array *array, bool nfound)
{
  t_property	*found;
  t_property	**properties;
  int		i;

  properties = (t_property **) data->sub_properties->values;
  if (!(found = property_findbytype(properties, LIST_SPECIES)) ||
      !(properties = (t_property **) found->sub_properties->values))
    return (false);
  if (!nfound)
    printf("List of species in compartment %s\n", id);
  else
    printf("List of species\n");
  while (*properties)
    if ((nfound && properties++) ||
	str_equals(property_getvalue((*properties++), "compartment"), id))
      array_add(array, property_getvalue(properties[-1], "name"));
  tab_sort((char **) array->values);
  i = -1;
  while (array->values && array->values[++i])
    printf("----->%s\n", array->values[i]);
  return (true);
}

static bool	display_reactions(t_property *data, const char *id)
{
  t_property	*found;
  t_property	**properties;
  int		i;
  char		*consumed;

  properties = (t_property **) data->sub_properties->values;
  if (!(found = property_findbytype(properties, LIST_REACTIONS)) ||
      !(properties = (t_property **) found->sub_properties->values))
    return (false);
  printf("List of reactions consuming species %s (quantities)\n", id);
  i = -1;
  while (properties[++i])
    if (consumed =
	get_consumed((t_property **) properties[i]->sub_properties->values, id))
      printf("----->%s (%s)\n", property_getvalue(properties[i], "id"), consumed);
  return (true);
}

static bool	display_reaction_infos(t_property *data, const char *id)
{
  t_property	*found;
  t_property	**properties;
  int		i;

  properties = (t_property **) data->sub_properties->values;
  if (!(found = property_findbyid(properties, id)) ||
      !(properties = (t_property **) found->sub_properties->values))
    return (false);
  while (*properties++ && (i = - 1))
    if (properties[-1]->tagtype == LIST_REACTANTS)
      {
	printf("List of reactants of reaction %s\n", id);
	display_list(properties[-1], "species");
      }
    else if (properties[-1]->tagtype == LIST_PRODUCTS)
      {
	printf("List of products of reaction %s\n", id);
	display_list(properties[-1], "species");
      }
  return (true);
}

void		display(t_property *data, t_options *options)
{
  t_array	*array;
  t_property	**properties;
  t_property	*found;
  char		*id;

  array = array_create();
  id = options->id;
  properties = (t_property **) data->sub_properties->values;
  if (!id ||
      !(found = property_findbyid(properties, id)) ||
      !((found->tagtype == COMPARTMENT &&
	 display_products(data, id, array, false)) ||
	(found->tagtype == SPECIES && display_reactions(data, id)) ||
	(found->tagtype == REACTION && display_reaction_infos(data, id))))
    if (!id)
      display_tags(data, array, true);
    else
      display_products(data, id, array, true);
  array_destroy(&array, false);
}
