/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:08:53 by hfakou            #+#    #+#             */
/*   Updated: 2025/06/30 17:05:10 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_start_char(int c)
{
	return (ft_isalpha(c) || c == '_');
}

int	is_var_char(int c)
{
	return (ft_isalnum(c) || c == '_');
}

/*
 ** Advances the lexer to the next character in the input line.
 ** Updates the current character (`c`), position (`pos`), and read position (`read_pos`).
 **
 ** @param lexer - pointer to the lexer structure
 */

void	read_char(t_lexer *lexer)
{
	if (lexer->input[lexer->read_pos] == '\0')
	{
		lexer->c = 0;
		return ;
	}
	else
		lexer->c = lexer->input[lexer->read_pos];
	lexer->pos = lexer->read_pos;
	lexer->read_pos++;
}

t_lexer	lexer_new(char *str)
{
	t_lexer	l;

	l.input = str;
	l.read_pos = 0;
	l.c = 0;
	l.pos = 0;
	l.len = ft_strlen(str);
	read_char(&l);
	return (l);
}
