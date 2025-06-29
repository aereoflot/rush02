-- Makefile ------------------------------------------------------------------
NAME	=	rust-02
SRCS	=	main.c utils.c dict.c number.c
OBJS	=	$(SRCS:.c=.o)
CC	=	cc
CFLAGS	=	-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

-- rush02.h ------------------------------------------------------------------
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush02.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <you>                                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 12:00:00 by <you>             #+#    #+#             */
/*   Updated: 2025/06/29 12:00:00 by <you>            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef RUSH02_H
# define RUSH02_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_dict
{
    unsigned long long  key;
    char                *value;
}   t_dict;

int     ft_strlen(char *str);
int     ft_isspace(char c);
int     ft_isdigit(char c);
int     ft_strcmp(char *s1, char *s2);
char    *ft_strdup_trim(char *src);
char    *ft_strjoin_free(char *s1, char *s2);
t_dict  *parse_dict(char *file, int *size);
char    *dict_lookup(t_dict *dict, int size, unsigned long long key);
void    ft_putstr(char *str);
void    print_number(unsigned long long nb, t_dict *dict, int size, int is_first);

#endif

-- utils.c --------------------------------------------------------------------
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <you>                                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 12:00:00 by <you>             #+#    #+#             */
/*   Updated: 2025/06/29 12:00:00 by <you>            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "rush02.h"

int ft_strlen(char *str)
{
    int i = 0;
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
    int i = 0;
    while (s1[i] && s1[i] == s2[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char *ft_strdup_trim(char *src)
{
    int start = 0;
    int end;
    char *dup;
    int i = 0;

    while (src[start] && ft_isspace(src[start]))
        start++;
    end = ft_strlen(src) - 1;
    while (end > start && ft_isspace(src[end]))
        end--;
    dup = (char *)malloc(end - start + 2);
    if (!dup)
        return (NULL);
    while (start <= end)
        dup[i++] = src[start++];
    dup[i] = '\0';
    return (dup);
}

void ft_putstr(char *str)
{
    if (!str)
        return ;
    write(1, str, ft_strlen(str));
}

char *ft_strjoin_free(char *s1, char *s2)
{
    int len1 = ft_strlen(s1);
    int len2 = ft_strlen(s2);
    char *res;
    int i = 0;
    int j = 0;

    res = (char *)malloc(len1 + len2 + 2);
    if (!res)
        return (NULL);
    while (s1 && s1[i])
    {
        res[i] = s1[i];
        i++;
    }
    if (i != 0)
        res[i++] = ' ';
    while (s2 && s2[j])
        res[i++] = s2[j++];
    res[i] = '\0';
    free(s1);
    return (res);
}

-- dict.c ---------------------------------------------------------------------
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <you>                                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 12:00:00 by <you>             #+#    #+#             */
/*   Updated: 2025/06/29 12:00:00 by <you>            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "rush02.h"

static int skip_spaces(char *str, int i)
{
    while (str[i] && ft_isspace(str[i]))
        i++;
    return (i);
}

static int is_valid_number(char *str)
{
    int i = 0;

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

static t_dict *add_entry(t_dict *dict, int *size,
        unsigned long long key, char *value)
{
    t_dict *new_dict;
    int i = 0;

    new_dict = (t_dict *)malloc(sizeof(t_dict) * (*size + 1));
    if (!new_dict)
        return (NULL);
    while (i < *size)
    {
        new_dict[i] = dict[i];
        i++;
    }
    new_dict[*size].key = key;
    new_dict[*size].value = value;
    free(dict);
    (*size)++;
    return (new_dict);
}

t_dict *parse_dict(char *file, int *size)
{
    int fd;
    char buffer[1];
    char line[1024];
    int idx = 0;
    t_dict *dict = NULL;
    int r;

    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (NULL);
    while ((r = read(fd, buffer, 1)) > 0)
    {
        if (buffer[0] == '\n' || idx >= 1023)
        {
            int i = 0;
            char num[40];
            int nidx = 0;
            char *val;
            unsigned long long key;
            int j;

            line[idx] = '\0';
            idx = 0;
            /* extra blank line */
            if (!line[0])
                continue ;
            while (line[i] && ft_isspace(line[i]))
                i++;
            while (line[i] && line[i] != ':' && !ft_isspace(line[i]))
                num[nidx++] = line[i++];
            num[nidx] = '\0';
            i = skip_spaces(line, i);
            if (line[i] == ':')
                i++;
            i = skip_spaces(line, i);
            val = ft_strdup_trim(line + i);
            if (num[0] && val && is_valid_number(num))
            {
                key = 0;
                j = 0;
                while (num[j])
                    key = key * 10 + (num[j++] - '0');
                dict = add_entry(dict, size, key, val);
                if (!dict)
                    return (NULL);
            }
            else
                free(val);
        }
        else
            line[idx++] = buffer[0];
    }
    close(fd);
    return (dict);
}

