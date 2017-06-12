/*
** requirement.c for  in /home/romain.pillot/projects/SBMLparser/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Mon Jun 12 07:05:40 2017 romain pillot
** Last update Mon Jun 12 13:16:57 2017 romain pillot
*/

#include <stdlib.h>
#include <stdbool.h>

static bool	char_isalphanumeric(char c)
{
  return ((c >= '0' && c <= '9') ||
	  (c >= 'a' && c <= 'z') ||
	  (c >= 'A' && c <= 'Z'));
}

static void	str_reduce(char *str)
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
  int   i;
  int   j;
  int   k;

  i = -1;
  str_reduce(str);
  hold = str;
  if (!(tab = malloc(sizeof(char *) * ((str_countchar(str) + 2)))))
    return (NULL);
  k = 0;
  while (str[++i])
    if (!char_isalphanumeric(str[(j = i)]) || !(str[(j = i + 1)]))
      {
	tab[k++] = hold;
	hold = str + j + 1;
	str[j] = 0;
      }
  tab[k] = 0;
  return (tab);
}
