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

typedef struct team_s
{
    char team_uuid[37];
    char *team_name;
    int client_max;
    struct team_s *next;
} team_t;

typedef struct game_info_s
{
    team_t *teams;
    int width;
    int height;
    int freq;
} game_info_t;

typedef enum item
{
    FOOD = 0,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
} item_t;

typedef struct tile_s
{
    int resources[THYSTAME + 1];
    int posx;
    int posy;
} tile_t;

typedef struct game_board_s
{
    team_t *teams;
    int width;
    int height;
    int freq;
    tile_t **map;
} game_board_t;

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
    bool is_graphic;
    bool is_ia;
    char uuid[37];
    struct client_s *next;
} client_t;

typedef enum orientation
{
    NORTH = 1,
    EAST,
    SOUTH,
    WEST
} orientation_t;

typedef struct player_s
{
    int inventory[THYSTAME + 1];
    orientation_t orientation;
    int posx;
    int posy;
    int level;
    int player_number;
    char uuid[37];
    char team_uuid[37];
    int cooldown;
    int hp;
    bool is_egg;
    struct timeval clock;
    struct timeval life_clock;
    void (*on_cd)(struct player_s *);
    struct player_s *next;
} player_t;


typedef struct func_s
{
    char *cmd;
    int (*fun)(char **, server_t *, game_board_t *, client_t *);
} func_t;

#define TILE_CONTENT g_board->map[y_index][x_index]
#define TILE_CONTENT_R g_board->map[y_index][x_index].resources

server_t **server_container(void);
char *my_strdup(char *cpy);
int get_tab_len(char *tab[]);
bool is_full_digits(char *string);
void free_tab(char *tab[]);
char *my_itoa(int i);
char *my_strcat(char *s1, char *s2);

tile_t *get_tile_by_pos(tile_t **tiles, int pos_x, int pos_y, \
game_board_t *game_board);
game_board_t *create_game_board(game_info_t *game_info);

client_t **client_container(void);
bool add_client(client_t *next);
bool delete_client(client_t *client);
client_t *get_client_by_socket(int fd);
void init_new_client(client_t *client);

player_t **player_container(void);
player_t *get_player_by_uuid(char *uuid);
bool add_player(player_t *next);
bool delete_player(player_t *player);
player_t *init_player(char *team_uuid, int posx, int posy);
player_t *get_player_by_number(int player_id);

team_t **team_container(void);
team_t *get_team_by_uuid(char *uuid);
team_t *init_team(char team_uuid[37], char *team_name, int max_client);
bool add_team(team_t *next);
bool delete_team(team_t *team);
team_t *get_team_by_name(char *name);
char *get_team_name_by_uuid(char uuid[37]);

char *read_from_fd(int fd, fd_set *fd_set);
int interpret_cmd(char *buff, server_t *server, game_board_t *game, \
client_t *client);

int setup_infos(int ac, char *av[], server_info_t *server_info, \
game_info_t *game_info);
void setup_default(server_info_t *s_info, game_info_t *g_info);
int f_case(game_info_t *game_info);
int c_case(server_info_t *server_info);
int y_case(game_info_t *g_info);
int x_case(game_info_t *g_info);

int create_server(server_info_t *server_info, game_info_t *sgame);
int server_loop(server_t *server, int res, server_info_t *server_in, \
game_board_t *game);
void stop_client(int fd, server_t *server, int *res);
void delete_client_from_list(client_t *client);
int handle_connection(server_t *server, UNSD server_info_t *server_in, \
game_board_t *game, int i);

int graphic_send_first_batch(game_board_t *g_board, \
client_t *client, server_t *server);
int ia_send_first_batch(game_board_t *g_board, \
client_t *client, server_t *server);

void my_sighandler(UNSD int signal);
int my_handler(int nb, bool change);

int game_loop(struct timeval *start, game_board_t *game);
void update_cooldown(game_board_t *board, server_t *server);

