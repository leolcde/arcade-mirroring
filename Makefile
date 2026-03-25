##
## Project  -  arcade
## Date     -  March 20th 2026
##
## Copyright (c) 2026 Jules Nourdin
##

C			=	g++
CFLAGS		=	-Wall -Wextra -std=c++20 -I./include -fno-gnu-unique -fPIC

BIN			=	arcade
CORE_SRC	=	src/main.cpp \
				src/utils.cpp \
				src/menu.cpp \
				src/launcher.cpp
CORE_OBJ	=	$(CORE_SRC:.cpp=.o)

GRAPHICS_LIBS	= arcade_ncurses.so arcade_libcaca.so

NCURSES_SRC		= lib/graphics/NCurses.cpp
NCURSES_OBJ		= $(NCURSES_SRC:.cpp=.o)
CACA_SRC		= lib/graphics/Caca.cpp
CACA_OBJ		= $(CACA_SRC:.cpp=.o)

GAMES_LIBS		= Snake.so

SNAKE_SRC		= lib/games/Snake.cpp
SNAKE_OBJ		= $(SNAKE_SRC:.cpp=.o)

all: core graphicals games

core: $(BIN)

$(BIN): $(CORE_OBJ)
	$(C) $(CFLAGS) -o $(BIN) $(CORE_OBJ) -ldl

graphicals: $(foreach lib,$(GRAPHICS_LIBS),lib/graphics/$(lib))

games: $(foreach lib,$(GAMES_LIBS),lib/games/$(lib))

lib/graphics/NCurses.so: $(NCURSES_OBJ)
	$(C) $(CFLAGS) -shared -o $@ $(NCURSES_OBJ) -lncurses

lib/graphics/Caca.so: $(CACA_OBJ)
	$(C) $(CFLAGS) -shared -o $@ $(CACA_OBJ) -lcaca

lib/games/Snake.so: $(SNAKE_OBJ)
	$(C) $(CFLAGS) -shared -o $@ $(SNAKE_OBJ)

%.o: %.cpp
	$(C) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(CORE_OBJ)
	rm -f $(NCURSES_OBJ)
	rm -f $(SNAKE_OBJ)

fclean: clean
	rm -f $(BIN)
	rm -f lib/graphics/*.so
	rm -f lib/graphics/*.o
	rm -f lib/games/*.so
	rm -f lib/games/*.o

re: fclean all

.PHONY: all core graphicals games clean fclean re
