/*
** EPITECH PROJECT, 2018
** MUL_my_runner_2018
** File description:
** menu.c
*/

#include <time.h>
#include <stdlib.h>
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/Window.h>
#include <SFML/System/Vector2.h>
#include <SFML/System/Export.h>
#include <SFML/System/Time.h>
#include <SFML/System/Types.h>
#include "struct.h"
#include "my.h"
#include <stdio.h>

void my_walk(obj_window_t *window, game_player_t *player)
{
    window->time2 = sfClock_getElapsedTime(window->clock2);
    if (window->time2.microseconds / 100000.0 > 2.0) {
        sfClock_restart(window->clock2);
        if (player->jump)
            sfMusic_play(window->walk[(rand() % 3)]);
    }
}

game_obj_t *create_all_block2(void)
{
    sfVector2f pos = {700, SIZE_Y - 100};
    sfIntRect rect = {0, 0, 100 , 100};
    game_obj_t *fond = create_obj("resource/stone.png", pos, rect, 5);
    int r = 0;

    srand(time(NULL));
    fond->next = NULL;
    for (int i = 0; i <= 6 * 100; i = i + 100)
        fond = add_block(fond, (sfVector2f) {i, SIZE_Y - 100});
    for (;pos.x < 50 * 100; pos.x = pos.x + 100) {
        r = (rand() % (7 + r)) + 1;
        pos.y -= (pos.y != SIZE_Y - 200 && (rand() % 4) + 1 != 1) ? 100 : 0;
        pos.y += (pos.y != SIZE_Y - 100 && (rand() % 4) + 1 != 1) ? 100 : 0;
        fond = (r != 1) ? add_block(fond, pos) : add_lava(fond, pos);
        fond = (pos.y != SIZE_Y - 100) ? add_block(fond, (sfVector2f) {pos.x , \
        SIZE_Y - 100}) : fond;
        r = (r != 1) ? 0 : r;
    }
    return (fond);
}

int my_check_botton(obj_window_t *window, int ac, game_obj_t *no_map)
{
    int test = 0;
    int x = sfMouse_getPositionRenderWindow(window->w).x;
    int y = sfMouse_getPositionRenderWindow(window->w).y;

    while (x > 480 && x < 880 && y > 47 && y < 247 && \
    sfMouse_isButtonPressed(sfMouseLeft))
        test = 1;
    while (x > 480 && x < 880 && y > 283 && y < 483 && \
    sfMouse_isButtonPressed(sfMouseLeft))
        test = 2;
    while (x > 480 && x < 880 && y > 519 && y < 719 && \
    sfMouse_isButtonPressed(sfMouseLeft) && ac == 2)
        test = 3;
    if (test) {
        sfMusic_play(window->music);
        sfTexture_destroy(no_map->texture);
        sfSprite_destroy(no_map->sprite);
        free(no_map);
    }
    return (test);
}

game_obj_t *my_select_map(int test, char **av, obj_window_t *window, \
game_obj_t *menu)
{
    window->game = 0;
    window->mode = 1;
    sfTexture_destroy(menu->texture);
    sfSprite_destroy(menu->sprite);
    free(menu);
    if (test == 1)
        return (create_all_block2());
    window->mode = 2;
    if (test == 2)
        return (create_all_block("resource/map"));
    window->mode = 3;
    if (test == 3 && my_valid_map(window->av) >= 2)
        return (create_all_block(av[1]));
    window->mode = 84;
    return (create_all_block(NULL));
}

game_obj_t *my_menu(obj_window_t *window, char **av, int ac, game_player_t \
*player)
{
    sfVector2f pos = {0, 0};
    sfIntRect rect = {0, 0, SIZE_X , SIZE_Y};
    game_obj_t *menu = create_obj("resource/menu.png", pos, rect, 5);
    game_obj_t *no_map = create_obj("resource/no map.png", pos, rect, 5);
    int test = 0;

    my_score(window);
    sfText_setString(window->score.txt1, give_score());
    for (int i = 3; i >= 0; i--)
        sfRenderWindow_drawSprite(window->w, window->parallax[i]->sprite, NULL);
    sfRenderWindow_drawSprite(window->w, menu->sprite, NULL);
    sfRenderWindow_drawText(window->w, window->score.txt1, NULL);
    if (ac < 2)
        sfRenderWindow_drawSprite(window->w, no_map->sprite, NULL);
    while (sfRenderWindow_isOpen(window->w) && !test) {
        my_draw_menu(window);
        test = my_check_botton(window, ac, no_map);
    }
    player->player->pos.y = SIZE_Y - 334 - 400;
    return (my_select_map(test, av, window, menu));
}
