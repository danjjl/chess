#ifndef DEF_KNIGHT
#define DEF_KNIGHT

#include"../piece.h"
class Knight : public Piece
{
	public:
	Knight(Colour colour);

	std::vector<Coordinate> findMoves(Coordinate const& point, bool eraseCheckMoves = true) const;

	Piece* clone() const;

	int getType() const;
};
#endif
