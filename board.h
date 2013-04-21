#ifndef DEF_BOARD
#define DEF_BOARD

#include "piece.h"
#include "./pieces/bishop.h"
#include "./pieces/king.h"
#include "./pieces/knight.h"
#include "./pieces/pawn.h"
#include "./pieces/queen.h"
#include "./pieces/rook.h"

#include "coordinate.h"
#include "colour.h"
#include <vector>

#include <iostream>

class Board
{
	public:
	Board();
	Board(Board const& board);
	~Board();

	Piece* get(Coordinate const& point) const;

	void add(Coordinate const& point, Piece *piece);
	void Delete(Coordinate const& point);

	void addTurn();
	unsigned int getTurn() const;

	bool kingInDanger(Colour colour) const;
	std::vector<Coordinate> colourMoves(Colour colour, bool checkCheck = false, std::vector<Coordinate> *origins = NULL) const;

	int eval(int numMoves, Colour colour);

	void replace(Coordinate const& to, Piece* newPiece);

	private:
	Coordinate findKing(Colour colour) const;

	private:
	Piece *tile[8][8];
	unsigned int m_turn;
};
bool operator==(Board const& board1, Board const& board2);
#endif
