/*
** read.c for  in /home/romain.pillot/projects/ghoulc/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Tue May 23 14:47:01 2017 romain pillot
** Last update Tue May 23 14:47:02 2017 romain pillot
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "util.h"

static char	*append(char *str, char c)
{
  char		*ap;
  int		i;
  int		j;

  i = (j = 0);
  while (str && str[i] && ++i);
  if (!(ap = malloc(sizeof(char) * (i + (!c ? 1 : 2)))))
    return (NULL);
  while(str && j < i)
    {
      ap[j] = str[j];
      j++;
    }
  if ((ap[j] = c))
    ap[j + 1] = 0;
  if (str)
    free(str);
  return (ap);
}

char	*scan_line(const int file)
{
  char	*str;
  char	buffer[1];
  int	error;

  str = NULL;
  while ((error = read(file, buffer, 1)))
    {
      if (buffer[0] == '\n')
	return (str ? str : append(NULL, 0));
      else if (error == -1 || !(str = append(str, buffer[0])))
	break;
    }
  if (error && str)
    free(str);
  return (error ? NULL : str);
}
