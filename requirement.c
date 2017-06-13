/*
** requirement.c for  in /home/romain.pillot/projects/SBMLparser/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Mon Jun 12 07:05:40 2017 romain pillot
** Last update Tue Jun 13 06:41:18 2017 romain pillot
*/

#include <stdlib.h>
#include <stdbool.h>

static bool	char_isalphanumeric(char c)
{
  return ((c >= '0' && c <= '9') ||
	  (c >= 'a' && c <= 'z') ||
	  (c >= 'A' && c <= 'Z'));
}

static char	*str_dupl(char const *str)
{
  char		*new;
  int		i;

  i = 0;
  while (str && str[i] && ++i);
  new = malloc(sizeof(char) * (i + 1));
  new[i] = 0;
  while (--i >= 0)
    new[i] = str[i];
  return (new);
}

static char	*str_reduce(char *str)
{
  int   i;
  int   j;

  i = (j = 0);
  while (str && str[i])
    {
      if (char_isalphanumeric(str[i]))
	{
	  if (i && j && !char_isalphanumeric(str[i - 1]))
	    str[j++] = str[i - 1];
	  str[j++] = str[i++];
	}
      else
	i++;
    }
  if (str)
    str[j] = 0;
  return (str);
}

static int	str_countchar(const char *str)
{
  int   i;
  int   j;

  i = (j = 0);
  while (str && str[i] && ++i)
    if (!char_isalphanumeric(str[i]))
      j++;
  return (j);
}

char	**my_strtowordtab_synthesis(char const *str)
{
  char  **tab;
  char  *hold;
  char	*dup;
  int   i;
  int   j;
  int   k;

  i = -1;
  hold = (dup = str_reduce(str_dupl(str)));
  if (!(tab = malloc(sizeof(char *) * ((str_countchar(dup) + 2)))))
    return (NULL);
  k = 0;
  while (dup[++i])
    if (!char_isalphanumeric(dup[(j = i)]) || !(dup[(j = i + 1)]))
      {
	tab[k++] = hold;
	hold = dup + j + 1;
	dup[j] = 0;
      }
  tab[k] = 0;
  return (tab);
}
