#include "minishell.h"

void add_command(t_cmd **head, t_cmd *new)
{
    if (!*head)
        *head = new;
    else {
        t_cmd *temp = *head;
        while (temp->next)
            temp = temp->next;
        temp->next = new;
    }
}
