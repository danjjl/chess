#include "king.h"
#include "../board.h"
#include <iostream>
using namespace std;
//Public
King::King(Colour colour) : Piece(colour)
{
}


std::vector<Coordinate> King::findMoves(Coordinate const& point, bool eraseCheckMoves) const
{
	std::vector<Coordinate> points;

	movesInDirection(points, point, 1, 0, false);//RIGHT
	movesInDirection(points, point, -1, 0, false);//LEFT
	movesInDirection(points, point, 0, 1, false);//TOP
	movesInDirection(points, point, 0, -1, false);//BOTTOM

	movesInDirection(points, point, 1, 1, false);//TOP_RIGHT
	movesInDirection(points, point, -1, 1, false);//TOP_LEFT
	movesInDirection(points, point, -1, -1, false);//BOTTOM_LEFT
	movesInDirection(points, point, 1, -1, false);//BOTTOM_RIGHT


//Rock
	if(!m_moved)
	{
		rock(1, points, point);//RIGHT
		rock(-1, points, point);//LEFT
	}

	if(eraseCheckMoves)
		fEraseCheckMoves(points, point);

	return points;
}


void King::move(Coordinate const& from, Coordinate const& to)
{
	if(((from.x() - to.x()) * (from.x() - to.x())) > 1)//rock
	{
		int side;
		int rookSide;
		if((from.x() - to.x()) < 0)
		{
			side = 1;
			rookSide = 7;
		}
		else
		{
			side = -1;
			rookSide = 0;
		}
		Coordinate rookFrom(rookSide, from.y());
		Coordinate rookTo(to.x() - side, from.y());
		Piece::move(rookFrom, rookTo);
	}
	Piece::move(from, to);
}


Piece* King::clone() const
{
	return new King(*this);
}

int King::getType() const
{
	return 10;
}



//Private
void King::rock(int side, std::vector<Coordinate> &points, Coordinate const& point) const//TODO maybee find a better system to know if rock is possible takes three functions and lot's of loops
{
	Coordinate test;
	test.y(point.y());
	if (side > 0)//side initialised to 0; so no else
		test.x(7);
	bool rock = true;

	if(m_board->get(test) != NULL && dynamic_cast<Rook *>(m_board->get(test)) && !m_board->get(test)->moved())//if rook didn't move
	{
		test = point;
		for(unsigned int i = point.x(); i > 1 && i < 6; i+= side)//teste if space between rook and king is empty
		{
			test.addX(side);
			if(m_board->get(test) != NULL)//Space rook king empty
				rock = false;
		}

		if(rock && rockNoDanger(side, point))
			movesInDirection(points, point, 2 * side, 0, false);//Will add left/right rock to possibilites
		
	}
}

bool King::rockNoDanger(int side, Coordinate const& point) const
{
	std::vector<Coordinate> dangerTiles = m_board->colourMoves(~m_colour);
	bool possible = true;

	Coordinate point1 = point;//point, point1 & point2 are the three points that have to be safe
	point1.addX(side);
	Coordinate point2 = point1;
	point2.addX(side);

	for(unsigned int i = 0; (i < dangerTiles.size()) && possible; i++)//Vérifie que ni le roi ni les deux cases que le roi parcourt pour rocker son en danger.
		if(dangerTiles[i] == point || dangerTiles[i] == point1 || dangerTiles[i] == point2)
			possible = false;
	return possible;
}
