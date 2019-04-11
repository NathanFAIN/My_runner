/*
** EPITECH PROJECT, 2018
** my.h
** File description:
** lib
*/
#define SIZE_X  1360
#define SIZE_Y  768

#include "struct.h"

#ifndef MY_H_
#define MY_H_

char *give_score(void);
void my_score(obj_window_t *window);
void my_add_score(obj_window_t *win);
int my_valid_map(char **av);
game_obj_t *my_normal_mode(obj_window_t *window, game_obj_t *block, \
game_player_t *p);
game_obj_t *my_infini_mode(obj_window_t *window, game_obj_t *block, \
game_player_t *p);
game_obj_t *my_menu(obj_window_t *window, char **av, int ac, game_player_t \
*player);
void my_draw_menu(obj_window_t *window);
void my_walk(obj_window_t *window, game_player_t *player);
obj_window_t *create_score(obj_window_t *win);
game_obj_t *my_lose(obj_window_t *window, game_player_t *player);
game_obj_t *my_move_player(obj_window_t *window, game_player_t *player, \
game_obj_t *b);
game_player_t *create_player(void);
char *my_open(char *av);
char **my_map(char *map);
void my_lava(obj_window_t *window, game_obj_t *obj);
game_obj_t *add_block(game_obj_t *fond, sfVector2f pos);
game_obj_t *add_lava(game_obj_t *fond, sfVector2f pos);
obj_window_t *create_fond(void);
void my_draw_window(obj_window_t *window);
game_obj_t *create_obj(const char *fd, sfVector2f pos, sfIntRect rect, float s);
game_obj_t *create_all_block(char *fd);
void my_draw_block(obj_window_t *window, game_obj_t *fond);
void my_move(game_obj_t *obj);
void destroy_all_block(game_obj_t *fond, game_player_t *player, \
obj_window_t *window);
void destroy_window(obj_window_t *window);
game_obj_t *my_win(obj_window_t *window, game_player_t *player, game_obj_t *b);
game_obj_t **create_parallax(int nb, int size, sfVector2f pos);
void move_parallax(obj_window_t *window);

#endif /* MY_H_ */
