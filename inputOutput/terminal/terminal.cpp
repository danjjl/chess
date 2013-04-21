#include "terminal.h"
using namespace std;

Render::Render(Board const& board)
{
	cout << "\nHello welcome to the terminal version of my chess game.\n \nAt each turn you will be prompted twice to give an input.\nThe first time to select a piece, the second time to choose where the piece goes.\nThe inputs must be filed in the form ColumnRow \n\nex : to move white pawn from D2 -> D4\n Please fill your selection : 42\n Please fill your selection : 44\n\n to quit enter 555" << endl;
	m_board = &board;

	m_piece[1][0] = 'P';
	m_piece[1][1] = 'p';
	m_piece[2][0] = 'N';
	m_piece[2][1] = 'n';
	m_piece[3][0] = 'B';
	m_piece[3][1] = 'b';
	m_piece[4][0] = 'R';
	m_piece[4][1] = 'r';
	m_piece[5][0] = 'Q';
	m_piece[5][1] = 'q';
	m_piece[6][0] = 'K';
	m_piece[6][1] = 'k';
}

void Render::draw() const
{
	cout << endl;
	int a = 0;
	int b = 0;
	Coordinate point(0,7);
	for(unsigned int i = 0; i < 8; i ++)
	{
		cout << 8 - i << " |";
		for(unsigned int j = 0; j < 8; j++)
		{
			if((j+i) % 2)//black tile
				cout << "-";
			else//white tile
				cout << " ";
			if(m_board->get(point) != NULL)
			{
				if(m_board->get(point)->getColour() == Black())
				{
					b = 1;
				}
				else
				{
					b = 0;
				}

				if(dynamic_cast<Pawn *>(m_board->get(point)))
					a = 1;
				else if(dynamic_cast<Knight *>(m_board->get(point)))
					a = 2;
				else if(dynamic_cast<Bishop *>(m_board->get(point)))
					a = 3;
				else if(dynamic_cast<Rook *>(m_board->get(point)))
					a = 4;
				else if(dynamic_cast<Queen *>(m_board->get(point)))
					a = 5;
				else if(dynamic_cast<King *>(m_board->get(point)))
					a = 6;

				cout << m_piece[a][b];
			}
			else
				cout << " ";//no piece

			if((j+i) % 2)//black tile
				cout << "-|";
			else//white tile
				cout << " |";

			point.addX();

		}
		point.addY(-1);
		point.x(0);
		cout << endl;
	}
	cout << "    ";
	for(unsigned int i = 0; i < 8; i++)
		cout << i+1 << "   ";
	cout << endl;
}

void Render::pat() const
{
	cout << "Pat" << endl;
}

void Render::checkmate() const
{
	cout << "Checkmate" << endl;
}

Render::~Render()
{
}
void Render::drawBorder(std::vector<Coordinate> const& moves) const
{
}
bool Render::input(Coordinate &click)
{
	bool close = false;
	bool notValid = true;
	int i = 0;
	while(notValid)
	{
		cout << endl;
		cout << "Please fill your selection : ";
		cin >> i;

		if(i == 555)
		{
			notValid = false;
			close = true;
		}
		else if(i == 0)
		{
			//Do nothing trick to skip quicker to restarting while for somme non valid inputs
		}
		else
		{
			int y = i % 10;
			int x = (i - y) / 10;
			if(x > 0 && y > 0 && x <= 8 && y <= 8)
			{
				click.x(x - 1);
				click.y(y - 1);
				notValid = false;
			}
		}
		cout << endl;
	}
	return close;
}
