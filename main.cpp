#include "main.h"
/*Count code lines j=0; for i in $(find "/home/jonathan/Documents/Programmation/chess/" | egrep '\.h|\.cpp'); do echo $i; ((j += $(cat $i | wc -l))); done; echo $j
*/

/*
Program can be called with two arguments (white, black): type of each player (h for human, c for computer)
A game ends when a player calls for an end or when game reaches end(checkmate, pat)
*/

//Determines who the players are (human or ai), launches game
int main (int argc, char *argv[])
{
	//True if human being (default Human-AI)
	bool player1 = true;
	bool player2 = false;

	//If non-default players launch game with two arguments (first is white)
	if(argc > 2)
	{
			if(argv[1][0] == 'c')
				player1 = false;

		if(argv[2][0] == 'h')
			player2 = true;
	}

	chessGame(player1, player2);
	return 0;
}

//Receives type of both players (human(true) or AI(false))
void chessGame(bool player1, bool player2)
{
	White playerColour;//Player colour is the colour of the player at a given turn (White starts)
	Board board;
	Render render(board);//Draw initial Board

	//Human-Human Game
	if(player1 && player2)
		while(!turn(render, board, playerColour, true)){}//turn false if one player decided to quit or on endgame
	//AI-AI Game
	else if(!player1 && !player2)
	{
		int i = 0;
		BoardState *player[2];
		player[0] = new BoardState(board, ~playerColour, 1, true);//white
		player[1] = new BoardState(board, playerColour, -1, true);//black

		while(!turn(render, board, playerColour, false, &player[i]))
			i = ((i + 1) % 2);//Switch ai

		player[0]->deleteChildren();//Empty AI
		player[1]->deleteChildren();
		delete player[0];
		delete player[1];
	}
	//AI vs Human or Human vs AI
	else
	{
		bool player = player1;
		int sign = 1;//White AI
		if(player1)
			sign = -1;//Black AI
		BoardState *ai = new BoardState(board, playerColour, sign, true);

		while(!turn(render, board, playerColour, player, &ai))
			player = !player;//Switch player

		ai->deleteChildren();//Empty AI
		delete ai;
	}
}

//Plays a turn, returns if player quits or endgame
bool turn(Render &render, Board &board, Colour &playerColour, bool player, BoardState* *currentAi)
{
	bool close = false;
	render.draw();
	if(board.colourMoves(playerColour, true).size() != 0)//not a checkmate or pat case
	{
		if(player)
			close = playerTurn(render, board, playerColour);
		else
			aiTurn(board, *currentAi);

		playerColour.invert();
		board.addTurn();
	}
	else//pat or checkmate case
	{
		close = true;
		if(board.kingInDanger(playerColour))//check + no moves => checkmate
			render.checkmate();
		else
			render.pat();
	}

	return close;
}

//Asks a player to move piece, returns if player quits
bool playerTurn(Render &render, Board &board, Colour &playerColour)
{
	bool close = false;
	bool played = false;
	std::vector<Coordinate> moves;
	Coordinate clickPiece;
	Coordinate clickMove;
	while(!played && !close)//while not played, not quit
	{
		close = render.input(clickPiece);//Select piece
		if(!close)
			if(board.get(clickPiece) != NULL && board.get(clickPiece)->getColour() == playerColour) //selected a valid piece
			{
				moves = board.get(clickPiece)->findMoves(clickPiece, true);
				render.drawBorder(moves);
				close = render.input(clickMove);//Select move
				if(!close)
					if(checkMove(moves, clickMove))
					{
						board.get(clickPiece)->move(clickPiece, clickMove);
						played = true;
					}
			}
	}
	return close;
}

void aiTurn(Board &board, BoardState* &currentAi)
{
	BoardState* tempState =  currentAi->newMove(board);
	delete currentAi;//Delete old stem
	currentAi = tempState;
}

//return (move in moves)
bool checkMove(std::vector<Coordinate> const& moves, const Coordinate point)
{
	bool valid = false;
	for(unsigned int i = 0; i < moves.size() && !valid; i++)
		if(moves[i] == point)
			valid = true;
	return valid;
}
