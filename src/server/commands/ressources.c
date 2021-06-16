/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** ressources
*/

#include "server/server.h"

char **ressources_container(void)
{
    static char **ptr = NULL;

    if (ptr == NULL) {
        ptr = my_malloc(sizeof(char *) * (THYSTAME + 2));
        ptr[0] = my_strdup("food");
        ptr[1] = my_strdup("linemate");
        ptr[2] = my_strdup("deraumere");
        ptr[3] = my_strdup("sibur");
        ptr[4] = my_strdup("mendiane");
        ptr[5] = my_strdup("phiras");
        ptr[6] = my_strdup("thystame");
        ptr[7] = NULL;
    }
    return ptr;
}