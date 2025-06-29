#include "rush02.h"

char    *dict_lookup(t_dict *dict, int size, unsigned long long key)
{
    int i;

    i = 0;
    while (i < size)
    {
        if (dict[i].key == key)
            return (dict[i].value);
        i++;
    }
    return (NULL);
}
