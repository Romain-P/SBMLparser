/*
** str_concat.c for  in /home/romain.pillot/projects/ADM_SBMLparser_2016/src/util/str
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Tue Jun 13 17:31:21 2017 romain pillot
** Last update Tue Jun 13 18:32:04 2017 romain pillot
*/

#include "util.h"
#include <stdlib.h>

char	*str_concat(char *a, const char *b, bool free_a)
{
  char	*concat;
  char	*hold;
  char	*hold_a;

  if (!(hold = (concat = malloc(sizeof(char) * (str_length(a) +
						str_length(b) + 1)))))
    return (NULL);
  hold_a = a;
  while (a && *a)
    *concat++ = *a++;
  while (b && *b)
    *concat++ = *b++;
  *concat = 0;
  if (free_a && hold_a)
    free(hold_a);
  return (hold);
}
