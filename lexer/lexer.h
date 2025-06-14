/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:34:33 by hfakou            #+#    #+#             */
/*   Updated: 2025/06/14 18:21:35 by hfakou           ###   ########.fr       */
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


typedef enum
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
	TOK_INVALID
} t_token_type;

typedef enum s_redir_type
{
    R_HERDOC,
    R_OUTPUT,
    R_INPUT,
    R_APPAND,
} t_redir_type;

typedef struct s_redir
{
    t_redir_type type;
    char *filename;
    struct s_redir *next;
}   t_redir;

typedef struct s_cmd
{
    char **argv; // array of pointers to store commands with arguments 
    t_redir *redir; // list of rredirections if there any of them
    struct s_cmd *next; // if there is a pipe we creat another t_cmd to store the other arguments after the pipe
}   t_cmd;

typedef struct
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
