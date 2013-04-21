#ifndef DEF_COORDINATE
#define DEF_COORDINATE

class Coordinate
{
	public:
	Coordinate();
	Coordinate(int x, int y);

	int x() const;//read
	int y() const;

	void x(int x);//Set value
	void y(int y);

	void addX(int x = 1);//increment
	void addY(int y = 1);

	private:
	int m_x;
	int m_y;
};
bool operator==(Coordinate const& point1, Coordinate const& point2);
#endif
