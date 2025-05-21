#include "minishell.h"
#include "minishell.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int ft_isspace(char c)
{
    if (c == ' ' || (c >= 9 && c <= 14))
        return (1);
    return (0);
}

t_token *create_token(char *str, int len, char *type)
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

t_token *tokenize(char *line)
{
    t_token *head = NULL;
    int i = 0;

    while (line[i])
    {
        if (ft_isspace(line[i]))
            i++;
        
        if ((line[i] == '>' || line[i] == '<') && line[i + 1] == line[i]) {
           add_token(&head, create_token(&line[i], 2, token_type(line[i], line[i + 1])));
            i += 2;
        }
        else if (line[i] == '>' || line[i] == '<' || line[i] == '|') {
            add_token(&head, create_token(&line[i], 1, token_type(line[i], '0')));
            i++;
        }
        else {
            int start = i;
            while (line[i] && !isspace(line[i]) && line[i] != '|' && line[i] != '<' && line[i] != '>')
                i++;
            add_token(&head, create_token(&line[start], i - start, token_type(line[i], '0')));
        }
    }
    return head;
}

char *token_type(char c, char next)
{
    if (c == '|')
        return ft_strdup("T_PIPE");
    else if (c == '<' && next == c)
        return ft_strdup("T_HERDOC");
    else if (c == '>' && next == c)
        return ft_strdup("T_APPEND");
    else if (c == '<')
        return ft_strdup("T_INPUT");
    else if (c == '>')
            return ft_strdup("T_OUTPUT");
    return ft_strdup("T_WORD");
}

void print_token(t_token *token)
{
    t_token *walk;

    walk = token;
    while (walk)
    {
        printf("%s type : [%s]\n", walk->value, walk->type);
        
        walk = walk->next;
    }
}
// 
int main(void)
{
    char *line;
    t_token *token = NULL;

    while (1)
    {
       line =  readline("minishell$ ");
       add_history(line);
        token = tokenize(line);
        print_token(token);
        free(line);
    }       
}
