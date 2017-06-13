/*
** tab_sort.c for  in /home/romain.pillot/projects/ADM_SBMLparser_2016/src/util/str
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Tue Jun 13 12:35:51 2017 romain pillot
** Last update Tue Jun 13 13:04:28 2017 romain pillot
*/

#include "util.h"

void	tab_sort(char **tab)
{
  int	i;
  int	j;
  char	*tmp;
  bool	changed;

  i = -1;
  changed = false;
  while (tab && tab[++i] && (j = -1))
    while (i && tab[i - 1][++j] && tab[i][j])
      if (tab[i - 1][j] > tab[i][j] ||
	  (tab[i][j] == tab[i -1][j] && !tab[i][j + 1]))
	{
	  tmp = tab[i - 1];
	  tab[i - 1] = tab[i];
	  tab[i] = tmp;
	  changed = true;
	  break;
	}
      else if (tab[i][j] != tab[i - 1][j])
	break;
  if (changed)
    tab_sort(tab);
}
