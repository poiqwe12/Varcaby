#include <SFML/Graphics.hpp>

using namespace sf;

class Podswietlenie
{
	RenderWindow *Okienko;		// Musi trzymac okno na ktorym sie wyswietla
	Sprite S;					// Moze wykorzystam	
	CircleShape Kolko;			// wiadomo
	Color C;
	bool najechany;
	bool klikniety;
	int pozycja_x, pozycja_y;
public:
	Podswietlenie();
	void set_pozycja_x(int p);
	void set_pozycja_y(int p);
	int get_pozycja_x();
	int get_pozycja_y();
	bool get_najechany();
	bool get_klikniety();
	void set_Window(RenderWindow *R1) {
		Okienko = R1;
	}
	void set_Pozycja(float x, float y);
	void set_Kolor(int r, int g, int b);
	void set_Rozmiar(float radius);
	void sprawdz_Zdarzenia(Event &e);
	CircleShape& Get()
	{
		return Kolko;
	}
};