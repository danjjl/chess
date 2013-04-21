#include "coordinate.h"
//Public
Coordinate::Coordinate()
{
	m_x = 0;
	m_y = 0;
}

Coordinate::Coordinate(int x, int y)
{
	m_x = x;
	m_y = y;
}


//Read value
int Coordinate::x() const
{
	return m_x;
}

int Coordinate::y() const
{
	return m_y;
}


//Set Value
void Coordinate::x(int x)
{
	m_x = x;
}

void Coordinate::y(int y)
{
	m_y = y;
}


//Increment value
void Coordinate::addX(int x)
{
	m_x += x;
}

void Coordinate::addY(int y)
{
	m_y += y;
}



bool operator==(Coordinate const& point1, Coordinate const& point2)
{
	return ((point1.x() == point2.x()) && (point1.y() == point2.y()));
}
