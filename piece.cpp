#include "piece.h"
#include "board.h"

//Public
void Piece::setBoard(Board *board)
{
	m_board = board;
}


Colour Piece::getColour() const
{
	return m_colour;
}

bool Piece::moved() const
{
	return m_moved;
}

unsigned int Piece::getMovedOnTurn() const
{
	return m_movedOnTurn;
}


void Piece::move(Coordinate const& from, Coordinate const& to)
{
	if(m_board->get(to) != NULL)
		m_board->Delete(to);
	m_board->add(to, m_board->get(from));//using this was cleaner but didn't work for rocks...
	m_board->add(from, NULL);

	m_movedOnTurn = m_board->getTurn();
	m_moved = true;
}



//protected
Piece::Piece(Colour colour)
{
	m_colour = colour;
	m_moved = false;
	m_movedOnTurn  = 0;
}


void Piece::movesInDirection(std::vector<Coordinate> &points, Coordinate testPoint, int x, int y, bool repeat) const
{
	bool test = true;

	while(test)
	{
		testPoint.addX(x);
		testPoint.addY(y);
		if(testPoint.x() < 8 && testPoint.x() >= 0 && testPoint.y() < 8 && testPoint.y() >= 0)//possible move
		{
			if(m_board->get(testPoint) == NULL)
				points.push_back(testPoint);
			else if(m_board->get(testPoint)->getColour() != m_colour)//kill piece
			{
				points.push_back(testPoint);
				test = false;
			}
			else
				test = false;
		}
		else
			test = false;
		if(!repeat)//Uses the same code for single(eg. knight) moves and long(eg. bishop) moves
			test = false;
	}
}


void Piece::fEraseCheckMoves(std::vector<Coordinate> &moves, Coordinate const& point) const
{
	for(unsigned int i = 0; i < moves.size(); )
	{
		Board testBoard(*m_board);//Makes a board copy
		testBoard.get(point)->move(point, moves[i]);
		if(testBoard.kingInDanger(m_colour))
			moves.erase(moves.begin() + i);
		else
			i++;
	}
}
