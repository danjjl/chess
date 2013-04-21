#ifndef DEF_TERMINAL
#define DEF_TERMINAL

#include <cstddef>

#include <iostream>
#include "../../board.h"
class Render
{
	public:
	Render(Board const& board);
	~Render();
	void draw() const;
	void pat() const;
	void checkmate() const;
	void drawBorder(std::vector<Coordinate> const& moves) const;
	bool input(Coordinate &click);

	private:
	const Board *m_board;
	char m_piece[7][2];
};
#endif
