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

game_obj_t **create_parallax(int nb, int size, sfVector2f pos)
{
    game_obj_t **parallax = malloc(sizeof(game_obj_t *) * nb);
    sfIntRect rect = {0, 0, size , size};

    parallax[0] = create_obj("resource/mc.png", pos, rect, 3);
    parallax[2] = create_obj("resource/mc2.png", pos, rect, 2.7);
    pos.x = size - 1;
    parallax[1] = create_obj("resource/mc.png", pos, rect, 3);
    parallax[3] = create_obj("resource/mc2.png", pos, rect, 2.7);
    return (parallax);
}

void move_parallax(obj_window_t *window)
{
    for (int i = 0; i < 4; i++)
        my_move(window->parallax[i]);
    window->time = sfClock_getElapsedTime(window->clock);
    window->seconds = window->time.microseconds / 100000.0;
    if (window->seconds > 1.0)
        sfClock_restart(window->clock);
    if (window->parallax[0]->pos.x <= -4000)
        window->parallax[0]->pos.x = window->parallax[1]->pos.x + 4000;
    if (window->parallax[1]->pos.x <= -4000)
        window->parallax[1]->pos.x = window->parallax[0]->pos.x + 4000;
    if (window->parallax[2]->pos.x <= -4000)
        window->parallax[2]->pos.x = window->parallax[3]->pos.x + 4000;
    if (window->parallax[3]->pos.x <= -4000)
        window->parallax[3]->pos.x = window->parallax[2]->pos.x + 4000;
}
