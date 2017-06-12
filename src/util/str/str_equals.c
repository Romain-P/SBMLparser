/*
** str_equals.c for  in /home/romain.pillot/projects/ghoulc/src/str
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Sun May 28 04:14:38 2017 romain pillot
** Last update Sun May 28 04:16:01 2017 romain pillot
*/

#include "util.h"

bool	str_equals(const char *a, const char *b)
{
  if (!a || !b)
    return (!a && !b);
  while (*a || *b)
    if (*a++ != *b++)
      return (false);
  return (true);
}
