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

    if (!token)
        return ;
    walk = token;
    while (walk)
    {
        printf("%s type : [%d]\n", walk->value, walk->type);
        
        walk = walk->next;
    }
}
int is_operator(char c)
{
    if (c == '|' || c == '<' || c == '>')
        return (1);
    else
        return (0);
}

int is_redir_or_pipe(char *line, int i)
{
    if (((line[i] == '>' || line[i] == '<') && line[i + 1] == line[i]) || is_operator(line[i]))
        return (1);
    else
        return (0);
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
    tok->value = ft_strndup(str, len);
    tok->type = type;
    tok->next = NULL;
    return tok;
}

void add_token(t_token **head, t_token *new)
{
    if (!*head)
        *head = new;
    else 
    {
        t_token *temp = *head;
        while (temp->next)
            temp = temp->next;
        temp->next = new;
    }
}
int parce_pipe_redi(char *line, int i, t_token **head)
{
    char c;
    int start;
    
    if ((line[i] == '>' || line[i] == '<') && line[i + 1] == line[i])
    {
        add_token(head, create_token(line + i , 2, token_type(line[i], line[i + 1])));
        i += 2;
    }
    else if (line[i] == '>' || line[i] == '<' || line[i] == '|')
    {
        add_token(head, create_token(line + i, 1, token_type(line[i], line[i + 1])));
        i++;
    }
    return (i);
}
char *parce_d_s_quotes(char *line, int *i)
{
    char c;
    size_t start;

    if (line[*i] == '\"')
        c = '\"';
    else
        c = '\'';
    start = *i;
    (*i)++;
    while (line[*i] && line[*i] != c)
        (*i)++;
    if (line[*i] == '\0')
    {
        ft_print_error("minishell: syntax error: unmatched quote");
        return (NULL);
    } 
    (*i)++;
    // add_token(head, create_token(line + start, *i - start, T_WORD));
    return (ft_strndup(line + start, *i - start));
}

void free_t_token(t_token **head)
{
    t_token *temp;

    if (!*head)
        return ;

    while (*head)
    {
        free((*head)->value);
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    *head = NULL;
}
char  *extract_word(char *line, int *i, t_token **head)
{
    char *word;
    char *h;

    while (line[*i] && !isspace(line[*i]) && !is_operator(line[*i]))
    {
        word = ft_strdup("");
        if (line[*i] == '\"' || line[*i] == '\'')
        {
            h = parce_d_s_quotes(line, &i);
            if (!h)
                return (NULL);
            char *temp = ft_strjoin(word, h);
            free(word);
            free(h);
            word = temp;
        }
        else
        {
            char t[2] = {line[(*i)++], 0};
            char *tmp = ft_strjoin(word, t);
            free(word);
            word = tmp;
        }
    }
    add_token(head, create_token(word, ft_strlen(word), T_WORD));
}