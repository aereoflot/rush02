#include "rush02.h"

char    *ft_strdup_trim(char *src)
{
    int     start;
    int     end;
    char    *dup;
    int     i;

    start = 0;
    while (src[start] && ft_isspace(src[start]))
        start++;
    end = ft_strlen(src) - 1;
    while (end > start && ft_isspace(src[end]))
        end--;
    dup = (char *)malloc(end - start + 2);
    if (!dup)
        return (NULL);
    i = 0;
    while (start <= end)
        dup[i++] = src[start++];
    dup[i] = '\0';
    return (dup);
}

char    *ft_strjoin_free(char *s1, char *s2)
{
    int     len1;
    int     len2;
    char    *res;
    int     i;
    int     j;

    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    res = (char *)malloc(len1 + len2 + 2);
    if (!res)
        return (NULL);
    i = -1;
    while (s1 && s1[++i])
        res[i] = s1[i];
    if (i)
        res[i++] = ' ';
    j = 0;
    while (s2 && s2[j])
        res[i++] = s2[j++];
    res[i] = '\0';
    free(s1);
    return (res);
}
