CC = gcc
FLAGS = -Wextra -Werror -Wall
OBJS =	main.o\


FLAGS = `sdl2-config --cflags --libs` -lSDL2_image -lm
GAME = wolf3d

all : $(GAME)

%.o : %.c 
	$(CC) -o $@ -c $<

$(GAME) : $(OBJS)
	$(CC) -o $(GAME) $(OBJS) $(FLAGS)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(GAME)