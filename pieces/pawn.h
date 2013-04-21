#ifndef DEF_PAWN
#define DEF_PAWN

#include"../piece.h"
class Pawn : public Piece
{
	public:
	Pawn(Colour colour);

	std::vector<Coordinate> findMoves(Coordinate const& point, bool eraseCheckMoves = true) const;

	void move(Coordinate const& from, Coordinate const& to);

	Piece* clone() const;

	int getType() const;


	private:
	void normalMove(int side, std::vector<Coordinate> &points, Coordinate point) const;
	void killingMove(int side, std::vector<Coordinate> &points, Coordinate point) const;
	void doubleMove(int side, std::vector<Coordinate> &points, Coordinate point) const;
	void coupEnPassant(int cote, int side, int passant, std::vector<Coordinate> &points, Coordinate point) const;

	void specialMoves(Coordinate const& from, Coordinate const& to, int passant);
};
#endif
