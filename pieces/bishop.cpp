#include "bishop.h"
#include "../board.h"
//Public
Bishop::Bishop(Colour colour):Piece(colour)
{
}


std::vector<Coordinate> Bishop::findMoves(Coordinate const& point, bool eraseCheckMoves) const
{
	std::vector<Coordinate> points;
	movesInDirection(points, point, 1, 1);//TOP_RIGHT
	movesInDirection(points, point, -1, 1);//TOP_LEFT
	movesInDirection(points, point, -1, -1);//BOTTOM_LEFT
	movesInDirection(points, point, 1, -1);//BOTTOM_RIGHT

	if(eraseCheckMoves)
		fEraseCheckMoves(points, point);
	return points;
}


Piece* Bishop::clone() const
{
	return new Bishop(*this);
}

int Bishop::getType() const
{
	return 3;
}
