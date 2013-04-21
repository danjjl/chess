#ifndef DEF_PIECE
#define DEF_PIECE
#include <cstddef>

#include "colour.h"
class Board;
#include "coordinate.h"
#include <vector>

class Piece
{
	public:
	virtual ~Piece(){};

	void setBoard(Board *board);

	Colour getColour() const;
	bool moved() const;
	unsigned int getMovedOnTurn() const;

	virtual void move(Coordinate const& from, Coordinate const& to);

	virtual Piece* clone() const = 0;
	virtual std::vector<Coordinate> findMoves(Coordinate const& point, bool eraseCheckMoves = true) const = 0;

	virtual int getType() const = 0;

	protected:
	Board *m_board;
	Colour m_colour;
	bool m_moved;
	unsigned int m_movedOnTurn;

	Piece(Colour colour);

	void movesInDirection(std::vector<Coordinate> &points, Coordinate testPoint, int x, int y, bool repeat = true) const;

	void fEraseCheckMoves(std::vector<Coordinate> &moves, Coordinate const& point) const;
};
#endif
