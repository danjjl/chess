#include "pawn.h"
#include "../board.h"

//Public
Pawn::Pawn(Colour colour) : Piece(colour)
{
}


std::vector<Coordinate> Pawn::findMoves(Coordinate const& point, bool eraseCheckMoves) const
{
	std::vector<Coordinate> points;
	int side = 1; //default white
	int passant = 4;

	if(m_colour == Black())
	{
		side = -1;
		passant = 3;
	}

	coupEnPassant(1, side, passant, points, point);
	coupEnPassant(-1, side, passant, points, point);

	killingMove(side, points, point);

		if(!moved())
			doubleMove(side, points, point);

	normalMove(side, points, point);

	if(eraseCheckMoves)
		fEraseCheckMoves(points, point);

	return points;
}


void Pawn::move(Coordinate const& from, Coordinate const& to)
{
	m_moved = true;
	if(m_colour == Black())//White and black so similar ctrl+C / ctrl+V a pitty
		specialMoves(from, to, 3);
	else
		specialMoves(from, to, 4);
}


Piece* Pawn::clone() const
{
	return new Pawn(*this);
}

int Pawn::getType() const
{
	return 1;
}



//Private
void Pawn::normalMove(int side, std::vector<Coordinate> &points, Coordinate point) const
{
		point.addY(side);
		if(point.y() < 8 && point.y() >= 0)//possible move
		{
			if(m_board->get(point) == NULL)
				points.push_back(point);
		}
}

void Pawn::killingMove(int side, std::vector<Coordinate> &points, Coordinate point) const
{
	int x = point.x();
	if((point.y() + side) >= 0 && (point.y() + side) < 8)
	{
		point.addY(side);
		if((point.x() - 1) >= 0)
		{
			point.addX(-1);//LEFT
			if(m_board->get(point) != NULL && m_board->get(point)->getColour() != m_colour)
				points.push_back(point);
		}
		if((x + 1) < 8)
		{
			point.x(x + 1);//RIGHT
			if(m_board->get(point) != NULL && m_board->get(point)->getColour() != m_colour)
				points.push_back(point);
		}
	}
}

void Pawn::doubleMove(int side, std::vector<Coordinate> &points, Coordinate point) const
{
	point.addY(side);
	if(m_board->get(point) == NULL)
	{
		point.addY(side);
		if(m_board->get(point) == NULL)
			points.push_back(point);
	}
}

void Pawn::coupEnPassant(int cote, int side, int passant, std::vector<Coordinate> &points, Coordinate point) const
{
	if(point.y() == passant)
	{
		if((point.x() + cote) >= 0 && (point.x() + cote) < 8)
		{
			point.addX(cote);//cote refers to right or left
			if(m_board->get(point) != NULL && dynamic_cast<Pawn *>(m_board->get(point)) && ((m_board->get(point)->getMovedOnTurn() + 1) == m_board->getTurn()))
			{
				point.addY(side);
				if(m_board->get(point) == NULL)
					points.push_back(point);
			}
		}
	}
}


void Pawn::specialMoves(Coordinate const& from, Coordinate const& to, int passant)
{

	if(from.y() == passant && from.x() != to.x() && m_board->get(to) == NULL)//coup en passant
	{
		Coordinate temp(to.x(), from.y());
		Piece::move(from, temp);//delete eaten piece
		Piece::move(temp, to);
	}
	else
		Piece::move(from, to);

	if(to.y() == 0 || to.y() == 7)//TODO give choici of new piece, here queen
		m_board->replace(to, new Queen(m_colour));//replace pawn by queen
}
