/*
** sort.c for  in /home/romain.pillot/projects/SBMLparser/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Mon Jun 12 13:01:14 2017 romain pillot
** Last update Wed Jun 14 08:18:30 2017 romain pillot
*/

#include <stdbool.h>
#include "parser.h"

void		parameter_sort(t_pair **params)
{
  t_pair	*tmp;
  bool		changed;
  int		i;
  int		j;

  changed = false;
  i = -1;
  while (params && params[++i] && params[i + 1] && !(j = 0))
    while (params[i]->key && params[i]->key[j] &&
	   params[i + 1]->key && params[i + 1]->key[j] &&
	   params[i]->key[j] >= params[i + 1]->key[j])
      {
	if (params[i]->key[j] > params[i + 1]->key[j])
	  {
	    tmp = params[i];
	    params[i] = params[i + 1];
	    params[i + 1] = tmp;
	    changed = true;
	    break;
	  }
	j++;
      }
  if (changed)
    parameter_sort(params);
}

static void	property_sort(t_property **props)
{
  t_property	*tmp;
  bool		changed;
  int		i;
  int		j;

  changed = false;
  i = -1;
  while (props && props[++i] && props[i + 1] && !(j = 0))
    while (props[i]->name && props[i]->name[j] &&
	   props[i + 1]->name && props[i + 1]->name[j] &&
	   props[i]->name[j] >= props[i + 1]->name[j])
      {
	if (props[i]->name[j] > props[i + 1]->name[j])
	  {
	    tmp = props[i];
	    props[i] = props[i + 1];
	    props[i + 1] = tmp;
	    changed = true;
	    break;
	  }
	j++;
      }
  if (changed)
    property_sort(props);
}

void	property_sort_full(t_property **props)
{
  
  int	i;

  property_sort(props);
  i = -1;
  while (props[++i])
    parameter_sort((t_pair **)props[i]->parameters->values);
}
