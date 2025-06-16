
#include "lexer.h"

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
