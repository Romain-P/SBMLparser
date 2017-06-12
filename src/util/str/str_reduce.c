/*
** str_reduce.c for  in /home/romain.pillot/projects/ghoulc/src/str
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Thu May 25 09:31:45 2017 romain pillot
** Last update Mon Jun 12 10:26:37 2017 romain pillot
*/

#include "util.h"

char    *str_reduce(char *str, const char c)
{
  int   i;
  int   j;
  bool	ignore;

  i = (j = 0);
  ignore = false;
  while (str && str[i])
    {
      ignore = str[i] == '\"' ? !ignore : ignore;
      if (ignore || (c ? str[i] != c : str[i] != ' ' && str[i] != '\t'))
	{
	  if (!ignore && i && j && (c ? str[i - 1] == c :
			 str[i - 1] == ' ' || str[i - 1] == '\t'))
	    str[j++] = c ? c : ' ';
	  str[j++] = str[i++];
	}
      else
	i++;
    }
  if (str)
    str[j] = 0;
  return (str);
}
