/*
** EPITECH PROJECT, 2018
** MUL_my_runner_2018
** File description:
** main.c
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
#include <time.h>
#include "my.h"
#include "struct.h"

char *my_open(char *av)
{
    char *map = malloc(sizeof(char) * 100000);
    int fd;
    int rd;
    if (av == NULL)
        return ("####");
    fd = open(av, O_RDONLY);
    if (fd < 0)
        return ("####");
    rd = read(fd, map, 100000);
    map[rd] = '\0';
    close(fd);
    return (map);
}

int my_h(char *av)
{
    if (av != NULL && av[0] == '-' && av[1] == 'h' && av[2] == '\0') {
        write(1, "Finite runner created with CSFML.\n\n", 35);
        write(1, "USAGE\n", 6);
        write(1, "\t./my_runner [<map>]\n\n\n\n", 24);
        write(1, "OPTIONS:\n", 9);
        write(1, "\t-h\t\tprint the usage and quit.\n\n\n\n", 34);
        write(1, "USER INTERACTIONS:\n", 19);
        write(1, "\t[ESCAPE_KEY]\tleave\n", 20);
        write(1, "\t[SPACE_KEY]\tjump\n\n\n\n", 21);
        write(1, "MAP FORMAT:\n", 12);
        write(1, "\tThe file must only contain\t'#' (block)\n\t\t\t\t\t", 45);
        write(1, "'%' (lava)\n\t\t\t\t\t' ' (void)\n\t\t\t\t\t" , 32);
        write(1, "'\\n' (new line)\n" , 16);
        write(1, "\tYou can see an example of map in 'resource/map'.\n", 50);
        return (1);
    }
    return (0);
}

int main(int ac, char *av[])
{
    obj_window_t *window;
    game_obj_t *block;
    game_player_t *player;

    if (my_h(av[1]) && ac)
        return (0);
    player = create_player();
    window = create_score(create_fond());
    window->av = av;
    block = my_menu(window, window->av, my_valid_map(window->av), player);
    while (sfRenderWindow_isOpen(window->w)) {
        window->game = 1;
        if (window->mode == 3 || window->mode == 2)
            block = my_normal_mode(window, block, player);
        else if (window->mode == 1)
            block = my_infini_mode(window, block, player);
    }
    my_score(window);
    destroy_all_block(block, player, window);
    return (0);
}
