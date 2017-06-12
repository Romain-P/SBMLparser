/*
** str_split.c for  in /home/romain.pillot/projects/ghoulc/src/str
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Thu May 25 09:28:27 2017 romain pillot
** Last update Mon Jun 12 11:22:42 2017 romain pillot
*/

#include <stdlib.h>
#include "util.h"

char    **str_split(char *str, const char delimiter)
{
  char  **tab;
  char  *hold;
  int   i;
  int   j;
  int   k;
  bool	ignore;

  i = -1;
  hold = str;
  if (!(tab = malloc(sizeof(char *) * ((str_countchar(str, delimiter) + 2)))))
    return (NULL);
  k = 0;
  ignore = false;
  while (str[++i])
    {
      ignore = str[i] == '"' ? !ignore : ignore;
      if (!ignore && (str[(j = i)] == delimiter || !(str[(j = i + 1)])))
	{
	  tab[k++] = hold;
	  hold = str + j + 1;
	  str[j] = 0;
	}
    }
  tab[k] = 0;
  return (tab);
}
