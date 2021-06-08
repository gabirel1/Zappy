/*
** EPITECH PROJECT, 2021
** setup_cases.c
** File description:
** setup_cases.c
*/

#include "server/server.h"

int x_case(game_info_t *g_info)
{
    printf("opt x == %s\n", optarg);
    if (is_full_digits(optarg) == false ||
    (atoi(optarg) < 10 || atoi(optarg) > 30)) {
        printf("-x option only accepts integer values between 10 and 30\n");
        return ERROR;
    }
    g_info->width = atoi(optarg);
    return SUCCESS;
}

int y_case(game_info_t *g_info)
{
    printf("opt y == %s\n", optarg);
    if (is_full_digits(optarg) == false ||
    (atoi(optarg) < 10 || atoi(optarg) > 30)) {
        printf("-y option only accepts integer values between 10 and 30\n");
        return ERROR;
    }
    g_info->height = atoi(optarg);
    return SUCCESS;
}

int c_case(server_info_t *server_info)
{
    printf("opt c == %s\n", optarg);
    if (is_full_digits(optarg) == false || atoi(optarg) < 1) {
        printf("-c option only accepts integer values greater or equal to 1\n");
        return ERROR;
    }
    server_info->max_client = atoi(optarg);
    return SUCCESS;
}

int f_case(game_info_t *game_info)
{
    printf("opt f == %s\n", optarg);
    if (is_full_digits(optarg) == false
    || atoi(optarg) < 2 || atoi(optarg) > 10000) {
        printf("-f option only accepts integer values between 2 and 10000\n");
        return ERROR;
    }
    game_info->freq = atoi(optarg);
    return SUCCESS;
}