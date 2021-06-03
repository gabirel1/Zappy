/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** setup
*/

#include "server/server.h"

int handle_connection(server_t *server, server_info_t *server_in, \
game_info_t *game, int i)
{
    char rcv[1024] = { 0 };
    client_t *new = NULL;
    size_t len = sizeof(server->server_address);

    if (i == server->serverfd) {
        new = my_malloc(sizeof(client_t));
        new->fd = accept(i, (struct sockaddr *) &server->server_address, \
        (socklen_t *) &len);
        if (new->fd == -1) {
            fprintf(stderr, "Error while accepting new client\n");
            return ERROR;
        }
        printf("new connection\n");
        FD_SET(new->fd, &server->active_fd_set);
        add_client(new);
    } else {
        read(i, rcv, 1024);
        printf("[%s]\n", rcv);
    }
    return SUCCESS;
}

int launch_server(server_t server, server_info_t server_in, game_info_t game)
{
    while (1) {
        server.read_fd_set = server.active_fd_set;
        server.write_fd_set = server.active_fd_set;
        if (select(FD_SETSIZE, &server.read_fd_set, &server.write_fd_set, \
        NULL, &server.timeout) == -1) {
            fprintf(stderr, "Error while waiting for client\n");
            return ERROR;
        }
        for (int i = 0; i < FD_SETSIZE; i += 1) {
            if (FD_ISSET(i, &server.read_fd_set))
                handle_connection(&server, &server_in, &game, i);
        }
    }
}

int setup_server(server_t server, server_info_t server_info, game_info_t game)
{
    if (bind(server.serverfd, (struct sockaddr *) &server.server_address, \
    sizeof(server.server_address)) == -1) {
        fprintf(stderr, "Error while binding socket\n");
        return ERROR;
    }
    if (listen(server.serverfd, server_info.max_client * \
    server_info.nb_teams + 1) == -1) {
        fprintf(stderr, "Error while listening on server");
        return ERROR;
    }
    FD_ZERO(&server.active_fd_set);
    FD_SET(server.serverfd, &server.active_fd_set);
    server.timeout.tv_sec = 1;
    server.timeout.tv_usec = 0;
    return (launch_server(server, server_info, game));
}

int create_server(server_info_t server_info, game_info_t game)
{
    server_t server = { 0 };
    int opt = 1;

    server.serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if (server.serverfd == -1) {
        fprintf(stderr, "ERROR While creating socket\n");
        return ERROR;
    }
    if (setsockopt(server.serverfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, \
    &opt, sizeof(opt)) == -1) {
        fprintf(stderr, "Error while setting up socket\n");
        return ERROR;
    }
    server.server_address.sin_family = AF_INET;
    server.server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.server_address.sin_port = htons(server_info.port);
    return (setup_server(server, server_info, game));
}