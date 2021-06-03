/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** server
*/

#ifndef SERVER_H_
#define SERVER_H_

#include "def.h"
#include "common/garbage_collector.h"

typedef struct game_info_s
{

} game_info_t;

typedef struct server_info_s
{
    int port;
    int max_client;
    int nb_teams;
} server_info_t;

typedef struct server_s
{
    int serverfd;
    fd_set write_fd_set;
    fd_set read_fd_set;
    fd_set active_fd_set;
    struct sockaddr_in server_address;
    struct timeval timeout;
} server_t;

typedef struct client_s
{
    int fd;
    struct client_s *next;
} client_t;

bool add_client(client_t *next);
bool delete_client(client_t *client);

#endif /* !SERVER_H_ */