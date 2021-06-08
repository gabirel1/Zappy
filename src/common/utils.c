/*
** EPITECH PROJECT, 2021
** utils.c
** File description:
** utils.c
*/

#include "def.h"

int get_tab_len(char *tab[])
{
    int len = 0;

    for (; tab[len]; len++);

    return len;
}

bool is_full_digits(char *string)
{
    for (int index = 0; string[index]; index++) {
        if (string[index] < '0' || string[index] > '9')
            return false;
    }
    return true;
}

void free_tab(char *tab[])
{
    if (tab != NULL) {
        for (int index = 0; tab[index]; index++) {
            free(tab[index]);
        }
        free(tab);
    }
}