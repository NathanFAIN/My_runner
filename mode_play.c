/*
** EPITECH PROJECT, 2018
** MUL_my_runner_2018
** File description:
** menu.c
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/Window.h>
#include <SFML/System/Vector2.h>
#include <SFML/System/Export.h>
#include <SFML/System/Time.h>
#include <SFML/System/Types.h>
#include <time.h>
#include "my.h"
#include "struct.h"

int my_valid_map(char **av)
{
    int fd;
    int rd;
    char map[100000];

    if (av[1] == NULL)
        return (1);
    fd = open(av[1], O_RDONLY);
    if (fd < 0)
        return (1);
    rd = read(fd, map, 100000);
    map[rd] = '\0';
    close(fd);
    for (int i = 0; map[i + 1] && map[i]; i++)
        if (map[i] != '#' && map[i] != ' ' && map[i] != '\n' && map[i] != '%')
            return (1);
    return (2);
}

game_obj_t *my_normal_mode(obj_window_t *window, game_obj_t *block, \
game_player_t *p)
{
    window->score.compt1 = 0;
    while (sfRenderWindow_isOpen(window->w) && window->game) {
        my_draw_window(window);
        my_draw_block(window, block);
        block = my_move_player(window, p, block);
        my_walk(window, p);
        if (sfKeyboard_isKeyPressed(sfKeyEscape))
            sfRenderWindow_close(window->w);
    }
    my_score(window);
    return (block);
}

float set_block(game_obj_t *block)
{
    float n = 0;

    for (game_obj_t *tmp = block; tmp->next; tmp = tmp->next)
        n = (tmp->pos.x > n && tmp->pos.y == SIZE_Y - 100) ? tmp->pos.x : n;
    return (n + 100);
}

void my_move_block(game_obj_t *block)
{
    for (game_obj_t *tmp = block; tmp->next; tmp = tmp->next) {
        if (tmp->pos.x <= -105) {
            tmp->pos.y = ((rand() % 6) + 1 != 1) ? SIZE_Y - 100 : SIZE_Y - 200;
            tmp->pos.x = set_block(block);
        }
    }
}

game_obj_t *my_infini_mode(obj_window_t *window, game_obj_t *block, \
game_player_t *p)
{
    window->score.compt1 = 0;
    while (sfRenderWindow_isOpen(window->w) && window->game) {
        my_draw_window(window);
        my_draw_block(window, block);
        block = my_move_player(window, p, block);
        my_move_block(block);
        my_walk(window, p);
        if (sfKeyboard_isKeyPressed(sfKeyEscape))
            sfRenderWindow_close(window->w);
    }
    my_score(window);
    return (block);
}
