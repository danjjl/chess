#ifndef DEF_BISHOP
#define DEF_BISHOP

#include "../piece.h"
class Bishop : public Piece
{
	public:
	Bishop(Colour colour);

	std::vector<Coordinate> findMoves(Coordinate const& point, bool eraseCheckMoves = true) const;

	Piece* clone() const;

	int getType() const;
};
#endif
