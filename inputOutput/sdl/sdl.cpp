#include "sdl.h"

Render::Render(Board const& board)
{
	m_board = &board;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	SDL_WM_SetCaption("Chess", NULL);

	m_screen = SDL_SetVideoMode(640, 640, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

	m_boardPicture = SDL_DisplayFormat(SDL_LoadBMP("./pictures/board.bmp"));

	m_border = SDL_DisplayFormatAlpha(IMG_Load("./pictures/border.png"));

	m_piece[1][0] = SDL_DisplayFormatAlpha(IMG_Load("./pictures/w_pawn.png"));
	m_piece[1][1] = SDL_DisplayFormatAlpha(IMG_Load("./pictures/b_pawn.png"));
	m_piece[2][0] = SDL_DisplayFormatAlpha(IMG_Load("./pictures/w_knight.png"));
	m_piece[2][1] = SDL_DisplayFormatAlpha(IMG_Load("./pictures/b_knight.png"));
	m_piece[3][0] = SDL_DisplayFormatAlpha(IMG_Load("./pictures/w_bishop.png"));
	m_piece[3][1] = SDL_DisplayFormatAlpha(IMG_Load("./pictures/b_bishop.png"));
	m_piece[4][0] = SDL_DisplayFormatAlpha(IMG_Load("./pictures/w_rook.png"));
	m_piece[4][1] = SDL_DisplayFormatAlpha(IMG_Load("./pictures/b_rook.png"));
	m_piece[5][0] = SDL_DisplayFormatAlpha(IMG_Load("./pictures/w_queen.png"));
	m_piece[5][1] = SDL_DisplayFormatAlpha(IMG_Load("./pictures/b_queen.png"));
	m_piece[6][0] = SDL_DisplayFormatAlpha(IMG_Load("./pictures/w_king.png"));
	m_piece[6][1] = SDL_DisplayFormatAlpha(IMG_Load("./pictures/b_king.png"));

	draw();
}
void Render::draw() const
{
	Coordinate point(0,7);
	int a = 0;
	int b = 0;

	SDL_Rect temp = convert(point);
	SDL_BlitSurface(m_boardPicture, NULL, m_screen, &temp);
	point.y(0);
	for(unsigned int i = 0; i < 8; i ++)
	{
		for(unsigned int j = 0; j < 8; j++)
		{
			if(m_board->get(point) != NULL)
			{
				if(m_board->get(point)->getColour() == Black())
					b = 1;
				else
					b = 0;

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

				SDL_Rect temp2 = convert(point);
				SDL_BlitSurface(m_piece[a][b], NULL, m_screen, &temp2);
			}
			point.addX();
		}
		point.x(0);
		point.addY();
	}
	SDL_Flip(m_screen);
}
void Render::pat()
{
	for(unsigned int i = 0; i < 8; i +=2)
	{
		for(unsigned int j = 0; j < 8; j+=2)
		{
			Coordinate point(i,j);
			SDL_Rect temp = convert(point);
			SDL_BlitSurface(m_border, NULL, m_screen, &temp);
		}
	}
	SDL_Flip(m_screen);
	waitQuit();
}
void Render::checkmate()
{
	for(unsigned int i = 0; i < 8; i ++)
	{
		for(unsigned int j = 0; j < 8; j++)
		{
			Coordinate point(i,j);
			SDL_Rect temp = convert(point);
			SDL_BlitSurface(m_border, NULL, m_screen, &temp);
		}
	}
	SDL_Flip(m_screen);
	waitQuit();
}
Render::~Render()
{
	SDL_FreeSurface(m_screen);
	SDL_FreeSurface(m_boardPicture);
	SDL_FreeSurface(m_border);
	for(unsigned int i = 1; i < 7; i ++)
	{
		SDL_FreeSurface(m_piece[i][0]);
		SDL_FreeSurface(m_piece[i][1]);
	}
	SDL_Quit();
}
void Render::drawBorder(std::vector<Coordinate> const& moves) const
{
	for(unsigned int i = 0; i < moves.size(); i++)
	{
		SDL_Rect temp = convert(moves[i]);//Not realy usefull but avoids warning
		SDL_BlitSurface(m_border, NULL, m_screen, &temp);//TODO don'y pass by convert but by operator=
	}

	SDL_Flip(m_screen);
}
bool Render::input(Coordinate &click)
{
	bool close = false;
	bool noClick = true;
	while(noClick)
	{
		SDL_WaitEvent(&m_event);
		switch(m_event.type)
		{
			case SDL_QUIT:
				close = true;
				noClick = false;
				break;
			case SDL_MOUSEBUTTONUP:
				draw();//Clean board
				click.x(m_event.button.x / 80);
				click.y(7 - (m_event.button.y / 80));//TODO check no problem
				noClick = false;
				break;
		}
	}
	return close;
}

void Render::waitQuit()
{
	bool close = false;
	while(!close)
	{
		SDL_WaitEvent(&m_event);
		if(m_event.type == SDL_QUIT)
			close = true;
	}
}

//SDL_Rect operator=(Coordinate const& point)//TODO Make it work!!
//{
//	SDL_Rect position;
//	position.x = point.x() * 80;
//	position.y = (7 - point.y()) * 80;
//	return position;
//}
SDL_Rect convert(Coordinate const& point)
{
	SDL_Rect position;
	position.x = point.x() * 80;
	position.y = (7 - point.y()) * 80;
	return position;
}
