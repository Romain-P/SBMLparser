/*
** json_helper.c for  in /home/romain.pillot/projects/ADM_SBMLparser_2016/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Wed Jun 14 08:14:15 2017 romain pillot
** Last update Wed Jun 14 11:35:50 2017 romain pillot
*/

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "util.h"

static t_property       **childs(t_property *property)
{
  return ((t_property **) property->sub_properties->values);
}

t_property	*json_get_property(t_property *list,
				   t_property *species,
				   char const *id)
{
  t_property	**reactions;
  int		i;
  t_property	*found;
  bool		first;

  if (list->tagtype == LIST_COMPARTMENTS)
    return (property_findbyid(childs(list),
			      property_getvalue(species, "compartment")));
  else if (list->tagtype == LIST_SPECIES)
    return (property_findbyid(childs(list), id));
  reactions = childs(list);
  i = -1;
  first = true;
  while (reactions[++i])
    {
      found = NULL;
      if (!(found = property_findby(childs(reactions[i]), "species", id)))
	continue;
      if (!first)
	printf(",\n");
      json_print_property(reactions[i]);
      first = false;
    }
  return (NULL);
}

void		json_print_property(t_property *p)
{
  t_pair	**pairs;
  int		i;

  if (!p)
    return ;
  pairs = (t_pair **) p->parameters->values;
  parameter_sort(pairs);
  i = -1;
  printf("\t    {\n");
  while (pairs && pairs[++i])
    printf(!i ? "\t\t\"%s\":  \"%s\"" :
	   ",\n\t\t\"%s\":  \"%s\"", pairs[i]->key, pairs[i]->value);
  printf("\n\t    }");
}

void		json_print_species(t_property *list, char const *id)
{
  int		i;
  t_property	**subs;
  bool		first;

  subs = childs(list);
  i = -1;
  first = true;
  while (subs[++i])
    if (str_equals(property_getvalue(subs[i], "compartment"), id))
      {
	if (!first)
	  printf(",\n");
	json_print_property(subs[i]);
	first = false;
      }
}