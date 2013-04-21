#include "board.h"
//Public:
Board::Board()
{
	m_turn = 0;

	for(unsigned int i = 0; i < 8; i++)
		for(unsigned int j = 0; j < 8; j++)
			tile[i][j] = NULL;

	White white;
	Black black;

	for(unsigned int i = 0; i < 8; i++)
	{
		tile[i][1] = new Pawn(white);
		tile[i][6] = new Pawn(black);
	}

	tile[0][0] = new Rook(white);
	tile[7][0] = new Rook(white);
	tile[0][7] = new Rook(black);
	tile[7][7] = new Rook(black);

	tile[1][0] = new Knight(white);
	tile[6][0] = new Knight(white);
	tile[1][7] = new Knight(black);
	tile[6][7] = new Knight(black);

	tile[2][0] = new Bishop(white);
	tile[5][0] = new Bishop(white);
	tile[2][7] = new Bishop(black);
	tile[5][7] = new Bishop(black);

	tile[3][0] = new Queen(white);
	tile[3][7] = new Queen(black);

	tile[4][0] = new King(white);
	tile[4][7] = new King(black);
	
	for(unsigned int i = 0; i < 8; i++)
		for(unsigned int j = 0; j < 8; j++)
			if(tile[i][j] != NULL)
				tile[i][j]->setBoard(this);//Pieces need to be board conscious
}

Board::Board(Board const& board)//Creates a copy of an existing board
{
	m_turn = board.getTurn();

	for(unsigned int i = 0; i < 8; i++)
		for(unsigned int j = 0; j < 8; j++)
		{
			tile[i][j] = NULL;
			Coordinate temp(i,j);
			if(board.get(temp) != NULL)
			{
				tile[i][j] = board.get(temp)->clone();
				tile[i][j]->setBoard(this);//clone makes pieces think they are on the old board -> setBoard(...)
			}
		}
}

Board::~Board()
{
	for(unsigned int i = 0; i < 8; i++)
		for(unsigned int j = 0; j < 8; j++)
			if(tile[i][j] != NULL)
			{
				delete tile[i][j];
				tile[i][j] = NULL;//Not compulsary but clean :)
			}
}


Piece* Board::get(Coordinate const& point) const
{
	return tile[point.x()][point.y()]; //Careful no seg fault checks!!
}


void Board::add(Coordinate const& point, Piece *piece)
{
	tile[point.x()][point.y()] = piece; //Careful no seg fault checks!!
}

void Board::Delete(Coordinate const& point)
{
	delete tile[point.x()][point.y()]; //Careful no seg fault checks!!
	tile[point.x()][point.y()] = NULL;
}


void Board::addTurn()
{
	m_turn ++;
}

unsigned int Board::getTurn() const
{
	return m_turn;
}


bool Board::kingInDanger(Colour colour) const
{
	bool danger = false;
	Coordinate kingPosition = findKing(colour);
	std::vector<Coordinate> dangerTiles = colourMoves(~colour);
	for(unsigned int i = 0; (i < dangerTiles.size()) && !danger; i++)
		if(dangerTiles[i] == kingPosition)
			danger = true;
	return danger;
}

std::vector<Coordinate>Board::colourMoves(Colour colour, bool checkCheck, std::vector<Coordinate> *origins) const//checkCheck is a bit ugly it is used to avoid recusrsive uses of colourMoves, internal uses (in class) are default => false, external can be true => check moves don't put you in check position
{
	std::vector<Coordinate> moves;
	Coordinate testPoint;
	for(unsigned int i = 0; i < 8; i++)
	{
		testPoint.y(0);
		for(unsigned int j = 0; j < 8; j++)
		{
			if(tile[i][j] != NULL && tile[i][j]->getColour() == colour)
			{
				if(dynamic_cast<King *>(tile[i][j]) && !(tile[i][j]->moved()) && !checkCheck)
					;//if it's a king that hasn't moved he can't be a threat to the other king(doing this because rocks require finding enemy moves(would be turning in circles if both kings haven't moved))
				else
				{
					int position = moves.size();
					std::vector<Coordinate> temp = tile[i][j]->findMoves(testPoint, checkCheck);//For a king passes three times in here!
					moves.insert(moves.end(), temp.begin(), temp.end());//concat

					if(origins != NULL)
						for(unsigned int u = position; u < moves.size(); u ++)
							origins->push_back(testPoint);
				}
			}
			testPoint.addY();
		}
		testPoint.addX();
	}
	return moves;
}




int Board::eval(int numMoves, Colour colour)
{
	int sign = -1 + (2 * colour.get());
	int value = 0;

	if(numMoves == 0)//Checkmate and pat
	{
		if(kingInDanger(colour))
			value = (10000) * -sign;
	}

	else
	{
		for(int i = 0; i < 8; i++)
			for(int j = 0; j < 8; j++)
				if(tile[i][j] != NULL)
				{
					int tempSign = -1 + (2 * tile[i][j]->getColour().get());
					if(dynamic_cast<Pawn *>(tile[i][j]))
					{
						int offset;
						if(tempSign == -1)
							offset = 1;
						else
							offset = 6;
						value += ((100  * tempSign) + (5 * (offset - j)));
					}
					else if(dynamic_cast<Knight *>(tile[i][j]))
						value += ((330 - m_turn) * tempSign);
					else if(dynamic_cast<Bishop *>(tile[i][j]))
						value += ((330 + m_turn) * tempSign);
					else if(dynamic_cast<Rook *>(tile[i][j]))
						value += (520 * tempSign);
					else if(dynamic_cast<Queen *>(tile[i][j]))
						value += (980 * tempSign);
				}

		value += ((sign * colourMoves(colour).size()) - (sign * colourMoves(~colour).size()));
	}
	return value;
}


void Board::replace(Coordinate const &to, Piece* newPiece)
{
	Delete(to);
	tile[to.x()][to.y()] = newPiece;
}




//Private
Coordinate Board::findKing(Colour colour) const
{
	Coordinate point;
	bool found = false;

	for(unsigned int i = 0; i < 8 && !found; i ++)
		for(unsigned int j = 0; j < 8 && !found; j++)
			if(tile[i][j] != NULL && dynamic_cast<King *>(tile[i][j]) && tile[i][j]->getColour() == colour)
			{
				point.x(i);
				point.y(j);
				found = true;
			}
	return point;
}



//operator
bool operator==(Board const& board1, Board const& board2)
{
	bool same = true;
	Coordinate testPoint;
	for(unsigned int i = 0; i < 8 && same; i++)
	{
		testPoint.x(i);
		for(unsigned int j = 0; j < 8 && same; j++)
		{
			testPoint.y(j);
			if(board1.get(testPoint) == NULL && board2.get(testPoint) == NULL)
				same = true;
			else if((board1.get(testPoint) == NULL && board2.get(testPoint) != NULL) || (board1.get(testPoint) != NULL && board2.get(testPoint) == NULL))
				same = false;
			else if(((board1.get(testPoint)->getColour() != board2.get(testPoint)->getColour()) || board1.get(testPoint)->getType() != board2.get(testPoint)->getType()))
				same  = false;
		}
	}
	return same;
}
