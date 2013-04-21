#include <cstddef>

#include "board.h"
#include "inputOutput/inputOutput.h"
#include "ai/boardState.h"

//Launches a chess game (human -> player = true)
void chessGame(bool player1, bool player2);
//Runs a chess turn (default for currentAi, because human-human, no AI)
bool turn(Render &render, Board &board, Colour &playerColour, bool playerTurn, BoardState* *currentAi = NULL);
bool playerTurn(Render &render, Board &board, Colour &playerColour);
void aiTurn(Board &board, BoardState* &currentAi);
//Checks a move is a valid move
bool checkMove(std::vector<Coordinate> const& moves, const Coordinate point);
