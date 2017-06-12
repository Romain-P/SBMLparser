/*
** list.h for  in /home/romain.pillot/projects/CPE_2016_corewar/vm/include
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Thu Mar 30 11:48:07 2017 romain pillot
** Last update Sun Apr  2 20:17:51 2017 romain pillot
*/

#ifndef LIST_H_
# define LIST_H_

# include <stdbool.h>

typedef struct	s_elem
{
  void		*get;
  struct s_elem	*next;
  struct s_elem	*previous;
}		t_elem;

typedef struct	s_list
{
  t_elem	*first;
  t_elem	*last;
  int		size;
}		t_list;

/*
** @Return a new double-linked list
*/
t_list		*list_create();

/*
** Add a new elem to a list
** @Return the data cast as t_elem
*/
t_elem		*list_add(t_list *list, void *data);

/*
** Remove a given data by its addresse (note void **data)
** @Return the data contained by the elem, previously removed
**	   from the given list.
*/
void		*list_dremove(t_list *list, void **data);

/*
** Remove a given elem from the list
** @Return the data contained by the elem, previously removed
**	   from the given list.
*/
void		*list_eremove(t_list *list, t_elem *elem);

/*
** Free all
*/
void		list_removeall(t_list *list, bool free_data);

#endif /* !LIST_H_ */
