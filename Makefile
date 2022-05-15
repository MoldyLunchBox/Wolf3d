CC = gcc
FLAGS = -Wextra -Werror -Wall
OBJS =	main.o\

INCLUDE = -I/Users/$$USER/.brew/Cellar/sdl2/2.0.22/include \
		-I/Users/$$USER/.brew/Cellar/sdl2_ttf/2.0.15/include \
		-I/Users/$$USER/.brew/Cellar/sdl2_mixer/2.0.4_3/include \
		-I/Users/$$USER/.brew/Cellar/sdl2_image/2.0.5/include
LIB = -L /Users/$$USER/.brew/Cellar/sdl2/2.0.22/lib \
		-L /Users/$$USER/.brew/Cellar/sdl2_ttf/2.0.15/lib \
		-L /Users/$$USER/.brew/Cellar/sdl2_mixer/2.0.4_3/lib \
		-L /Users/$$USER/.brew/Cellar/sdl2_image/2.0.5/lib
SDL = `sdl2-config --cflags --libs` -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_image

LIBFT_DIR = ./libft

LIBFT_LIB = $(LIBFT_DIR)/libft.a

#FLAGS = `sdl2-config --cflags --libs` -lSDL2_image -lm

GAME = wolf3d

all :
	gcc -g  main.c parsing.c init_loading.c tools.c tools_2.c load_textures.c load_textures_2.c events.c mouse_events_1.c mouse_events_2.c sprites.c screens.c play.c render_1.c render_2.c render_3.c -o  wolf3d $(INCLUDE) $(LIB) $(SDL) $(LIBFT_LIB)