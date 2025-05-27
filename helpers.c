#include "minishell.h"

t_type token_type(char c, char next)
{
    if (c == '|')
        return T_PIPE;
    else if (c == '<' && next == c)
        return T_HERDOC;
    else if (c == '>' && next == c)
        return T_APPAND;
    else if (c == '<')
        return T_INPUT;
    else if (c == '>')
            return T_OUTPUT;
    return T_WORD;
}

void print_token(t_token *token)
{
    t_token *walk;

    walk = token;
    while (walk)
    {
        printf("%s type : [%d]\n", walk->value, walk->type);
        
        walk = walk->next;
    }
}
int is_start_char(int c) 
{ 
    return ft_isalpha(c) || c == '_'; 
}

int is_var_char(int c)   
{ 
    return ft_isalnum(c) || c == '_'; 
}
int ft_isspace(char c)
{
    if (c == ' ' || (c >= 9 && c <= 14))
        return (1);
    return (0);
}

t_token *create_token(char *str, int len, t_type type)
{
    t_token *tok = malloc(sizeof(t_token));
    tok->value = strndup(str, len);
    tok->type = type;
    tok->next = NULL;
    return tok;
}

void add_token(t_token **head, t_token *new)
{
    if (!*head)
        *head = new;
    else {
        t_token *temp = *head;
        while (temp->next)
            temp = temp->next;
        temp->next = new;
    }
}