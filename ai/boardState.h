#ifndef DEF_BOARDSTATE
#define DEF_BOARDSTATE

#include <thread>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "../board.h"
#include "../colour.h"

#include <iostream>


class BoardState
{
	public:
	BoardState(Board const& board, Colour colour, int sign, bool firstIni = false);
	~BoardState();
	BoardState* newMove(Board &board);
	void deleteChildren(int butOne = -1);

	private:
	BoardState* firstLevel(Board &board);
	int downLevel(int totalMoves, int numDown, Colour *colour);
	BoardState* findBoard(Board const& board);

	void addChildren();
	Board* getBoard() const;//Move to private

	void thread_func(unsigned int numMoves, int *value, const Coordinate from, const Coordinate to, Colour *stopColour);
	void thread_caller(unsigned int numMoves, int &bestMove, int &maxVal);

	private:
	Board *m_board;
	Colour m_colour;
	int m_sign;
	std::vector<Coordinate> m_origins;
	std::vector<Coordinate> m_destinations;
	int m_value;
	unsigned int m_numMoves;
	std::vector<BoardState*> m_child;
};
#endif
