#include "colour.h"
//Public
bool Colour::get() const
{
	return m_isBlack;
}

void Colour::invert()
{
	if(m_isBlack)
		m_isBlack = false;
	else
		m_isBlack = true;
}



bool operator==(Colour const& colour1, Colour const& colour2)
{
	return (colour1.get() == colour2.get());
}

bool operator!=(Colour const& colour1, Colour const& colour2)
{
	return (colour1.get() != colour2.get());
}

Colour operator~(Colour const& colour)
{
	if(colour.get())
		return White();
	else
		return Black();
}



White::White()
{
	m_isBlack = false;
}

Black::Black()
{
	m_isBlack = true;
}
