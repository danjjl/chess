#MAIN SOURCE
SOURCE = main.cpp board.cpp colour.cpp coordinate.cpp piece.cpp ./pieces/bishop.cpp ./pieces/king.cpp ./pieces/knight.cpp ./pieces/pawn.cpp ./pieces/queen.cpp ./pieces/rook.cpp
#AI
AI = ./ai/boardState.cpp
#RENDERING
SDL = ./inputOutput/sdl/sdl.cpp
TERMINAL = ./inputOutput/terminal/terminal.cpp

#COMPILE OPTIONS
THREAD = -std=c++0x -pthread
WFLAGS = -Wall -Wextra
OPTIMIZATION = -ftree-vectorize -O3

#SDL OPTIONS
LIB_SDL = -DINC_SDL -lSDLmain -lSDL -lSDL_image -I/usr/include/SDL

debug : $(SOURCE) $(TERMINAL) $(AI)
	g++ $(WFLAGS) -g $(SOURCE) $(TERMINAL) $(AI) $(THREAD) -o chess

chess : $(SOURCE) $(SDL) $(AI)
	g++ $(SOURCE) $(SDL) $(AI) $(THREAD) -m64 $(LIB_SDL) $(OPTIMIZATION) -msse2 -o ../release/chess

chesst : $(SOURCE) $(TERMINAL) $(AI)
	g++ $(SOURCE) $(TERMINAL) $(AI) $(THREAD) -m64 $(OPTIMIZATION) -msse2 -o ../release/chesst
