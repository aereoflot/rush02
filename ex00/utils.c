#include "rush02.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str && str[i])
        i++;
    return (i);
}

int ft_isspace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' ||
            c == '\v' || c == '\f' || c == '\r');
}

int ft_isdigit(char c)
{
    return (c >= '0' && c <= '9');
}

int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i] && s1[i] == s2[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void ft_putstr(char *str)
{
    if (!str)
        return ;
    write(1, str, ft_strlen(str));
}
