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

t_token *tokenize(char *line)
{
    int start;
    t_token *head = NULL;
    int i = 0;

    while (line[i])
    {
        if (ft_isspace(line[i]))
        {
            i++;
            continue;
        }
        i = parce_pipe_redi(line, i, head);
        if (line[i] == '\"' || line[i] == '\'')
        {
            i = parce_d_s_quotes(line, i, head);
            if (i == 0)
            {
                ft_print_error("minishell: syntax error: unmatched quote");
                break;
            }
        }
        else 
        {
            start = i;
            while (line[i] && !isspace(line[i]) && line[i] != '|' && line[i] != '<' 
            && line[i] != '>' && line[i] != '\'' && line[i] != '\"')
                i++;
            add_token(&head, create_token(line + start, i - start, T_WORD));
    }
    }
    return head;
}


void expand_variables(t_token *head)
{
    int here;
    char *src;
    size_t len;
    char *result;
    size_t i;
    char *exit_code;

    while (head)
    {
        here = 0;
        src = head->value;
        len = strlen(src);
        if (len >= 2 && src[0] == '\'' && src[len - 1] == '\'')
        {
            head = head->next;
            continue;
        }
        i = 0;
        while (src[i])
        {
            if (src[i] == '$')
            {
                if (src[i + 1] == '?')
                {
                    here = 1;
                    exit_code = ft_itoa(g_exit_status);
                    size_t ec_len = ft_strlen(exit_code);
                    result = exit_code;
                    i += 2;
                    continue;
                }
                if (is_start_char(src[i + 1]))
                {
                    here = 1;
                    size_t j = i + 1;
                    while (is_var_char(src[j])) 
                        j++;

                    char *name = ft_substr(src, i + 1, j - (i + 1));
                    char *val = getenv(name);
                    if (val)
                    {
                        size_t val_len = ft_strlen(val);
                        result = ft_calloc(val_len + 1, 1);
                        ft_memcpy(result, val, val_len);
                    }
                    free(name);
                    i = j;
                    continue;
                }
            }
            else
                i++;
        }
        if (here)
        {
            free(head->value);
            head->value = result;
        }
            head = head->next;
    }
}
void check_errors(t_token *head)
{
    char *src;
    int i;

    if (head->type == T_PIPE)
    {
        ft_print_error("minishell: syntax error near unexpected token `|'");
        g_exit_status = 2;
    }
    // while (head)
    // {
    //     src = head->value;
    

}

void    ft_print_error(char *error)
{
    write(2, error, ft_strlen(error));
    write (2, "\n", 1);
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
        check_errors(token);
        print_token(token);
        free(line);
    }       
}
