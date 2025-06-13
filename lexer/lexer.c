#include <stdio.h>
#include "lexer.h"
#include "string.h"
#include "stdlib.h"
#include "readline/readline.h"
void print_lexer(t_lexer *lexer)
{
	printf("Input: \"%s\"\n", lexer->input);
	printf("char: %c;%zu\n", lexer->c, lexer->pos);
	printf("Future index: %zu\n", lexer->read_pos);
}


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
	t_lexer l;

	l.input = str;
	l.read_pos = 0;
	l.c = 0;
	l.pos = 0;
	l.len = strlen(str);
	read_char(&l);
	return (l);
}
t_token token_new(char *s, t_token_type type, size_t len)
{
	t_token tok;

	tok.literal = s;
	tok.type = type;
	tok.len = len;

	return (tok);
}
int ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return 1;
	else 
		return (0);
}
t_token token_word(t_lexer *lexer)
{
	t_token tok;

	tok.literal = &lexer->input[lexer->pos];
	tok.len = 0;
	while (lexer->c && lexer->c != '|' && lexer->c != '<' && lexer->c != '>' && lexer->c != '\'' && lexer->c != '\"' && !ft_isspace(lexer->c))
	{
		tok.len++;
		read_char(lexer);
	}
	tok.type = TOK_WORD;
	return (tok);
}
	
void skip_white_space(t_lexer *lexer)
{
	while ((lexer->c >= 9 && lexer->c == 13) || lexer->c == 32)
		read_char(lexer);
}
t_token token_s_d_word(t_lexer *lexer)
{
	t_token tok;
	char c;

	if (lexer->c == '\'')
		c = '\'';
	else
		c = '\"';	
	read_char(lexer);
	tok.literal = &lexer->input[lexer->pos];
	tok.len = 0;
	while (lexer->c && lexer->c != c)
	{
		tok.len++;
		read_char(lexer);
	}
	if (lexer->c == '\0')
	{
		printf("unmatched quote\n");
		return (tok);
	}
	read_char(lexer);
	if (c == '\'')
		tok.type = TOK_SINGLE;
	else
		tok.type = TOK_DOUBLE;
	return (tok);
}
t_token lexer_next_token(t_lexer *lexer)
{
	t_token tok;

	skip_white_space(lexer);
	if (lexer->c == '<')
	{
		tok = token_new(&lexer->input[lexer->pos], TOK_INPUT, 1);
		read_char(lexer);
	}
	else if (lexer->c == '>')
	{
		tok = token_new(&lexer->input[lexer->pos], TOK_OUTPUT, 1);
		read_char(lexer);
	}
	else if (lexer->c == '|')
	{
		tok = token_new(&lexer->input[lexer->pos], TOK_PIPE, 1);
		read_char(lexer);
	}
	else if (lexer->c == '\0')
		tok = token_new(NULL, TOK_NULL, 0);
	else if (lexer->c == '\'' || lexer->c == '\"')
		tok = token_s_d_word(lexer);
	else
		tok = token_word(lexer);
	return (tok);
}
void token_print(t_token token)
{
	if (token.type == TOK_INPUT)
		printf("(TOK_IN)");
	else if (token.type == TOK_OUTPUT)
		printf("(TOK_OUT)");
	else if (token.type == TOK_PIPE)
		printf("(TOK_PIPE)");
	else if (token.type == TOK_NULL)
		printf("(nil)");
	else if (token.type == TOK_WORD)
		printf("(TOK_WORD)");
	else if (token.type == TOK_SINGLE)
		printf("(TOK_SINGLE)");
	else if (token.type == TOK_DOUBLE)
		printf("(TOK_DOUBLE)");
	else
	{
		UNIMPLEMENTED("INVALID TOKRN RECEIVED");
	}
	printf(" \"%.*s\"\n", (int) token.len, token.literal);
}
		
int main()
{
	t_lexer lexer;
	t_token tok;


	while (1)
	{
		char *input = readline("hello world# ");

		lexer = lexer_new(input);
		printf("%s\n", input);
		tok = lexer_next_token(&lexer);
		while (tok.type)
		{
			token_print(tok);
			//print_lexer(&lexer);
			tok = lexer_next_token(&lexer);
		}
	}
}
