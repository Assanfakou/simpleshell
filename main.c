/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 19:17:48 by hfakou            #+#    #+#             */
/*   Updated: 2025/06/11 19:58:40 by hfakou           ###   ########.fr       */
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
        else if (((line[i] == '>' || line[i] == '<') && line[i + 1] == line[i]) || (line[i] == '>' || line[i] == '<' || line[i] == '|'))
            i = parce_pipe_redi(line, i, &head);
        else if (line[i] == '\"' || line[i] == '\'')
        {
            i = parce_d_s_quotes(line, i, &head);
            if (i == 0)
                return (NULL);
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

    while (head)
    {
        here = 0;
        src = head->value;
        len = ft_strlen(src);
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
                    result = ft_itoa(g_exit_status);
                    i += 2;
                    continue;
                }
                else if (is_start_char(src[i + 1]))
                {
                    size_t j = i + 1;
                    while (is_var_char(src[j])) 
                        j++;
                    char *val = getenv(ft_substr(src, i + 1, j - (i + 1)));
                    if (val)
                    {
                        here = 1;
                        size_t val_len = ft_strlen(val);
                        result = ft_calloc(val_len + 1, 1);
                        ft_memcpy(result, val, val_len);
                    }
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
void check_errors(t_token **head)
{
    t_token *step;
    int i;
    if (!*head)
        return ;

    step = *head;
    if (step->type == T_PIPE)
    {
        ft_print_error("minishell: syntax error near unexpected token `|'");
        g_exit_status = 2;
        free_t_token(head);
        return ;
    }
    while (step->next)
    {
        if (step->type == T_PIPE && step->next->type != T_WORD)
        {
            printf("minishell: syntax error near unexpeted token `%s'\n", step->next->value);
            g_exit_status = 2;
            free_t_token(head);
            return ;
        }
        else if (step->type == T_HERDOC || step->type == T_OUTPUT || step->type == T_INPUT || step->type == T_APPAND)
        {
            if (step->next->type != T_WORD)
            {
                 printf("minishell: syntax error near unexpeted token `%s'\n", step->next->value);
                g_exit_status = 2;
                free_t_token(head);
                return ;
            }
        }
        step = step->next;
    }
    if (step->type == T_PIPE)
    {
        ft_print_error("minishell: syntax error near unexpected token `|'");
        g_exit_status = 2;
        free_t_token(head);
        return ;
    }
}

void    ft_print_error(char *error)
{
    write(2, error, ft_strlen(error));
    write (2, "\n", 1);
}

int main(void)
{
    char *line;
    t_token *token = NULL;

    while (1)
    {
        line = readline("minishell$ ");
        add_history(line);
        token = tokenize(line);
        expand_variables(token);
        check_errors(&token);
        if (token)
            print_token(token);
        free(line);
    }       
}
