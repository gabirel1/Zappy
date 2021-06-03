/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** client
*/

#include "server/server.h"

client_t **client_container(void)
{
    static client_t *head = NULL;

    return &head;
}

bool add_client(client_t *next)
{
    client_t **front_ptr = client_container();
    client_t *tmp = *front_ptr;

    if (!next)
        return (false);
    next->next = NULL;
    if (front_ptr == NULL || *front_ptr == NULL) {
        *front_ptr = next;
        return (true);
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = next;
    return (true);
}

bool delete_client(client_t *client)
{
    client_t **front_ptr = client_container();
    client_t *tmp = *front_ptr;
    client_t *second_tmp = *front_ptr;

    if (!*front_ptr)
        return (false);
    if (client == tmp) {
        *front_ptr = tmp->next;
        return (true);
    }
    while (client != tmp->next)
        tmp = tmp->next;
    second_tmp = tmp->next->next;
    tmp->next = second_tmp;
    return (true);
}

client_t *get_client_by_socket(int fd)
{
    for (client_t *tmp = *client_container(); tmp; tmp = tmp->next)
        if (tmp->fd == fd)
            return tmp;
    return NULL;
}