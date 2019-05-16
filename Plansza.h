#include <SFML/Graphics.hpp>
#include "Pionek.h"

using namespace sf;

class Plansza
{
	RenderWindow Okno;
	RectangleShape Pole[8][8];			// Czarno bia³e pola szachownicy
	char Polorzenie_pionków[8][8];		// tablica logiczna		
	Pionek tab_Pionek_1[12];
	Pionek tab_Pionek_2[12];
	int ile_bialych;
	int ile_czarnych;
	
public:
	Plansza();
	~Plansza();
	void Show();
	void Poka_polozenie_pionkow();
};

