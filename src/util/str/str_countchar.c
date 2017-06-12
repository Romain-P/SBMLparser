/*
** str_countchar.c for  in /home/romain.pillot/projects/ghoulc/src/str
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Thu May 25 09:33:12 2017 romain pillot
** Last update Thu May 25 09:42:39 2017 romain pillot
*/

#include "util.h"

int     str_countchar(const char *str, const char c)
{
  int   i;
  int   j;

  i = (j = 0);
  while (str && str[i] && ++i)
    if (str[i] == c)
      j++;
  return (j);
}
