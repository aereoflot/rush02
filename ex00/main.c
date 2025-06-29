#include "rush02.h"

static int is_valid_numeric(char *str)
{
    int i;

    i = 0;
    if (!str || !str[0])
        return (0);
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

static unsigned long long ft_atoi_u64(char *str)
{
    unsigned long long res;
    int                 i;

    res = 0; i = 0;
    while (ft_isspace(str[i]))
        i++;
    while (ft_isdigit(str[i]))
    {
        res = res * 10 + (str[i] - '0');
        i++;
    }
    return (res);
}

static int handle_args(int argc, char **argv, char **dict_file, char **num_str)
{
    if (argc == 2)
    {
        *dict_file = "numbers.dict";
        *num_str = argv[1];
    }
    else if (argc == 3)
    {
        *dict_file = argv[1];
        *num_str = argv[2];
    }
    else
        return (0);
    return (is_valid_numeric(*num_str));
}

int main(int argc, char **argv)
{
    char    *dict_file;
    char    *num_str;
    int     dict_size;
    t_dict  *dict;
    int     i;

    dict_size = 0;
    if (!handle_args(argc, argv, &dict_file, &num_str))
        return (write(1, "Error\n", 6), 0);
    dict = parse_dict(dict_file, &dict_size);
    if (!dict)
        return (write(1, "Dict Error\n", 11), 0);
    print_number(ft_atoi_u64(num_str), dict, dict_size, 1);
    write(1, "\n", 1);
    i = 0;
    while (i < dict_size)
        free(dict[i++].value);
    free(dict);
    return (0);
}
