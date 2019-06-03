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
	////////////////////////////////
	//MIN MAX
	int tab_wagi_pionowe[8];
	int tab_wagi_poziome[8];
	int waga_bicie, waga_damka;
	bool multi;
public:
	Plansza();
	~Plansza();
	void Show();
	void Poka_polozenie_pionkow();
	void Poka_tablice(char tab[8][8]);
	////// Metody sprawdzajace/////////
	bool ruch_lewy_dol(char tab[8][8],int x, int y);
	bool ruch_lewy_gora(char tab[8][8], int x, int y);
	bool ruch_prawy_dol(char tab[8][8],int x, int y);
	bool ruch_prawy_gora (char tab[8][8],int x, int y);
	///////////////////////////////
	bool bicie_lewy_dol(char tab[8][8],int x, int y);
	bool bicie_lewy_gora(char tab[8][8],int x, int y);
	bool bicie_prawy_dol(char tab[8][8],int x, int y);
	bool bicie_prawy_gora(char tab[8][8],int x, int y);
	//////  Metody wykonujace  ///////////
	void wykonaj_bicie_lewy_dol(char tab[8][8], int x, int y);
	void wykonaj_bicie_prawy_dol(char tab[8][8], int x, int y);
	void wykonaj_bicie_lewy_gora(char tab[8][8], int x, int y);
	void wykonaj_bicie_prawy_gora(char tab[8][8], int x, int y);
	////////////////////////////////
	void wykonaj_ruch_lewy_dol(char tab[8][8], int x, int y);
	void wykonaj_ruch_prawy_dol(char tab[8][8], int x, int y);
	void wykonaj_ruch_lewy_gora(char tab[8][8], int x, int y);
	void wykonaj_ruch_prawy_gora(char tab[8][8], int x, int y);
	//////////Metody do grania multiplayer///////////
	bool mozliwe_ruchy_czarne();
	bool mozliwe_ruchy_biale();
	///////////Inne metody////////
	bool sprawdz_bicie(Pionek *wsk,int ile);
	bool sprawdz_bicie(char tab[8][8], bool czy_czarne);
	
	void Wysteruj_z_logiki();
	int mozliwe_bicie(char tab[8][8],int x,int y);
	/////////////////////////////////
	bool minmax(bool czy_czarne,int glebokosc);
	int policz_wage(bool czy_czarne, char tab[8][8]);
	void kopiowanie_tablicy(char tab[8][8], char tab2[8][8]);
	/////////////////////////////////////

	



};

