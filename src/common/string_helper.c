/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** string_helper
*/

#include "def.h"

char *my_strdup(char *cpy)
{
    char *ret = my_malloc(strlen(cpy) + 1);

    memset(ret, 0, strlen(cpy) + 1);
    strcpy(ret, cpy);
    return ret;
}

bool is_delim(char c, char *delim)
{
    for (int i = 0; delim[i]; i += 1)
        if (delim[i] == c)
            return true;
    return false;
}

int get_nb_args(char *str, char *delim)
{
    int count = 0;
    for (int i = 0; str[i]; i += 1) {
        if ((!is_delim(str[i], delim) && i == 0) ||
        (i > 0 && !is_delim(str[i], delim)
        && is_delim(str[i - 1], delim)))
            count += 1;
    }
    return (count);
}

char **str_to_word_array(char *str, char *delim)
{
    char **tab = NULL;
    int nb_of_args = get_nb_args(str, delim);
    char *ptr = strtok(str, delim);
    int index = 0;

    tab = malloc(sizeof(char *) * (nb_of_args + 2));
    if (tab == NULL)
        return NULL;
    while (ptr != NULL) {
        tab[index] = strdup(ptr);
        ptr = strtok(NULL, delim);
        index++;
    }
    tab[index] = NULL;
    return tab;
}