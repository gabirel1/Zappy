/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** string_utils
*/

#include "def.h"

char *my_strcat(char *s1, char *s2)
{
    char *ret = my_malloc(((s1) ? strlen(s1) : 0) + strlen(s1) + 1);

    memset(ret, 0, ((s1) ? strlen(s1) : 0) + strlen(s1) + 1);
    if (s1)
        strcpy(ret, s1);
    strcpy(ret, s2);
    return ret;
}

char *convert_digit(char *dest, int i)
{
    if (i <= -10)
        dest = convert_digit(dest, i / 10);
    *dest++ = '0' - i % 10;
    return (dest);
}

char *my_itoa(int i)
{
    char *dest = my_malloc(sizeof(char) * 12);
    char *s = dest;

    for (int k = 0; k < 12; k += 1)
        dest[k] = 0;
    if (i < 0)
        *s++ = '-';
    else
        i = -i;
    *convert_digit(s, i) = '\0';
    return (dest);
}