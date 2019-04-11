/*
** EPITECH PROJECT, 2018
** MUL_my_runner_2018
** File description:
** my_destroy.c
*/

#include <time.h>
#include <stdio.h>
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

void destroy_window(obj_window_t *window)
{
    sfTexture_destroy(window->t);
    sfSprite_destroy(window->s);
    sfRenderWindow_destroy(window->w);
}

void destroy_all_block(game_obj_t *fond, game_player_t *player, \
obj_window_t *window)
{
    for (game_obj_t *tmp = fond; tmp->next; tmp = tmp->next) {
        sfTexture_destroy(tmp->texture);
        sfSprite_destroy(tmp->sprite);
        free(tmp);
    }
    sfMusic_destroy(window->music);
    sfMusic_destroy(player->music);
    for (int i = 0; i < 4; i++)
        sfMusic_destroy(window->walk[i]);
    destroy_window(window);
}
