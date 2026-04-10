##
## Project  -  arcade
## Date     -  March 20th 2026
##
## Copyright (c) 2026 Jules Nourdin
##

C			=	g++
CFLAGS		=	-Wall -Wextra -std=c++20 -I./include -fno-gnu-unique -fPIC

BIN			=	arcade

# CORE
CORE_SRC	=	src/main.cpp \
				src/utils.cpp \
				src/menu.cpp \
				src/launcher.cpp
CORE_OBJ	=	$(CORE_SRC:.cpp=.o)

# GRAPHICS
GRAPHICS_LIBS	= arcade_ncurses.so arcade_sfml.so arcade_sdl2.so
NCURSES_SRC		= lib/NCurses.cpp
NCURSES_OBJ		= $(NCURSES_SRC:.cpp=.o)
SFML_SRC		= lib/Sfml.cpp
SFML_OBJ		= $(SFML_SRC:.cpp=.o)
SDL2_SRC		= lib/Sdl2.cpp
SDL2_OBJ		= $(SDL2_SRC:.cpp=.o)

# GAMES
GAMES_LIBS		= arcade_snake.so arcade_nibbler.so
SNAKE_SRC		= lib/Snake.cpp
SNAKE_OBJ		= $(SNAKE_SRC:.cpp=.o)
NIBBLER_SRC		= lib/Nibbler.cpp
NIBBLER_OBJ		= $(NIBBLER_SRC:.cpp=.o)

# BONUS
BONUS_LIBS		= arcade_libcaca.so
CACA_SRC		= bonus/Caca.cpp
CACA_OBJ		= $(CACA_SRC:.cpp=.o)


all: core graphicals games bonus

# CORE COMPIL
core: $(BIN)

$(BIN): $(CORE_OBJ)
	$(C) $(CFLAGS) -o $(BIN) $(CORE_OBJ) -ldl

# GRAPHICS COMPIL
graphicals: $(foreach lib,$(GRAPHICS_LIBS),lib/$(lib))

lib/arcade_ncurses.so: $(NCURSES_OBJ)
	$(C) $(CFLAGS) -shared -o $@ $(NCURSES_OBJ) -lncurses

lib/arcade_sfml.so: $(SFML_OBJ)
	$(C) $(CFLAGS) -shared -o $@ $(SFML_OBJ) -lsfml-graphics -lsfml-window -lsfml-system

lib/arcade_sdl2.so: $(SDL2_OBJ)
	$(C) $(CFLAGS) -shared -o $@ $(SDL2_OBJ) -lSDL2 -lSDL2_ttf

# GAMES COMPIL
games: $(foreach lib,$(GAMES_LIBS),lib/$(lib))

lib/arcade_snake.so: $(SNAKE_OBJ)
	$(C) $(CFLAGS) -shared -o $@ $(SNAKE_OBJ)

lib/arcade_nibbler.so: $(NIBBLER_OBJ)
	$(C) $(CFLAGS) -shared -o $@ $(NIBBLER_OBJ)

# BONUS COMPIL
bonus: $(foreach lib,$(BONUS_LIBS),bonus/$(lib))

bonus/arcade_libcaca.so: $(CACA_OBJ)
	$(C) $(CFLAGS) -shared -o $@ $(CACA_OBJ) -lcaca


%.o: %.cpp
	$(C) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(CORE_OBJ)
	rm -f $(NCURSES_OBJ)
	rm -f $(SFML_OBJ)
	rm -f $(SDL2_OBJ)
	rm -f $(CACA_OBJ)
	rm -f $(SNAKE_OBJ)
	rm -f $(NIBBLER_OBJ)
	rm -f $

fclean: clean
	rm -f $(BIN)
	rm -f lib/*.o
	rm -f lib/*.so
	rm -f bonus/*.o
	rm -f bonus/*.so

re: fclean all

.PHONY: all core graphicals games clean fclean re
