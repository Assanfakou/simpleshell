#include "minishell.h"

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

t_token *tokenize(char *line)
{
    int start;
    t_token *head = NULL;
    int i = 0;
    char c;

    while (line[i])
    {
        if (ft_isspace(line[i]))
            i++;
        
        if ((line[i] == '>' || line[i] == '<') && line[i + 1] == line[i]) {
           add_token(&head, create_token(&line[i], 2, token_type(line[i], line[i + 1])));
            i += 2;
        }
        else if (line[i] == '>' || line[i] == '<' || line[i] == '|') {
            add_token(&head, create_token(&line[i], 1, T_WORD));
            i++;
        }
        else if (line[i] == '\"' || line[i] == '\'')
        {
            if (line[i] == '\"')
                c = '\"';
            else
                c = '\'';
            i++;
            start = i;
            while (line[i] && line[i] != c)
                i++;
            if (line[i] == '\0')
                exit(1);
            i++;
            add_token(&head, create_token(&line[start], (i - 1) - start, T_WORD));
        }
        else {
            start = i;
            while (line[i] && !isspace(line[i]) 
            && line[i] != '|' && line[i] != '<' 
            && line[i] != '>' 
            && line[i] != '\'' && line[i] != '\"')
                i++;
            add_token(&head, create_token(&line[start], i - start, T_WORD));
        }
    }
    return head;
}
void    ft_

// void add_command(t_cmd **head, t_cmd *new)
// {
//     if (!*head)
//         *head = new;
//     else {
//         t_token *temp = *head;
//         while (temp->next)
//             temp = temp->next;
//         temp->next = new;
//     }
// }
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
