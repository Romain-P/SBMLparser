/*
** nbr_parsestring.c for  in /home/romain.pillot/projects/ghoulc/src/nbr
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Sun May 28 16:18:26 2017 romain pillot
** Last update Sat Jun  3 16:57:02 2017 romain pillot
*/

#include "util.h"

static bool     is_digit(char c)
{
  return (c >= '0' && c <= '9');
}

static int	private(const char *str, int i, int n, int s)
{
  if ((str[i] == '-' || str[i] == '+') && (i == 0 || !is_digit(str[i - 1])))
    return (private(str, i + 1, n, str[i] == '-' ? s * - 1 : s));
  else if (is_digit(str[i]))
    if ((((long)n * 10) + (str[i] - 48)) > 2147483647)
      return (0);
    else
      return (private(str, i + 1, (n * 10) + (str[i] - 48), s));
  else if (n == 0)
    return (-1);
  else
    return (n * s);
}

int	nbr_parseint(const char *str)
{
  if (str && *str == '0' && !(str[1]))
    return (0);
  return (private(str, 0, 0, 1));
}
