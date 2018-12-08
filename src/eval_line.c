/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_line.c.                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:19:48 by ptruffau          #+#    #+#             */
/*   Updated: 2018/11/07 14:19:50 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_parser.h>

int ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' ||
		c == ' ')
		return (1);
	else
		return (0);
}

char	*ft_strndup(char *src, int len)
{
	char	*new;
	int		i;

	if (!(new = malloc(sizeof(char *) * len + 1)))
		return (NULL);
	i = 0;
	while (i < len && src[i] != '\0')
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}


static char *analyse(char *src)
{
	char *eval;
	int len;
	int j;
	int i;

	i = -1;
	len = ft_strlen(src);
	if (!(eval = ft_strnew(len)))
		return (NULL);
	while (src[++i])
	{
		if (ft_isspace(src[i]))
			eval[i] = ' ';
		else if (src[i] == '<')
			eval[i] = 'r';
		else if (src[i] == '>')
		{
			j = i;
			while (j > 0 && ft_isdigit(src[j - 1]))
				eval[--j] = 'r';
			eval[i] = 'r';
			if (i + 2 < len && src[i + 1] == '&')
			{
				eval[++i] = 'r';
				if (src[i + 1] == '-')
					eval[++i] = 'r';
				else
				{
					while (ft_isdigit(src[i + 1]))
						eval[++i] = 'r';
				}
			}
		}
		else if (src[i] == '&' || src[i] == '|' || src[i] == ';')
			eval[i] = 'o';
		else
			eval[i] = 'e';
	}
	eval[i] = 0;
	return (eval);
}

static t_word *find_type(t_word *w, char c, int *pos)
{
	if (c == 'o')
	{
		if (ft_strequ(w->word, "&&"))
			w->type = O_AND;
		else if (ft_strequ(w->word, "||"))
			w->type = O_OR;
		else if (ft_strequ(w->word, ";"))
			w->type = O_SEP;
		else
			w->type = 0;
		*pos = 0;
	}
	else if (c == 'r')
	{
		char *ptr;

		if ((ptr = ft_strchr(w->word, '>')))
			w->type = (*(ptr + 1) == '>'? R_DRIGHT : R_RIGHT);
		else if ((ptr = ft_strchr(w->word, '<')))
			w->type = (*(ptr + 1) == '<'? R_DLEFT : R_LEFT);
		else
			w->type = 0;
	}
	else if (c == 'e')
	{
		if (*pos == 0)
			w->type = CMD;
		else if (*w->word == '-')
			w->type = OPTION;
		else
			w->type = PATH;
		*pos = *pos + 1;
	}
	return (w);
}

static t_word *new_tword(void)
{
	t_word *n;

	if (!(n = (t_word *)malloc(sizeof(t_word))))
		return (NULL);
	n->word = NULL;
	n->type = undef;
	n->next = NULL;
	return (n);
}

static t_word *get_next_word(t_word *w, char *eval, char *input, int *i, int *pos)
{
	char c;
	int begin;

	while (eval[*i] == ' ')
		*i = *i + 1;
	c = eval[*i];
	begin = *i;
	while (eval[*i] == c)
		*i = *i + 1;
	 if (!(w->word = ft_strndup(input + begin, *i - begin)))
	 	return (w);
	 return (find_type(w, c, pos));
}

static t_word *ft_get_words(char *input, char *eval)
{
	t_word *head;
	t_word *tmp;
	int pos;
	int i;
	int len;

	i = 0;
	pos = 0;
	if (!(head = new_tword()) || !(head = get_next_word(head, eval, input, &i, &pos))
	|| eval[i] == 0)
		return (head);
	len = ft_strlen(input);
	tmp = head;
	while (i < len)
	{
		if (!(tmp->next = new_tword()))
			return (head);
		tmp = tmp->next;
		if (!(tmp = get_next_word(tmp, eval, input, &i, &pos)))
			return (head);
	}
	return (head);
}

t_word *eval_line(char *input)
{
	t_word *head;
	char *eval;

	if (!input|| !*input|| !(eval = analyse(input)))
		return (NULL);
	head = ft_get_words(input, eval);
	ft_strdel(&eval);
	return (head);
}