/*
** EPITECH PROJECT, 2018
** MUL_my_runner_2018
** File description:
** menu.c
*/

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

int my_check_botton2(obj_window_t *window)
{
    int test = 1;
    int x = sfMouse_getPositionRenderWindow(window->w).x;
    int y = sfMouse_getPositionRenderWindow(window->w).y;

    while (x > 441 && x < 841 && y > 484 && y < 684 && \
    sfMouse_isButtonPressed(sfMouseLeft))
        test = 0;
    if (!test)
        sfMusic_play(window->music);
    return (test);
}

void my_draw_menu(obj_window_t *window)
{
    sfRenderWindow_display(window->w);
    while (sfRenderWindow_pollEvent(window->w, &window->event))
        if (window->event.type == sfEvtClosed)
            sfRenderWindow_close(window->w);
    if (sfKeyboard_isKeyPressed(sfKeyEscape))
        sfRenderWindow_close(window->w);
}

game_obj_t *my_lose(obj_window_t *window, game_player_t *player)
{
    sfVector2f pos = {200, -50};
    sfIntRect rect = {0, 0, SIZE_X , SIZE_Y};
    game_obj_t *lose = create_obj("resource/lose.png", pos, rect, 5);
    int test = 1;

    sfMusic_play(player->music);
    while (sfRenderWindow_isOpen(window->w) && test) {
        sfRenderWindow_drawSprite(window->w, player->player->sprite, NULL);
        sfRenderWindow_drawSprite(window->w, lose->sprite, NULL);
        my_draw_menu(window);
        test = my_check_botton2(window);
    }
    return (my_menu(window, window->av, my_valid_map(window->av), player));
}

game_obj_t *my_win(obj_window_t *window, game_player_t *player, game_obj_t *b)
{
    sfIntRect rect = {0, 0, SIZE_X , SIZE_Y};
    game_obj_t *lose;
    int test = 1;

    for (game_obj_t *tmp = b; tmp->next && test; tmp = tmp->next)
        test = (tmp->pos.x > player->player->pos.x + SIZE_X - 100) ? 0 : test;
    if (!test)
        return (b);
    lose = create_obj("resource/win.png", (sfVector2f) {200, -50}, rect, 5);
    while (sfRenderWindow_isOpen(window->w) && test) {
        sfRenderWindow_drawSprite(window->w, player->player->sprite, NULL);
        sfRenderWindow_drawSprite(window->w, lose->sprite, NULL);
        my_draw_menu(window);
        test = my_check_botton2(window);
    }
    sfTexture_destroy(lose->texture);
    sfSprite_destroy(lose->sprite);
    free(lose);
    return (my_menu(window, window->av, my_valid_map(window->av), player));
}
