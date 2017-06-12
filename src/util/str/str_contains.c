/*
** str_contains.c for  in /home/romain.pillot/projects/ghoulc/src/str
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Tue May 30 11:39:23 2017 romain pillot
** Last update Tue May 30 11:42:34 2017 romain pillot
*/

#include "util.h"

bool	str_contains(const char *str, const char *charset)
{
  int   i;

  i = 0;
  if (!charset || !(*charset))
    return (false);
  while (str && *str)
    if (*str++ == charset[i])
      if (!(charset[++i]))
	return (true);
      else
	continue;
    else
      i= 0;
  return (false);
}
