#include "lexer.h"

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
t_lexer lexer_new(char *str)
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
