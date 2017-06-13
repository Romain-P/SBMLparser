/*
** main.h for  in /home/romain.pillot/bin
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Thu Nov 24 11:15:51 2016 romain pillot
** Last update Tue Jun 13 15:32:38 2017 romain pillot
*/

#ifndef PARSER_H_
# define PARSER_H_

# define _EXIT_SUCCESS		(0)
# define _EXIT_FAILURE		(84)

# define SEP_PARAM_OPEN		('<')
# define SEP_PARAM_CLOSE	('>')
# define SEP_PROP_END		('/')
# define SEP_PAIR		('=')

# define HEADER			("<?xml")

# include "array.h"

typedef enum	s_tagtype
{
  UNDEFINED,
  COMPARTMENT,
  SPECIES,
  REACTION,
  SPECIES_REF,
  LIST_COMPARTMENTS,
  LIST_SPECIES,
  LIST_REACTIONS,
  LIST_REACTANTS,
  LIST_PRODUCTS
}		t_tagtype;

typedef struct		s_tag
{
  t_tagtype const	type;
  char const		* const name;
}			t_tag;

typedef struct	s_pair
{
  char		*key;
  char		*value;
}		t_pair;

typedef struct	s_options
{
  char		*id;
  bool		print_equation;
  bool		json_format;
}		t_options;

typedef struct		s_property
{
  char			*name;
  t_tagtype		tagtype;
  t_array		*parameters;
  struct s_property	*parent;
  t_array		*sub_properties;
}			t_property;

t_property	*load_data(const int fd);

t_options	*load_options(int ac, char **args, bool debug);

void		display(t_property *data, t_options *options);

void		display_list(t_property *list, char const *param);

char		*get_consumed(t_property **props, char const *id);

t_property	*property_create(const char *name, t_property *parent);

bool		property_exists(t_property **props, t_property *prop);

t_property	*property_findbyid(t_property **props, char const *id);

char		*property_getvalue(t_property *property, char const *key);

t_property	*property_findbytype(t_property **pros, t_tagtype type);

void		property_destroy(t_property *property, bool recursively);

char		*property_name(const char *str);

void		property_sort_full(t_property **props);

#endif /** !PARSER_H_ **/
