/*
** tab_contains.c for  in /home/romain.pillot/projects/ADM_SBMLparser_2016/src/util/str
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Wed Jun 14 13:25:58 2017 romain pillot
** Last update Wed Jun 14 13:27:27 2017 romain pillot
*/

#include "util.h"

bool	tab_contains(char **tab, const char *str)
{
  while (*tab)
    if (str_equals(*tab++, str))
      return (true);
  return (true);
}
