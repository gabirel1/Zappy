/*
** EPITECH PROJECT, 2021
** sighandler.c
** File description:
** sighandler.c
*/

#include "server/server.h"

int my_handler(int nb, bool change)
{
    static int number = 0;

    if (change == true)
        number = nb;
    return number;
}

void my_sighandler(UNSD int signal)
{
    my_handler(12, true);
}