int seg(char *team_name, int fd, server_t *server);
int smg(char *message, int fd, server_t *server);
int pfk(int fd, int player_number, server_t *server);
int pdr(int fd, int player_number, int resource_number, \
server_t *server);
int pgt(int fd, int player_number, int resource_number, \
server_t *server);
int pdi(int fd, int player_number, server_t *server);
int pex(int fd, int player_number, server_t *server);
int pbc(int fd, int player_number, char *message, server_t *server);
int enw(int fd, int egg_number, int player_number, server_t *server); //
int eht(int fd, int egg_number, server_t *server); //
int ebo(int fd, int egg_number, server_t *server); //
int edi(int fd, int egg_number, server_t *server); //
int pic(int fd, int first_player, int *player_numbers, server_t *server); //
int pie(int fd, int pos[2], int result, server_t *server); //
int sbp(int fd, server_t *server); //
int suc(int fd, server_t *server);

int msz(char *request[], server_t *server, game_board_t *g_board, \
client_t *client);
int bct(char *request[], server_t *server, game_board_t *g_board, \
client_t *client);
int mct(char *request[], server_t *server, game_board_t *g_board, \
client_t *client);
int tna(char *request[], server_t *server, game_board_t *g_board, \
client_t *client);
int ppo(char *request[], server_t *server, game_board_t *g_board, \
client_t *client);
int plv(char *request[], server_t *server, game_board_t *g_board, \
client_t *client);
int pin(char *request[], server_t *server, game_board_t *g_board, \
client_t *client);
int sgt(char *request[], server_t *server, game_board_t *g_board, \
client_t *client);
int sst(char *request[], server_t *server, game_board_t *g_board, \
client_t *client);

char **ressources_container(void);
int get_resources_number_by_name(char *name);
int forward(game_board_t *game, player_t *player);
int left(game_board_t *game, player_t *player);
int right(game_board_t *game UNSD, player_t *player);
char *look(game_board_t *game, player_t *player);
char *look_tiles(tile_t *tiles, int length, char *ret, char **ressources);
char *inventory(game_board_t *game UNSD, player_t *player);
int eject(game_board_t *game, player_t *player);
int fork_player(game_board_t *game, player_t *player);
int take(game_board_t *game, player_t *player, char *object);
int set(game_board_t *game, player_t *player, char *object);
int incantation(game_board_t *game UNSD, player_t *player);
int broadcast_text(char *request[], server_t *server, game_board_t *g_board, \
client_t *client);

int move_forward(char *request[], server_t *server, game_board_t *g_board, \
client_t *client);
int move_left(char *request[], server_t *server, game_board_t *g_board, \
client_t *client);
int move_right(char *request[], server_t *server, game_board_t *g_board, \
client_t *client);
int f_look(char *request[], server_t *server, game_board_t *g_board, \
client_t *client);
int f_inventory(char *request[], server_t *server, game_board_t *g_board, \
client_t *client);
int f_eject(char *request[], server_t *server, game_board_t *g_board, \
client_t *client);
int f_fork(char *request[], server_t *server, game_board_t *g_board, \
client_t *client);
int f_take(char *request[], server_t *server, game_board_t *g_board, \
client_t *client);
int f_set(char *request[], server_t *server, game_board_t *g_board, \
client_t *client);
int f_connect_nbr(char *request[], server_t *server, game_board_t *g_board, \
client_t *client);
int f_broadcast_text(char *request[], server_t *server, game_board_t *g_board, \
client_t *client);

static const func_t func_tab[] = {
    {"msz", &msz},
    {"bct", &bct},
    {"mct", &mct},
    {"tna", &tna},
    {"ppo", &ppo},
    {"plv", &plv},
    {"pin", &pin},
    {"sgt", &sgt},
    {"sst", &sst},
    {"Forward", &move_forward},
    {"Right", &move_right},
    {"Left", &move_left},
    {"Look", &f_look},
    {"Inventory", &f_inventory},
    {"Broadcast", &f_broadcast_text},
    {"Connect_nbr", &f_connect_nbr},
    {"Fork", &f_fork},
    {"Eject", &f_eject},
    {"Take", &f_take},
    {"Set", &f_set},
    // {"Incantation", &incantation},
    {NULL, NULL}
};

#endif /* !SERVER_H_ */