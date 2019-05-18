#include <SFML/Graphics.hpp>
#include "Pionek.h"
#include "Podswietlenie.h"
using namespace sf;

class Plansza
{
	RenderWindow Okno;
	RectangleShape Pole[8][8];			// Czarno bia³e pola szachownicy
	char Polorzenie_pionków[8][8];		// tablica logiczna	
	bool Pol_tab[8][8];					// tablica logiczna do podswietlen
	Pionek tab_Pionek_1[12];			// Pionki czarne
	Pionek tab_Pionek_2[12];			// Pionki bia³e
	Podswietlenie tab_Podswietlenia[32];		// Podswietlenia prawid³owych ruchów
	int ile_bialych;
	int ile_czarnych;
	
public:
	Plansza();
	~Plansza();
	void Show();
	void Poka_polozenie_pionkow();
	//////////////////////////////
	bool ruch_lewy_dol(int x, int y);
	bool ruch_lewy_gora(int x, int y);
	bool ruch_prawy_dol(int x, int y);
	bool ruch_prawy_gora(int x, int y);
	///////////////////////////////
	bool bicie_lewy_dol(int x, int y);
	bool bicie_lewy_gora(int x, int y);
	bool bicie_prawy_dol(int x, int y);
	bool bicie_prawy_gora(int x, int y);
	////////////////////////////////
	bool mozliwe_ruchy_czarne();
	bool mozliwe_ruchy_biale();
	////////////////////////////////
	bool sprawdz_bicie(Pionek *wsk,int ile);
	void Wysteruj_z_logiki();
	bool mozliwe_bicie();
};

