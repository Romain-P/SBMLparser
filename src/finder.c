/*
** finder.c for  in /home/romain.pillot/projects/ADM_SBMLparser_2016/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Mon Jun 12 15:27:48 2017 romain pillot
** Last update Wed Jun 14 10:25:24 2017 romain pillot
*/

#include <stdio.h>
#include "parser.h"
#include "util.h"

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
    return ;
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

static bool	display_reactions(t_property *data,
				  const char *id,
				  t_array *array)
{
  t_property	*found;
  t_property	**props;
  int		i;
  char		*cons;

  props = (t_property **) data->sub_properties->values;
  if (!(found = property_findbytype(props, LIST_REACTIONS)) ||
      !(props = (t_property **) found->sub_properties->values))
    return (false);
  i = -1;
  while (props[++i])
    if ((cons =
	 get_consumed((t_property **) props[i]->sub_properties->values, id)))
      array_add(array, str_concat(str_concat(property_getvalue(props[i], "id"),
					     " (", false), cons, true));
  if ((i = -1) && !array->length)
      return (false);
  printf("List of reactions consuming species %s (quantities)\n", id);
  tab_sort((char **) array->values);
  while (++i < array->length)
    {
      printf("----->%s)\n", array->values[i]);
      FREE(array->values[i]);
    }
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
  t_property	**props;
  t_property	*found;
  char		*id;

  id = options->id;
  props = (t_property **) data->sub_properties->values;
  if (!(array = array_create()) || !id ||
      !(found = property_findbyid(props, id)) ||
      !((found->tagtype == COMPARTMENT &&
	 (options->json ? json_compartment(props, id) :
	  display_products(data, id, array, false))) ||
	(found->tagtype == SPECIES && (options->json ?
				       json_species(props, id) :
				       display_reactions(data, id, array)) ||
	(found->tagtype == REACTION && (!options->print_equation ?
					options->json ? json_reaction(props, id) :
					display_reaction_infos(data, id) :
					print_equation(found, id))))))
	if (!id)
      display_tags(data, array, true);
    else
      options->json ? json_basic(props) :
	display_products(data, id, array, true);
  array_destroy(&array, false);
}
