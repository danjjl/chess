#ifndef DEF_ROOK
#define DEF_ROOK

#include"../piece.h"
class Rook : public Piece
{
	public:
	Rook(Colour colour);

	std::vector<Coordinate> findMoves(Coordinate const& point, bool eraseCheckMoves = true) const;

	Piece* clone() const;

	int getType() const;

};
#endif
