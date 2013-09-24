#include "boardState.h"
//TODO I KILLED THE AI :(; BUG CAN'T PUT CHECKMATE (-> can't finish game (wonder why...))
/*These values should be fine tuned to maximise AI efficency*/
//Evaluation of a move is calulated +- Randomness
#define RANDOMNESS 5
//Minimum calculated moves in advance (Next time you play)
#define MIN_PREVISION 3
//Minimum moves calculated (total off all possible moves)
#define MIN_MOVES 10000

using namespace std;
//REMOVE BoardState(board, white, -1, true);//Black AI
//A BoardState reflects the game at a certain moment
BoardState::BoardState(Board const& board, Colour colour, int sign, bool firstIni)
{
	m_board = new Board(board);
	m_colour = colour;
	m_sign = sign;
	//->Oponents move on first turn
	m_destinations = board.colourMoves(m_colour, true, &m_origins);//m_origins is also populated at this line
	m_numMoves = m_origins.size();
	m_value = -100000 * m_sign;//going to use this value to not calculate all branches !!! :)

	if(m_numMoves == 0)
		m_value = m_board->eval(m_numMoves, m_colour);

	if(firstIni)//Only used once for first ever created object
	{
		srand (time(NULL));//TODO MOVE, CALLED TWICE FOR AI VS AI
		if(sign == 1)//White ai
		{
			m_child.push_back(new BoardState(board, ~m_colour, m_sign * -1));//As if initial board was a black turn player
			m_numMoves = 1;
		}
		else
			addChildren();
	}
}
BoardState::~BoardState()
{
	delete m_board;//Children have already been deleted if destructor is called
	m_board = NULL;
}
BoardState* BoardState::newMove(Board &board)
{
	BoardState* currentBoard = findBoard(board);//Find board (last move was opponent)
	BoardState* nextBoard = currentBoard->firstLevel(board); //look for new move, return pointer to played move

	delete currentBoard;//Ouuf was the last memory leak
	currentBoard = NULL;

	return nextBoard;
}

BoardState* BoardState::firstLevel(Board &board)//Main difference between firstLevel and downLevel is firstLevel writes a move to baord
{
	int maxVal = -100000 * m_sign;
	int bestMove = 0;

	if(m_child.empty())
		addChildren();

	thread_caller(m_numMoves, bestMove, maxVal);

	std::cout << "\t" << m_origins[bestMove].x() + 1<< "," << m_origins[bestMove].y() + 1<< " : " << m_destinations[bestMove].x() + 1<< "," << m_destinations[bestMove].y() + 1<< "\t" << maxVal << std::endl << std::endl;//TODO remove in release

	board.get(m_origins[bestMove])->move(m_origins[bestMove], m_destinations[bestMove]);

	deleteChildren(bestMove);//except bestMove

	return m_child[bestMove];
}

void BoardState::thread_caller(unsigned int numMoves, int &bestMove, int &maxVal)
{
	int *values  = new int[numMoves];
	thread *threads = new thread[numMoves];

	Colour stopColour = m_colour;
	if((m_board->getTurn() / 2) % 2)
		stopColour.invert();

	for(unsigned int i = 0; i < numMoves; i++)
		threads[i] = thread(&BoardState::thread_func, m_child[i], numMoves, &values[i], m_origins[i], m_destinations[i], &stopColour);

	for(unsigned int i = 0; i < numMoves; i++)
	{
		threads[i].join();

		if(values[i] * m_sign > maxVal * m_sign)
		{
			maxVal = values[i];
			bestMove = i;
		}
	}

	cout << endl;
	delete[] values;
	delete[] threads;

}
void BoardState::thread_func(unsigned int numMoves, int *value, const Coordinate from, const Coordinate to, Colour *stopColour)
{
	*value = downLevel(numMoves, 1, stopColour) + ( RANDOMNESS * (rand() % 2)) - (RANDOMNESS * (rand() % 2));
	m_value = *value;

	std::cout << "\t" << from.x() + 1<< "," << from.y() + 1<< " : " << to.x() + 1<< "," << to.y() + 1<< "\t" << *value << std::endl;//TODO remove in release
}


int BoardState::downLevel(int totalMoves, int numDown, Colour *colour)
{
	if(m_numMoves != 0)//Not a game end, if not m_value had been calculated at child creation
	{
		if(!m_child.empty() || (numDown < MIN_PREVISION) || (totalMoves < MIN_MOVES) /*|| m_colour == *colour*/)//All children will stop at same color (player colour, //TODO optimize and change to ennemy colour)//TODO NEWLY INTRODUCED BUG WITH COLOUR
		{
			if(m_child.empty())//Make new children
			{
				addChildren();
				totalMoves *= m_numMoves;
			}
			else
			{
				totalMoves *= (m_numMoves / 2) + 1;//add a few moves if children are already born
			}

			for (unsigned int i = 0; i < m_numMoves; i++)
			{
				int tempVal = m_child[i]->downLevel(totalMoves + 1, numDown + 1, colour);//(Could deadlock in each player can only play one move (would never end))
				if((tempVal * m_sign) > (m_value * m_sign))
					m_value = tempVal;
			}
		}
		else//to many children already -> stop
			m_value  = m_board->eval(m_numMoves, m_colour);
	}

	return m_value;
}
BoardState* BoardState::findBoard(Board const& board)
{
	int newRoot = -1;//Exprès pour essayer de provoquer une segfault si rien n'est trouve

	for(unsigned int i = 0; i < m_numMoves; i++)
		if(board == *m_child[i]->getBoard())//Comparaison needs an object (not a pointer -> *)
			newRoot = i;

	deleteChildren(newRoot);

	return m_child[newRoot];
}
void BoardState::deleteChildren(int butOne)
{
	int size = m_child.size();
	for(int i = 0; i < size; i++)
		if(i != butOne)//overloading with this test, (default value is -1)
			if(m_child[i] != NULL)
			{
				m_child[i]->deleteChildren();//Neat recursion if children deleted can delete direct children
				delete m_child[i];
				m_child[i] = NULL;
			}
}

Board* BoardState::getBoard() const
{
	return m_board;
}
void BoardState::addChildren()
{
	for(unsigned int i = 0 ; i < m_numMoves; i++)
	{
		Board tempBoard(*m_board);
		tempBoard.get(m_origins[i])->move(m_origins[i], m_destinations[i]);
		tempBoard.addTurn();
		m_child.push_back(new BoardState(tempBoard, ~m_colour, m_sign * -1));
	}
}
