
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  ft_parsing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 23:39:07 by ktlili            #+#    #+#             */
/*   Updated: 2018/10/05 18:35:37 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSING_H
# define FT_PARSING_H

#include "minishell.h"

#define CMD 2
#define SEP 1
#define PIPE 
//  invalid write dans eval_line.c ligne 164 et 146 si ya que des 
// espaces ou si ya des espaces vers la fin, c'est un peu random
 
enum e_type{ /* les pipes? les quotes " et ' c'est a gerer a 
                            ce niveau aussi*/
      undef = 0,
      O_AND = 1, // comme ;
      O_OR = 2, // comme ;
      O_SEP = 3, // plus qu'un ; sont reconnu comme undef
      R_LEFT = 4,
      R_RIGHT = 5,
      R_DLEFT = 6,
      R_DRIGHT = 7,
      CMD_ = 8, // les cmd sont reconnu comme O_OR
      OPTION = 9, // pas besoin de reconnaitre les options. sinon on 
      PATH = 10  // oblige de gerer les -- 
  };

typedef struct s_word
{
	enum e_type 	type;
	char 			*word;
	struct s_word 	*next;
}				t_word;


typedef enum	e_node_type
{
	e_pipe, sep, cmd
}				t_node_type;

typedef struct	s_tree
{
	t_node_type		type;
	t_command		*data;
	struct s_tree	*left;
	struct s_tree	*right;
}				t_tree;


t_word *eval_line(char *input);
//tree building
int	ft_build_tree(char *line, t_tree **tree);
t_tree	*tr_new_node(int type);
int add_cmd(t_tree *node, t_tree **head);
int add_pipe(t_tree *node, t_tree **head);
int add_sep(t_tree *node, t_tree **head);
//syntax.c
int	assert_syntax(t_tree *head, int level);
// eval.c
int	eval_tree(t_tree *tree);
//util
void free_tree(t_tree *head);
#endif
