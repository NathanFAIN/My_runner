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

char *nbr_str(long nb)
{
    char *str = malloc(16);
    long i = -1;

    for (int i = 0; i < 13; i++)
        str[i] = (i == 0) ? '0' : '\0';
    for (long compt =  nb; compt >= 1; i++)
        compt = compt / 10;
    for (; nb >= 1; i--) {
        str[i] = nb % 10 + 48;
        nb = nb / 10;
    }
    return (str);
}

void my_add_score(obj_window_t *win)
{
    if (sfClock_getElapsedTime(win->score.clock).microseconds < 1000000.0)
        return;
    sfClock_restart(win->score.clock);
    win->score.compt1 = win->score.compt1 + 1;
    sfText_setString(win->score.txt1, nbr_str(win->score.compt1));
}

obj_window_t *create_score(obj_window_t *win)
{
    win->score.seconds = 0;
    win->score.compt1 = 0;
    win->score.txt1 = sfText_create();
    win->score.clock = sfClock_create();
    sfText_setFont(win->score.txt1, sfFont_createFromFile("resource/mc.ttf"));
    sfText_setString(win->score.txt1, "0");
    sfText_setColor(win->score.txt1, sfBlack);
    sfText_setCharacterSize(win->score.txt1, 100);
    sfText_setPosition(win->score.txt1, (sfVector2f) {10, 0});
    return (win);
}
