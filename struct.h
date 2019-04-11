/*
** EPITECH PROJECT, 2018
** struct.h
** File description:
** my structs
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/Window.h>
#include <SFML/System/Vector2.h>
#include <SFML/System/Export.h>
#include <SFML/System/Time.h>
#include <SFML/System/Types.h>

#ifndef STRUCT_H_
#define STRUCT_H_

typedef struct game_obj_s
{
    sfTexture *texture;
    sfSprite *sprite;
    sfVector2f pos;
    sfIntRect rect;
    float speed;
    int id;
    struct game_obj_s *next;
} game_obj_t;

typedef struct game_player_s
{
    game_obj_t *player;
    sfClock *clock;
    sfTime time;
    sfMusic *music;
    float seconds;
    int compt;
    int y;
    int jump;
} game_player_t;

typedef struct game_compt_s
{
    sfClock *clock;
    sfTime time;
    float seconds;
    int compt1;
    sfText *txt1;
    sfVector2f pos1;
} game_compt_t;

typedef struct obj_window_s
{
    sfRenderWindow *w;
    sfTexture *t;
    sfSprite *s;
    game_compt_t score;
    game_obj_t **parallax;
    sfEvent event;
    sfClock *clock;
    sfClock *clock2;
    sfMusic **walk;
    sfMusic *music;
    sfTime time;
    sfTime time2;
    float seconds;
    int compt;
    int mode;
    int game;
    int r;
    char **av;
} obj_window_t;

#endif /* STRUCT_H_ */
