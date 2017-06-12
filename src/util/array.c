/*
** key_array.c for  in /home/romain.pillot/projects/ghoulc/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Tue May 23 14:48:44 2017 romain pillot
** Last update Tue May 30 14:38:55 2017 romain pillot
*/

#include <stdlib.h>
#include <unistd.h>
#include "array.h"

t_array		*array_create()
{
  t_array	*array;

  if (!(array = malloc(sizeof(t_array))))
    return (NULL);
  array->values = NULL;
  array->length = 0;
  return (array);
}

void		array_destroy(t_array **array_addr, bool free_content)
{
  int		i;
  t_array	*array;

  if (!array_addr || !(array = *array_addr))
    return ;
  if (free_content && array->values)
    {
      i = -1;
      while (array->values[++i])
	free(array->values[i]);
    }
  if (array->values)
    free(array->values);
  free(array);
  *array_addr = 0;
}

void	array_add(t_array *array, void *elem)
{
  void	**new;
  int	len;

  if (!elem || !array ||
      !(new = malloc(sizeof(void *) * ((len = array->length) + 2))))
    return ;
  new[len + 1] = 0;
  new[len] = elem;
  while (len--)
    new[len] = array->values[len];
  free(array->values);
  array->values = new;
  array->length++;
}

void		array_del(t_array *array, const int index, bool free_elem)
{
  const void	*addr;
  void		**new;
  int		i;
  int		j;

  if (!array || index >= array->length || index < 0 ||
      !(new = malloc(sizeof(void *) * (array->length))))
    return ;
  new[array->length - 1] = 0;
  addr = array->values + index;
  i = (j = -1);
  while (array->values[++i])
    if (array->values + i != addr)
      new[++j] = array->values[i];
  if (free_elem)
    free(array->values[index]);
  free(array->values);
  array->values = new;
  array->length--;
}
