#include "../libft/libft.h"
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
char *expand_variable(char *variable)
{
    int here;
    size_t len;
    char *result = ft_strdup("");
    size_t i;

        len = ft_strlen(variable);
        if (len >= 2)
                return (ft_strdup(variable));
        i = 0;
        while (variable[i])
        {
            if (variable[i] == '$')
	    {
                if (variable[i + 1] == '?')
                {
                    result = ft_itoa(2);
		    printf("kkdd\n");
                    i += 2;
                }
                if (is_start_char(variable[i + 1]))
                {
                    size_t j = i;
                    while (is_var_char(variable[j]))
                            j++;
                    char *val = getenv(ft_substr(variable, i, j - i));
                    if (val)
                    {
                        size_t val_len = ft_strlen(val);
                        result = ft_calloc(val_len + 1, 1);
                        ft_memcpy(result, val, val_len);
                    }
                    i = j;
                }
            }
	    else
	    {
		    char t[2] = { variable[i++], 0 };
		    char *tmp = ft_strjoin(result, t);
		    free(result);
		    result = tmp;
	    }
	}
        return (result);
}
int main (int ac, char **av)
{
	char *pa = expand_variable(av[1]);
	printf("%s\n", pa);
}


