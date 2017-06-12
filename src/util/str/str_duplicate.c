/*
** str_duplicate.c for  in /home/romain.pillot/projects/ghoulc/src/str
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Sun May 28 03:24:50 2017 romain pillot
** Last update Sun May 28 03:28:35 2017 romain pillot
*/

#include "util.h"
#include <stdlib.h>

char	*str_dupl(const char *str)
{
  char  *new;
  char  *hold;

  if (!(hold = (new = malloc(sizeof(char) * (str_length(str) + 1)))))
    return (NULL);
  while (*str)
    *new++ = *str++;
  *new = 0;
  return (hold);
}
