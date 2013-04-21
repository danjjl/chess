#ifndef DEF_COLOUR
#define DEF_COLOUR

class Colour
{
	public:
	bool get() const;
	void invert();

	protected:
	bool m_isBlack;//0 white; 1 black
};

bool operator==(Colour const& colour1, Colour const& colour2);
bool operator!=(Colour const& colour1, Colour const& colour2);
Colour operator~(Colour const& colour);

class White : public Colour
{
	public:
	White();
};
class Black : public Colour
{
	public:
	Black();
};
#endif