char *dict_lookup(t_dict *dict, int size, unsigned long long key)
{
    int i = 0;

    while (i < size)
    {
        if (dict[i].key == key)
            return (dict[i].value);
        i++;
    }
    return (NULL);
}

-- number.c -------------------------------------------------------------------
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <you>                                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 12:00:00 by <you>             #+#    #+#             */
/*   Updated: 2025/06/29 12:00:00 by <you>            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "rush02.h"

static void print_with_space(char *str, int *first)
{
    if (!str)
        return ;
    if (!*first)
        write(1, " ", 1);
    ft_putstr(str);
    *first = 0;
}

static void handle_upto_hundred(unsigned long long nb,
        t_dict *d, int s, int *first)
{
    unsigned long long tens;

    if (nb == 0)
        return ;
    if (nb <= 20 || (nb < 100 && nb % 10 == 0))
        print_with_space(dict_lookup(d, s, nb), first);
    else if (nb < 100)
    {
        tens = (nb / 10) * 10;
        print_with_space(dict_lookup(d, s, tens), first);
        print_with_space(dict_lookup(d, s, nb % 10), first);
    }
}

static void print_recursive(unsigned long long nb,
        t_dict *d, int s, int *first)
{
    if (nb >= 1000000000ULL)
    {
        print_recursive(nb / 1000000000ULL, d, s, first);
        print_with_space(dict_lookup(d, s, 1000000000ULL), first);
        nb %= 1000000000ULL;
    }
    if (nb >= 1000000ULL)
    {
        print_recursive(nb / 1000000ULL, d, s, first);
        print_with_space(dict_lookup(d, s, 1000000ULL), first);
        nb %= 1000000ULL;
    }
    if (nb >= 1000ULL)
    {
        print_recursive(nb / 1000ULL, d, s, first);
        print_with_space(dict_lookup(d, s, 1000ULL), first);
        nb %= 1000ULL;
    }
    if (nb >= 100ULL)
    {
        print_with_space(dict_lookup(d, s, nb / 100ULL), first);
        print_with_space(dict_lookup(d, s, 100ULL), first);
        nb %= 100ULL;
    }
    handle_upto_hundred(nb, d, s, first);
}

void print_number(unsigned long long nb, t_dict *dict, int size, int first)
{
    if (nb == 0)
    {
        ft_putstr(dict_lookup(dict, size, 0));
        return ;
    }
    print_recursive(nb, dict, size, &first);
}

-- main.c ---------------------------------------------------------------------
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <you>                                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 12:00:00 by <you>             #+#    #+#             */
/*   Updated: 2025/06/29 12:00:00 by <you>            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "rush02.h"

static int is_valid_numeric(char *str)
{
    int i = 0;

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
    unsigned long long res = 0;
    int i = 0;

    while (ft_isspace(str[i]))
        i++;
    while (ft_isdigit(str[i]))
    {
        res = res * 10 + (str[i] - '0');
        i++;
    }
    return (res);
}

int main(int argc, char **argv)
{
    char *dict_file = "numbers.dict";
    char *num_str;
    int dict_size = 0;
    t_dict *dict;
    int i = 0;

    if (argc == 2)
        num_str = argv[1];
    else if (argc == 3)
    {
        dict_file = argv[1];
        num_str = argv[2];
    }
    else
    {
        write(1, "Error\n", 6);
        return (0);
    }
    if (!is_valid_numeric(num_str))
    {
        write(1, "Error\n", 6);
        return (0);
    }
    dict = parse_dict(dict_file, &dict_size);
    if (!dict)
    {
        write(1, "Dict Error\n", 11);
        return (0);
    }
    print_number(ft_atoi_u64(num_str), dict, dict_size, 1);
    write(1, "\n", 1);
    while (i < dict_size)
        free(dict[i++].value);
    free(dict);
    return (0);
}
