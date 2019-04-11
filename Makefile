##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## my make file
##

CC	=	gcc

SRC	=	main.c 				\
		my_create.c			\
		draw_obj.c			\
		my_destroy.c		\
		create_obj.c		\
		move.c				\
		menu.c				\
		parallax.c			\
		my_score2.c			\
		menu_2.c			\
		mode_play.c			\
		my_score.c			\


OBJ	=	$(SRC:.c=.o)

NAME =	my_runner

FLAGS	=	-W \
			-Wextra \
			-Werror \
			-Wall \
			-lcsfml-graphics \
			-lcsfml-audio \
			-lcsfml-window \
			-lcsfml-system \

RM = rm -rf

all:
		$(CC) $(SRC) -g3 $(FLAGS) -o $(NAME)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re: 		fclean all
