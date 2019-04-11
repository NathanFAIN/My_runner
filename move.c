/*
** EPITECH PROJECT, 2018
** MUL_my_runner_2018
** File description:
** move.c
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

void my_move(game_obj_t *obj)
{
    if (obj->rect.width == 100)
        obj->pos.x -= (obj->pos.x >= -106) ? obj->speed : 0;
    else
        obj->pos.x -= obj->speed;
    sfSprite_setPosition(obj->sprite, obj->pos);
}

void my_lava(obj_window_t *window, game_obj_t *obj)
{
    if (obj->id != 3)
        return;
    if (window->seconds > 1.0 && obj->pos.x >= -100 && obj->pos.x <= SIZE_X) {
        obj->rect.top = (obj->rect.top == 1500) ? 0 : obj->rect.top + 100;
        sfSprite_setTextureRect(obj->sprite, obj->rect);
    }
}

game_obj_t *my_jump_player(obj_window_t *win, game_player_t *player, \
game_obj_t *tmp, game_obj_t *b)
{
    if (sfKeyboard_isKeyPressed(sfKeySpace) && player->jump) {
        player->y = -18;
        player->jump = 0;
    }
    player->player->pos.y = (tmp->next && tmp->pos.y - 200 > \
    player->player->pos.y && tmp->next && tmp->pos.y - 270 < \
    player->player->pos.y) ? tmp->pos.y - 235 : player->player->pos.y;
    player->jump = (!player->y) ? 1 : player->jump;
    win->r = (player->player->pos.y > SIZE_Y) ? 1 : win->r;
    if (win->r)
        b = my_lose(win, player);
    player->player->rect.left = (player->player->rect.left < 6900) \
    ? player->player->rect.left + 300 : 0;
    player->player->pos.y += player->y;
    player->y += (player->y != 0 && player->y < 20) ? 1 : 0;
    player->y = (player->y != 0) ? player->y : 1;
    sfSprite_setTextureRect(player->player->sprite, player->player->rect);
    sfSprite_setPosition(player->player->sprite, player->player->pos);
    return (b);
}

game_obj_t *my_move_player(obj_window_t *win, game_player_t *player, \
game_obj_t *b)
{
    game_obj_t *tmp = b;

    win->r = 0;
    player->time = sfClock_getElapsedTime(player->clock);
    player->seconds = player->time.microseconds / 10000.0;
    if (player->seconds > 1.0) {
        for (; tmp->next && player->y; tmp = tmp->next) {
            player->y = (tmp->pos.y - 200 > player->player->pos.y && \
            tmp->pos.y - 245 - player->y < player->player->pos.y && \
            player->player->pos.x + 155 > tmp->pos.x && player->player->pos.x \
            < tmp->pos.x - 15 && tmp->id != 3 && player->y > 0) ? 0 : player->y;
            win->r = (tmp->pos.y > player->player->pos.y && tmp->pos.y - 220 < \
            player->player->pos.y && player->player->pos.x + 155 > tmp->pos.x \
            && player->player->pos.x < tmp->pos.x - 15) ? 1 : win->r;
        }
        sfClock_restart(player->clock);
        b = my_jump_player(win, player, tmp, b);
    }
    sfRenderWindow_drawSprite(win->w, player->player->sprite, NULL);
    return (my_win(win, player, b));
}
