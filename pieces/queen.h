#ifndef DEF_QUEEN
#define DEF_QUEEN

#include"../piece.h"
class Queen : public Piece
{
	public:
	Queen(Colour colour);

	std::vector<Coordinate> findMoves(Coordinate const& point, bool eraseCheckMoves = true) const;

	Piece* clone() const;

	int getType() const;
};
#endif
