/*
** EPITECH PROJECT, 2021
** server_container.c
** File description:
** server_container.c
*/

#include "server/server.h"

server_t **server_container(void)
{
    static server_t *server = NULL;

    return &server;
}