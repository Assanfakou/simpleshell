/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:08:43 by marvin            #+#    #+#             */
/*   Updated: 2025/05/26 13:24:408 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_status = 0; // 1 or 0 for $?

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
        {
            i++;
            continue;
        }
        
        if ((line[i] == '>' || line[i] == '<') && line[i + 1] == line[i]) {
           add_token(&head, create_token(&line[i], 2, token_type(line[i], line[i + 1])));
            i += 2;
        }
        else if (line[i] == '>' || line[i] == '<' || line[i] == '|') {
            add_token(&head, create_token(&line[i], 1, token_type(line[i], line[i + 1])));
            i++;
        }
        else if (line[i] == '\"' || line[i] == '\'')
        {
            if (line[i] == '\"')
                c = '\"';
            else
                c = '\'';
            start = i;
            i++;
            while (line[i] && line[i] != c)
                i++;
            if (line[i] == '\0')
            {
                ft_error("double quots doesn't closed");
                break;
            }
            i++;
            add_token(&head, create_token(&line[start], i - start, T_WORD));
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

int is_start_char(int c) 
{ 
    return ft_isalpha(c) || c == '_'; 
}

int is_var_char(int c)   
{ 
    return ft_isalnum(c) || c == '_'; 
}

void expand_variables(t_token *head)
{
    while (head)
    {
        char *src = head->value;
        size_t len = strlen(src);

        // Skip expansion for tokens inside single quotes: '...'
        if (len >= 2 && src[0] == '\'' && src[len - 1] == '\'')
        {
            head = head->next;
            continue;
        }

        // Preallocate buffer (4x size for safe expansion room)
        char *result = calloc(len * 4 + 1, 1);
        size_t ri = 0; // write index

        size_t i = 0;
        while (src[i])
        {
            if (src[i] == '$')
            {
                if (src[i + 1] == '?')
                {
                    char *exit_code = ft_itoa(g_exit_status);
                    size_t ec_len = strlen(exit_code);
                    memcpy(result + ri, exit_code, ec_len);
                    ri += ec_len;
                    free(exit_code);
                    i += 2;
                    continue;
                }
                else if (is_start_char((unsigned char)src[i + 1]))
                {
                    size_t j = i + 1;
                    while (is_var_char((unsigned char)src[j])) j++;

                    char *name = ft_substr(src, i + 1, j - (i + 1));
                    char *val = getenv(name);  // use ft_getenv if needed
                    if (val)
                    {
                        size_t val_len = strlen(val);
                        memcpy(result + ri, val, val_len);
                        ri += val_len;
                    }
                    free(name);
                    i = j;
                    continue;
                }
            }
            // Ordinary character
            result[ri++] = src[i++];
        }

        result[ri] = '\0';

        free(head->value);
        head->value = result;

        head = head->next;
    }
}

void    ft_error(char *error)
{
    printf("%s\n", error);
}

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
        expand_variables(token);
        print_token(token);
        free(line);
    }       
}
