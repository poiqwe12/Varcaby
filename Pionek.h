#include <SFML/Graphics.hpp>

using namespace sf;

class Pionek
{
	RenderWindow *Okienko;		// Musi trzymac okno na ktorym sie wyswietla
	Sprite S;					// Moze wykorzystam	
	CircleShape Kolko;			// wiadomo
	Color C;
	bool najechany;
	bool klikniety;
	int pozycja_x, pozycja_y;
public:
	Pionek();
	void set_pozycja_x(int p);
	void set_pozycja_y(int p);
	int get_pozycja_x();
	int get_pozycja_y();
	bool get_najechany();
	bool get_klikniety();
	void set_Window(RenderWindow *R1) {
		Okienko = R1;
	}
	void set_Pozycja(float x,float y);
	void set_Kolor(int r,int g,int b);
	void set_Rozmiar(float radius);
	void set_klikniety(bool a);
	void sprawdz_Zdarzenia(Event &e);
	CircleShape& Get()
	{
		return Kolko;
	}
};


/*
		std::cout << "-------------Bia³e-----------------------------------\n";
		std::cout << "x:  " << x << "  y:  " << y << "\n";
		std::cout << "R_prawy dol:  " << ruch_prawy_dol(x, y) << "\n";
		std::cout << "R_lewy dol:   " << ruch_lewy_dol(x, y) << "\n";
		std::cout << "R_lewy gora:  " << ruch_lewy_gora(x, y) << "\n";
		std::cout << "R_prawy gora: " << ruch_prawy_gora(x, y) << "\n";
		std::cout << "-----------------------------------------------------\n";
		tab_Podswietlenia[2].sprawdz_Zdarzenia(e);
if (tab_Podswietlenia[2].get_najechany() && sf::Mouse::isButtonPressed(sf::Mouse::Left))
{
	Polorzenie_pionków[y][x] = '.';
	Polorzenie_pionków[y - 1][x + 1] = 'B';

	return false;
}
tab_Podswietlenia[3].sprawdz_Zdarzenia(e);
if (tab_Podswietlenia[3].get_najechany() && sf::Mouse::isButtonPressed(sf::Mouse::Left))
{
	Polorzenie_pionków[y][x] = '.';
	Polorzenie_pionków[y - 1][x - 1] = 'B';
	return false;
}
Poka_polozenie_pionkow();		*/