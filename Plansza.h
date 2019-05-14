#include <SFML/Graphics.hpp>

using namespace sf;

class Plansza
{
	RenderWindow Okno;
	RectangleShape Pole[8][8];
	Text  tekst[16];
	
public:
	Plansza();
	~Plansza();
	void Show();
};

