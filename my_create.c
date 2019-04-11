/*
** EPITECH PROJECT, 2018
** MUL_my_runner_2018
** File description:
** my_create.c
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

sfRenderWindow *create_window(void)
{
    sfRenderWindow *window;
    sfVideoMode video_mode;

    video_mode.width = SIZE_X;
    video_mode.height = SIZE_Y;
    video_mode.bitsPerPixel = 32;
    window = sfRenderWindow_create(video_mode, "Mine Runner", sfClose, NULL);
    sfRenderWindow_setIcon(window, 100, 100, \
    sfImage_getPixelsPtr(sfImage_createFromFile("resource/block.jpg")));
    sfRenderWindow_setFramerateLimit(window, 100);
    return (window);
}

game_obj_t *create_obj(const char *fd, sfVector2f pos, sfIntRect rect, float s)
{
    game_obj_t *obj = malloc(sizeof(game_obj_t));

    obj->pos = pos;
    obj->rect = rect;
    obj->speed = s;
    obj->texture = sfTexture_createFromFile(fd, NULL);
    obj->sprite = sfSprite_create();
    sfSprite_setTexture(obj->sprite, obj->texture, sfTrue);
    sfSprite_setTextureRect(obj->sprite, obj->rect);
    sfSprite_setPosition(obj->sprite, obj->pos);
    return (obj);
}

obj_window_t *create_fond(void)
{
    obj_window_t *win = malloc(sizeof(obj_window_t));
    win->walk = malloc(sizeof(sfMusic *) * 4);

    win->parallax = create_parallax(4, 4000, (sfVector2f) {0, -250});
    win->w = create_window();
    win->t = sfTexture_createFromFile("resource/fond.jpg", NULL);
    win->s = sfSprite_create();
    sfSprite_setTexture(win->s, win->t, sfTrue);
    win->clock = sfClock_create();
    win->clock2 = sfClock_create();
    win->walk[0] = sfMusic_createFromFile("resource/stone2.ogg");
    win->walk[1] = sfMusic_createFromFile("resource/stone3.ogg");
    win->walk[2] = sfMusic_createFromFile("resource/stone4.ogg");
    win->walk[3] = sfMusic_createFromFile("resource/stone5.ogg");
    win->music = sfMusic_createFromFile("resource/click.ogg");
    win->seconds = 0;
    win->compt = 0;
    return (win);
}

game_obj_t *create_all_block(char *fd)
{
    sfVector2f pos = {-100, SIZE_Y - 100};
    sfIntRect rect = {0, 0, 100 , 100};
    game_obj_t *fond = create_obj("resource/block.jpg", pos, rect, 5);
    char *map = my_open(fd);

    fond->next = NULL;
    for (int i = 0; map[i]; i++)
        pos.y -= (map[i] == '\n') ? 100 : 0;
    for (int x = 0; map[x]; x++) {
        pos.y += 100;
        for (int i = 0; map[x] != '\n' && map[x]; x++, i++) {
            pos.x = 100 * i;
            fond = (map[x] == '#') ? add_block(fond, pos) : fond;
            fond = (map[x] == '%') ? add_lava(fond, pos) : fond;
        }
    }
    return (fond);
}

game_player_t *create_player(void)
{
    game_player_t *player = malloc(sizeof(game_player_t));
    sfVector2f pos = {0, SIZE_Y - 334 - 400};
    sfIntRect rect = {0, 0, 300, 300};

    player->player = create_obj("resource/zombie.png", pos, rect, 0);
    player->music = sfMusic_createFromFile("resource/death.ogg");
    player->clock = sfClock_create();
    player->seconds = 0;
    player->compt = 0;
    player->y = 3;
    player->jump = 1;
    return (player);
}
