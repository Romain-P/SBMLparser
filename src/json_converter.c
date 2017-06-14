/*
** json_converter.c for  in /home/romain.pillot/projects/ADM_SBMLparser_2016/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Wed Jun 14 04:52:57 2017 romain pillot
** Last update Wed Jun 14 14:20:40 2017 romain pillot
*/

#include <stdlib.h>
#include <stdio.h>
#include "parser.h"
#include "util.h"

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
  printf("{\n");
  i = -1;
  while (subs[++i])
    {
      if (!(p = json_get_property(subs[i], species, id, false)) &&
	  subs[i]->tagtype != LIST_REACTIONS)
	continue;
      printf(!i ? "\t\"%s\":  [\n" :
	     ",\n\t\"%s\":  [\n", subs[i]->name);
      json_print_property(json_get_property(subs[i], species, id, true), NULL);
      printf("\n\t]");
    }
  printf("\n}\n");
  return (true);
}

bool		json_compartment(t_property **pros, char const *id)
{
  t_property	*comp;
  t_property	**subs;
  int		i;
  bool		first;

  comp = property_findbytype(pros, LIST_COMPARTMENTS);
  comp = property_findbyid(childs(comp), id);
  printf("{\n\t\"listOfCompartments\": [\n");
  json_print_property(comp, NULL);
  printf("\n\t],\n\t\"listOfReactions\": [\n");
  subs = childs(property_findbytype(pros, LIST_REACTIONS));
  i = -1;
  first = true;
  while (subs[++i])
    if (str_equals(property_getvalue(subs[i], "compartment"), id))
      {
	if (!first)
	  printf(",\n");
	json_print_property(subs[i], NULL);
	first = false;
      }
  printf("\n\t],\n\t\"listOfSpecies\": [\n");
  json_print_species(property_findbytype(pros, LIST_SPECIES), id);
  printf("\n\t]\n}\n");
  return (true);
}

static void	json_display_list(t_property *list)
{
  int		i;
  t_property	**subs;

  subs = childs(list);
  i = -1;
  while (subs[++i])
    {
      if (i)
	printf(",\n");
      json_print_property(subs[i], (char*[]) {"species", "stoichiometry", 0});
    }
}

bool		json_reaction(t_property **props, char const *id)
{
  t_property	**reactions;
  t_property	*r;
  int		i;

  reactions = childs(property_findbytype(props, LIST_REACTIONS));
  r = property_findbyid(reactions, id);
  printf("{\n\t\"%s\":  [\n", "listOfReactants");
  json_display_list(property_findbytype(childs(r), LIST_REACTANTS));
  printf("\n\t],\n\t\"%s\":  [\n", "listOfProducts");
  json_display_list(property_findbytype(childs(r), LIST_PRODUCTS));
  printf("\n\t]\n}\n");
  return (true);
}
