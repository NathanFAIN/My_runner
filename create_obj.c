/*
** EPITECH PROJECT, 2018
** MUL_my_runner_2018
** File description:
** create_obj.c
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

game_obj_t *add_block(game_obj_t *fond, sfVector2f pos)
{
    sfIntRect rect = {0, 0, 100 , 100};
    game_obj_t *new = create_obj("resource/stone.png", pos, rect, 5);
    game_obj_t *tmp;

    new->id = 1;
    new->next = NULL;
    if (!fond)
        return (new);
    for (tmp = fond; tmp->next; tmp = tmp->next);
    tmp->next = new;
    return (fond);
}

game_obj_t *add_lava(game_obj_t *fond, sfVector2f pos)
{
    sfIntRect rect = {0, 0, 100 , 100};
    game_obj_t *new;
    game_obj_t *tmp;

    pos.y += 5;
    new = create_obj("resource/lava.png", pos, rect, 5);
    new->id = 3;
    new->next = NULL;
    if (!fond)
        return (new);
    for (tmp = fond; tmp->next; tmp = tmp->next);
    tmp->next = new;
    return (fond);
}
