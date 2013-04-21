#include "knight.h"
#include "../board.h"
//Public
Knight::Knight(Colour colour) : Piece(colour)
{
}


std::vector<Coordinate> Knight::findMoves(Coordinate const& point, bool eraseCheckMoves) const
{
	std::vector<Coordinate> points;

	movesInDirection(points, point, 2, 1, false);
	movesInDirection(points, point, -2, 1, false);
	movesInDirection(points, point, -2, -1, false);
	movesInDirection(points, point, 2, -1, false);

	movesInDirection(points, point, 1, 2, false);
	movesInDirection(points, point, -1, 2, false);
	movesInDirection(points, point, -1, -2, false);
	movesInDirection(points, point, 1, -2, false);

	if(eraseCheckMoves)
		fEraseCheckMoves(points, point);
	return points;
}


Piece* Knight::clone() const
{
	return new Knight(*this);
}

int Knight::getType() const
{
	return 2;
}
