#include "rook.h"
#include "../board.h"
//Public
Rook::Rook(Colour colour) : Piece(colour)
{
}


std::vector<Coordinate> Rook::findMoves(Coordinate const& point, bool eraseCheckMoves) const
{
	std::vector<Coordinate> points;
	movesInDirection(points, point, 1, 0);//RIGHT
	movesInDirection(points, point, -1, 0);//LEFT
	movesInDirection(points, point, 0, 1);//TOP
	movesInDirection(points, point, 0, -1);//BOTTOM

	if(eraseCheckMoves)
		fEraseCheckMoves(points, point);

	return points;
}


Piece* Rook::clone() const
{
	return new Rook(*this);
}

int Rook::getType() const
{
	return 5;
}
