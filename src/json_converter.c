/*
** json_converter.c for  in /home/romain.pillot/projects/ADM_SBMLparser_2016/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Wed Jun 14 04:52:57 2017 romain pillot
** Last update Wed Jun 14 09:20:28 2017 romain pillot
*/

#include "parser.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>

static t_property	**childs(t_property *property)
{
  return ((t_property **) property->sub_properties->values);
}

bool		json_species(t_property **props, char const *id)
{
  t_property	*species;
  t_property	*p;
  t_property	**subs;
  int		i;

  p = property_findbytype(props, MODEL);
  subs = childs(property_findbytype(props, LIST_SPECIES));
  species = property_findbyid(subs, id);
  subs = childs(p);
  property_sort_full(subs);
  printf("{\n");
  i = -1;
  while (subs[++i])
    {
      printf(!i ? "\t\"%s\":  [\n" :
	     ",\n\t\"%s\":  [\n", subs[i]->name);
      json_print_property(json_get_property(subs[i], species, id));
      printf("\n\t]");
    }
  printf("\n}\n");
  return (true);
}

bool	json_compartment(t_property **pros, char const *id)
{
  
  return (true);
}

bool	json_reaction(t_property **props, char const *id)
{
  
  return (true);
}

bool	json_basic(t_property **props)
{
  
  return (true);
}
