/*
** EPITECH PROJECT, 2018
** MUL_my_runner_2018
** File description:
** my_create.c
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/Window.h>
#include <SFML/System/Vector2.h>
#include <SFML/System/Export.h>
#include <SFML/System/Time.h>
#include <SFML/System/Types.h>
#include "struct.h"
#include "my.h"

void my_putchar(char c, int fd)
{
    write(fd, &c, 1);
}

int my_put_nbr(int nb, int fd)
{
    if (nb >= 10)
        my_put_nbr(nb / 10, fd);
    my_putchar((nb % 10) + 48, fd);
    return (0);
}

int my_getnbr(char const *str)
{
    int j = 0;
    int k = 1;
    int rtn = 0;

    while (str[j] >= 48 && str[j] <= 57)
        j++;
    j--;
    while (0 <= j) {
        rtn = rtn + (str[j] - 48) * k;
        k = k * 10;
        j--;
    }
    return (rtn);
}

char *give_score(void)
{
    int i = 0;
    int fd = open("resource/score", O_RDWR);
    char *score = malloc(sizeof(char) * 12);

    i = read(fd, score, 12);
    close(fd);
    score[i] = '\0';
    return (score);
}

void my_score(obj_window_t *window)
{
    int fd = open("resource/score", O_RDWR);
    char *score = give_score();

    if (window->score.compt1 > my_getnbr(score))
        my_put_nbr(window->score.compt1, fd);
    close(fd);
    free(score);
}
