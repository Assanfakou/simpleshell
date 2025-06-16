/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:34:33 by hfakou            #+#    #+#             */
/*   Updated: 2025/06/15 19:45:55 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "string.h"
#include "stdlib.h"
#include "readline/readline.h"
#include "readline/history.h"
#include <stdbool.h>

typedef struct s_lexer	{
	char 	*input;
	char 	c;
	size_t 	pos; // index of c
	size_t 	len; // length of input
	size_t 	read_pos; // next char index
} t_lexer;


typedef enum s_token_type
{
	TOK_NULL = 0,
	TOK_PIPE,
	TOK_INPUT,
	TOK_OUTPUT,
	TOK_HERDOC,
	TOK_APPAND,
	TOK_WORD,
	TOK_DOUBLE,
	TOK_SINGLE,
	TOK_INVALID,
	TOK_NONE
} t_token_type;

typedef struct s_token
{
	t_token_type type;
	char *literal;
	size_t len;
	bool space;
} t_token;

# define UNIMPLEMENTED(...) printf("%s:%d: UNIMPEMENTED: %s \n", __FILE__, __LINE__, __VA_ARGS__); \
	exit(1);

void token_print(t_token token);
t_token lexer_next_token(t_lexer *lexer);
t_token token_redir(t_lexer *lexer);
t_token token_s_d_word(t_lexer *lexer);
bool skip_white_space(t_lexer *lexer);
int ft_isspace(char c);
t_token token_new(char *s, t_token_type type, size_t len);
t_lexer lexer_new(char *str);
void	read_char(t_lexer *lexer);
void print_lexer(t_lexer *lexer);
