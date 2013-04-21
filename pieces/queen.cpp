#include "queen.h"
#include "../board.h"
//Public
Queen::Queen(Colour colour) : Piece(colour)
{
}


std::vector<Coordinate> Queen::findMoves(Coordinate const& point, bool eraseCheckMoves) const
{
	std::vector<Coordinate> points;

	movesInDirection(points, point, 1, 0);//RIGHT
	movesInDirection(points, point, -1, 0);//LEFT
	movesInDirection(points, point, 0, 1);//TOP
	movesInDirection(points, point, 0, -1);//BOTTOM

	movesInDirection(points, point, 1, 1);//TOP_RIGHT
	movesInDirection(points, point, -1, 1);//TOP_LEFT
	movesInDirection(points, point, -1, -1);//BOTTOM_LEFT
	movesInDirection(points, point, 1, -1);//BOTTOM_RIGHT

	if(eraseCheckMoves)
		fEraseCheckMoves(points, point);
	return points;
}


Piece* Queen::clone() const
{
	return new Queen(*this);
}

int Queen::getType() const
{
	return 6;
}
