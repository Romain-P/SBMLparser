/*
** str_starts.c for  in /home/romain.pillot/projects/SBMLparser/src/util/str
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Mon Jun 12 09:04:58 2017 romain pillot
** Last update Mon Jun 12 09:05:52 2017 romain pillot
*/

#include "util.h"

bool	str_starts(const char *str, const char *charset)
{
  if (!str || !charset)
    return (false);
  while (*charset)
    if (*str++ != *charset++)
      return (false);
  return (true);
}
