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

/* utils */
int     ft_strlen(char *str);
int     ft_isspace(char c);
int     ft_isdigit(char c);
int     ft_strcmp(char *s1, char *s2);
void    ft_putstr(char *str);

/* string utils */
char    *ft_strdup_trim(char *src);
char    *ft_strjoin_free(char *s1, char *s2);

/* dict & lookup */
t_dict  *parse_dict(char *file, int *size);
char    *dict_lookup(t_dict *dict, int size, unsigned long long key);

/* number */
void    print_number(unsigned long long nb, t_dict *dict, int size, int first);

#endif