#include "rush02.h"

typedef struct s_ctx
{
    t_dict  *dict;
    int     size;
}   t_ctx;

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
                                t_ctx *ctx, int *first)
{
    unsigned long long tens;

    if (nb == 0)
        return ;
    if (nb <= 20 || (nb < 100 && nb % 10 == 0))
        print_with_space(dict_lookup(ctx->dict, ctx->size, nb), first);
    else if (nb < 100)
    {
        tens = (nb / 10) * 10;
        print_with_space(dict_lookup(ctx->dict, ctx->size, tens), first);
        print_with_space(dict_lookup(ctx->dict, ctx->size, nb % 10), first);
    }
}

static void print_recursive_nb(unsigned long long nb,
                               t_ctx *ctx, int *first);

static unsigned long long print_segment(unsigned long long nb,
                                        unsigned long long mag,
                                        t_ctx *ctx, int *first)
{
    if (nb >= mag)
    {
        print_recursive_nb(nb / mag, ctx, first);
        print_with_space(dict_lookup(ctx->dict, ctx->size, mag), first);
        nb %= mag;
    }
    return (nb);
}

static void print_recursive_nb(unsigned long long nb,
                               t_ctx *ctx, int *first)
{
    nb = print_segment(nb, 1000000000ULL, ctx, first);
    nb = print_segment(nb, 1000000ULL, ctx, first);
    nb = print_segment(nb, 1000ULL, ctx, first);
    if (nb >= 100ULL)
    {
        print_with_space(dict_lookup(ctx->dict, ctx->size, nb / 100ULL), first);
        print_with_space(dict_lookup(ctx->dict, ctx->size, 100ULL), first);
        nb %= 100ULL;
    }
    handle_upto_hundred(nb, ctx, first);
}

void    print_number(unsigned long long nb, t_dict *dict, int size, int first)
{
    t_ctx ctx;

    if (nb == 0)
    {
        ft_putstr(dict_lookup(dict, size, 0));
        return ;
    }
    ctx.dict = dict;
    ctx.size = size;
    print_recursive_nb(nb, &ctx, &first);
}
