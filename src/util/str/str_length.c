/*
** str_length.c for  in /home/romain.pillot/projects/ghoulc/src/str
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Sun May 28 03:27:08 2017 romain pillot
** Last update Sun Jun  4 16:58:29 2017 romain pillot
*/

#include "util.h"

int     str_length(const char *str)
{
  int	i;

  i = 0;
  while (str && str[i] && ++i);
  return (i);
}

int	tab_length(char  **tab)
{
  int	i;

  i = 0;
  while (tab && tab[i] && ++i);
  return (i);
}
