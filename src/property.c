/*
** property.c for  in /home/romain.pillot/projects/SBMLparser/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Mon Jun 12 09:13:21 2017 romain pillot
** Last update Tue Jun 13 12:24:57 2017 romain pillot
*/

#include "parser.h"
#include "util.h"
#include <stdlib.h>

t_property	*property_create(const char *name, t_property *parent)
{
  t_property	*property;

  if (!(property = malloc(sizeof(t_property))))
    return (NULL);
  property->name = name ? str_dupl(name) : NULL;
  property->tagtype = UNDEFINED;
  property->parameters = array_create();
  property->parent = parent;
  property->sub_properties = array_create();
  return (property);
}

bool    property_exists(t_property **props, t_property *prop)
{
  while (props && *props)
    if (str_equals((*props++)->name, prop->name))
      return (true);
  return (false);
}

t_property	*property_findbyid(t_property **props, char const *id)
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
	if (str_equals(pairs[j]->key, "id") &&
	    str_equals(pairs[j]->value, id))
	  return (props[i]);
      if ((found =
	   property_findbyid((t_property **) props[i]->sub_properties->values, id)))
	return (found);
    }
  return (NULL);
}

t_property	*property_findbytype(t_property **props, t_tagtype type)
{
  t_property	*found;

  while (props && *props)
    {
      if ((*props++)->tagtype == type)
	return (props[-1]);
      if ((found =
	   property_findbytype((t_property **) props[-1]->sub_properties->values, type)))
	return (found);
    }
  return (NULL);
}

void	property_destroy(t_property *property, bool recursively)
{
  int	i;

  FREE(property->name);
  i = -1;
  while (++i < property->parameters->length)
    {
      FREE(((t_pair *) property->parameters->values[i])->key);
      FREE(((t_pair *) property->parameters->values[i])->value);
    }
  array_destroy(&property->parameters, true);
  i = -1;
  if (recursively)
    while (++i < property->sub_properties->length)
      property_destroy((t_property *) property->sub_properties->values[i], true);	
  array_destroy(&property->sub_properties, false);
  FREE(property);
}
