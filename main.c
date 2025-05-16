#include "minishell.h"

void parse_data(t_cmd *comd, char *line)
{
    int i = 0;
    int j;

    while (line)
    {
        if (line[i] == '\'')
            printf("hello\n");
    }
}

int main(void)
{
    char *line;
    t_cmd cmd;

    while (1)
    {
        line = readline("minishell$ ");
        parse_data(&cmd, line);
        if (!line)
            break;
        // printf("%s\n", line);
        free(line);
    }
    return 0;
}