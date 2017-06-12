/*
** property.c for  in /home/romain.pillot/projects/SBMLparser/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Mon Jun 12 09:13:21 2017 romain pillot
** Last update Mon Jun 12 11:52:06 2017 romain pillot
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
  property->parameters = array_create();
  property->parent = parent;
  property->sub_properties = array_create();
  return (property);
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
