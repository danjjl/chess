#ifndef DEF_IO
#define DEF_IO

//TODO EDIT COMMENT Only uncomment one off the the rendering inputs
#if defined(INC_SDL)
	#include "sdl/sdl.h"
#endif
#ifndef INC_SDL
	#include "terminal/terminal.h"
#endif

/*
//Template explaining how to create your own rendering engine

#include "../board.h"//Path relative to this file (edit accordingly to your path)

//name and argument of class and methods need to match (you can of course create extra methods for internal use)
class Render
{
	public:
	Render(Board const& board);//Intialise rendering engine (if it needs to), save pointer(pointer because draw doesn't pass any arguments) to board and must draw board
	~Sdl();
	void draw() const;//Draw current board(thanks to pointer)
	void pat() const; //Display pat message
	void checkmate() const; // Display checkmate messageS
	void drawBorder(std::vector<Coordinate> const& moves) const;//CAN ONLY BE DEFINED if possible Highlight tiles passed in moves
	bool input(Coordinate &click);returns the selection of the player; (in main two selections will be asked for (from and to)); returns true if player wants to exit; Coordinate must be : 0 <= point.x,point.y < 8

	private:
	const Board *m_board;//pointer to board given during initialisation
};
*/
#endif
