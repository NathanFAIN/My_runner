/*
** EPITECH PROJECT, 2018
** MUL_my_runner_2018
** File description:
** draw_obj.c
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

void my_draw_window(obj_window_t *window)
{
    sfRenderWindow_display(window->w);
    sfRenderWindow_clear(window->w, sfWhite);
    sfRenderWindow_drawSprite(window->w, window->s, NULL);
    for (int i = 3; i >= 0; i--)
        sfRenderWindow_drawSprite(window->w, window->parallax[i]->sprite, NULL);
    while (sfRenderWindow_pollEvent(window->w, &window->event))
        if (window->event.type == sfEvtClosed)
            sfRenderWindow_close(window->w);
    if (sfKeyboard_isKeyPressed(sfKeyEscape))
        sfRenderWindow_close(window->w);
}

void my_draw_block(obj_window_t *window, game_obj_t *fond)
{
    for (game_obj_t *tmp = fond; tmp->next; tmp = tmp->next) {
        my_move(tmp);
        my_lava(window, tmp);
        if (tmp->pos.x >= -100 && tmp->pos.x <= SIZE_X)
            sfRenderWindow_drawSprite(window->w, tmp->sprite, NULL);
    }
    my_add_score(window);
    move_parallax(window);
    sfRenderWindow_drawText(window->w, window->score.txt1, NULL);
}
