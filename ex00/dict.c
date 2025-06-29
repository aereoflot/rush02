#include "rush02.h"

static int  skip_spaces(char *str, int i)
{
    while (str[i] && ft_isspace(str[i]))
        i++;
    return (i);
}

static int  is_valid_number(char *str)
{
    int i;

    i = 0;
    if (!str[i])
        return (0);
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

static t_dict    *add_entry(t_dict *dict, int *size,
                            unsigned long long key, char *val)
{
    t_dict  *new;
    int     i;

    new = (t_dict *)malloc(sizeof(t_dict) * (*size + 1));
    if (!new)
        return (NULL);
    i = 0;
    while (i < *size)
    {
        new[i] = dict[i];
        i++;
    }
    new[*size].key = key;
    new[*size].value = val;
    free(dict);
    (*size)++;
    return (new);
}

static int  process_line(char *line, t_dict **dict, int *size)
{
    int                 i;
    int                 nidx;
    char                num[40];
    char                *val;
    unsigned long long  key;

    i = 0; nidx = 0;
    while (line[i] && ft_isspace(line[i]))
        i++;
    while (line[i] && line[i] != ':' && !ft_isspace(line[i]))
        num[nidx++] = line[i++];
    num[nidx] = '\0';
    i = skip_spaces(line, i + (line[i] == ':'));
    val = ft_strdup_trim(line + i);
    if (!num[0] || !val || !is_valid_number(num))
        return (free(val), 1);
    key = 0; i = 0;
    while (num[i])
        key = key * 10 + (num[i++] - '0');
    *dict = add_entry(*dict, size, key, val);
    if (!*dict)
        return (0);
    return (1);
}

t_dict  *parse_dict(char *file, int *size)
{
    int     fd;
    char    line[1024], c;
    int     idx;
    t_dict  *dict;

    idx = 0; dict = NULL;
    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (NULL);
    while (read(fd, &c, 1) > 0)
    {
        if (c == '\n' || idx >= 1023)
        {
            line[idx] = '\0';
            if (!process_line(line, &dict, size))
                return (close(fd), NULL);
            idx = 0;
        }
        else
            line[idx++] = c;
    }
    close(fd);
    return (dict);
}
