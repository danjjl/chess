#ifndef DEF_SDL
#define DEF_SDL
#include <cstddef>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "../../board.h"
class Render
{
	public:
	Render(Board const& board);
	~Render();
	void draw() const;
	void pat();
	void checkmate();
	void drawBorder(std::vector<Coordinate> const& moves) const;
	bool input(Coordinate &click);
	private:
	void waitQuit();

	private:
	const Board *m_board;
	SDL_Surface *m_screen;
	SDL_Surface* m_boardPicture;
	SDL_Surface *m_border;
	SDL_Surface* m_piece[7][2];

	SDL_Event m_event;
};
//	SDL_Rect operator=(Coordinate const& point);
	SDL_Rect convert(Coordinate const& point);
#endif
