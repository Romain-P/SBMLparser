/*
** display.c for  in /home/romain.pillot/projects/ghoulc/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Tue May 23 13:51:46 2017 romain pillot
** Last update Tue May 23 14:45:53 2017 romain pillot
*/

#include <stdio.h>
#include <unistd.h>
#include "util.h"

static bool	private_print(const int channel, const char *str)
{
  int		len;

  len = 0;
  while(str && str[len] && ++len);
  return (len ? write(channel, str, len) : false);
}

bool	print(const char *str)
{
  return (private_print(STDOUT_FILENO, str));
}

bool	fprint(const char *str)
{
  return (private_print(STDERR_FILENO, str));
}
