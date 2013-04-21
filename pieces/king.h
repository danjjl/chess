#ifndef DEF_KING
#define DEF_KING

#include"../piece.h"
class King : public Piece
{
	public:
	King(Colour colour);

	std::vector<Coordinate> findMoves(Coordinate const& point, bool eraseCheckMoves = true) const;

	void move(Coordinate const& from, Coordinate const& to);

	Piece* clone() const;

	int getType() const;

	private:
	void rock(int side, std::vector<Coordinate> &points, Coordinate const& point) const;
	bool rockNoDanger(int side, Coordinate const& point) const;
};
#endif
