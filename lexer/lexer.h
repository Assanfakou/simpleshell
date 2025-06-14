/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:34:33 by hfakou            #+#    #+#             */
/*   Updated: 2025/06/14 12:19:56 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "string.h"
#include "stdlib.h"
#include "readline/readline.h"
#include "readline/history.h"


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
	TOK_WORD,
	TOK_DOUBLE,
	TOK_SINGLE,
	TOK_INVALID
} t_token_type;

typedef struct
{
	t_token_type type;
	char *literal;
	size_t len;
} t_token;

# define UNIMPLEMENTED(...) printf("%s:%d: UNIMPEMENTED: %s \n", __FILE__, __LINE__, __VA_ARGS__); \
	exit(1);

