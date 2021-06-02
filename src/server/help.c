/*
** EPITECH PROJECT, 2021
** help.c
** File description:
** help.c
*/

#include "def.h"

int help_func(int error_code)
{
    char usage1[49] = "USAGE: ./zappy_server -p port -x width -y height";
    char usage2[41] = " -n name1 name2 ... -c clientsNb -f freq";
    char port[26] = "port\t  is the port number";
    char width[34] = "width\t  is the width of the world";
    char height[36] = "height\t  is the height of the world";
    char name_x[34] = "nameX\t  is the name of the team X";
    char cli_nb[55] = "clientsNb is the number of authorized clients per team";
    char freq1[34] = "freq\t  is the reciprocal of time ";
    char freq2[30] = "unit for execution of actions";

    printf("%s%s\n", usage1, usage2);
    printf("\t%s\n", port);
    printf("\t%s\n", width);
    printf("\t%s\n", height);
    printf("\t%s\n", name_x);
    printf("\t%s\n", cli_nb);
    printf("\t%s%s\n", freq1, freq2);

    return error_code;
}