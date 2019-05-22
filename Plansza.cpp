#include "Plansza.h"
#include <iostream>
#include "Pozycja.h"
#include <list>
/* Konstruktor */
Plansza::Plansza()
{
	/* Logika */

	ile_bialych=12;
	ile_czarnych=12;
	int b;
	int a = b = 0;
	int c = 0;

	/*  Grafika  */
	Okno.create(VideoMode(840, 840, 32), "Warcaby");	// Utworzenie Okna
	/* Konfiguracja okna */
	Okno.setActive(true);
	Okno.setKeyRepeatEnabled(false);		// pozwalaj na to by samoczynnie powtarza³ sie wcisnienty w oknie pcicisk
	Okno.setFramerateLimit(60);				// limit klatek
	Okno.setVerticalSyncEnabled(true);		// Synchronizacja pionowa TAK/NIE(Jesli ustawimy to setFramelimit ingnorowany)
	Okno.setPosition(Vector2i(100, 100));

	/* Tworzenie szachownicy */
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			Pol_tab[i][j] = 0;
			Pole[i][j].setSize(Vector2f(100, 100));
			if ((i + j) % 2 == 0)
			{
				(Pole[i][j]).setFillColor(Color(173, 190, 166));			// POla bia³e
			}
			else
			{
				(Pole[i][j]).setFillColor(Color(40, 40, 40));				// Pola czarne
			}
			Pole[i][j].setPosition(20 + j * 100, 20 + (i * 100));
		}
	}
	/*  Ustawienie tabilicy logicznej warcabów 
		B-bia³e C-czarne .-puste pole	
		b-bia³a damka	
		c-czarna damka
	
	*/
	for (int i = 0; i < 8; i++)				//wiadomo	
	{
		for (int j = 0; j < 8; j++)			// wiadomo
		{
			if ((i + j) % 2 != 0)			// tylko dla czarnych pol szachownicy
			{
				if (i < 3)					// Dla tych na górze
				{
					Polorzenie_pionków[i][j] = 'C';
				}
				else if (i > 4)				// Dla tych na dole
				{
					Polorzenie_pionków[i][j] = 'B';
				}
				else						// Dla pol czarnych niezajetych przez pionki
				{
					Polorzenie_pionków[i][j] = '.';
				}
			}
			else							// Dla Pol bia³ych
			{
				Polorzenie_pionków[i][j] = '.';
			}
		}
	}
	/* Tworzenie pionków czarnych */
	for (int i = 0; i < 12; ++i)
	{
		tab_Pionek_1[i].set_Window(&Okno);
		tab_Pionek_1[i].set_Kolor(20, 20, 20);
	}
	/* Tworzenie pionków bia³ych */
	for (int i = 0; i < 12; ++i)
	{
		tab_Pionek_2[i].set_Window(&Okno);
		tab_Pionek_2[i].set_Kolor(235, 235, 235);
	}
	for (int i = 0; i < 8; i++)				//wiadomo	
	{
		for (int j = 0; j < 8; j++)			// wiadomo
		{
			if (Polorzenie_pionków[i][j] == 'C')	// jezeli pionek czarny
			{
				tab_Pionek_1[a].set_Pozycja(70 + j * 100, 70 + (i * 100));
				tab_Pionek_1[a].set_pozycja_x(j);
				tab_Pionek_1[a++].set_pozycja_y(i);
			}
			if (Polorzenie_pionków[i][j] == 'B')   // jezeli pionek bia³y
			{
				tab_Pionek_2[b].set_Pozycja(70 + j * 100, 70 + (i * 100));
				tab_Pionek_2[b].set_pozycja_x(j);
				tab_Pionek_2[b++].set_pozycja_y(i);
			}
		}
	}
	/* Tworzenie podswietlen dla mozliwych ruchów ruchów  */
	for (int i = 0; i < 32; ++i)
	{
		tab_Podswietlenia[i].set_Window(&Okno);
		tab_Podswietlenia[i].set_Kolor(210, 40, 40);
	}
	
	
}


/* Destruktor */
Plansza::~Plansza()
{

}
/* Funkcja do pokazywania tablicy logicznej*/
void Plansza::Poka_polozenie_pionkow()
{
	std::cout << "   a b c d e f g h\n\n";
	for (int i = 0; i < 8; i++)				//wiadomo	
	{
		std::cout << 8 - i << " ";
		for (int j = 0; j < 8; j++)			// wiadomo
		{
			std::cout << "|" << Polorzenie_pionków[i][j];
		}
		std::cout << "|" << "\n";
	}
}
/*              Metody od ruchów                      */
bool Plansza::ruch_lewy_dol(int x, int y)
{
	if (x > 0 && y < 7)
	{
		if (Polorzenie_pionków[++y][--x] == '.')
			return true;
	}
	return false;
}
bool Plansza::ruch_lewy_gora(int x, int y)
{
	if (x > 0 && y > 0)
	{
		if (Polorzenie_pionków[--y][--x] == '.')
			return true;
	}
	return false;
}
bool Plansza::ruch_prawy_dol(int x, int y)
{
	if (x <7 && y < 7)
	{
		if (Polorzenie_pionków[++y][++x] == '.')
			return true;
	}
	return false;
}
bool Plansza::ruch_prawy_gora(int x, int y)
{
	if (y > 0 && x < 7)
	{
		if (Polorzenie_pionków[--y][++x] == '.')
			return true;
	}
	return false;
}
/*     BIcia   */
bool Plansza::bicie_lewy_dol(int x, int y)
{
	char jaki_kolor_bije = Polorzenie_pionków[y][x];
	char jaki_kolor_bijemy = 'a';
	char jaki_kolor_bijemy2 = 'a';

	if (jaki_kolor_bije == 'B' || jaki_kolor_bije == 'b')
	{
		jaki_kolor_bijemy = 'C';
		jaki_kolor_bijemy2 = 'c';
	}
	if (jaki_kolor_bije == 'C' || jaki_kolor_bije == 'c')
	{
		jaki_kolor_bijemy = 'B';
		jaki_kolor_bijemy2 = 'b';
	}
	if (x > 1 && y < 6)
	{
		if ((Polorzenie_pionków[y+1][x-1] == jaki_kolor_bijemy|| (Polorzenie_pionków[y + 1][x - 1] == jaki_kolor_bijemy2)) && Polorzenie_pionków[y+2][x-2] == '.')
			return true;
	}
	return false;
}
bool Plansza::bicie_lewy_gora(int x, int y)
{
	char jaki_kolor_bije = Polorzenie_pionków[y][x];
	char jaki_kolor_bijemy = 'a';
	char jaki_kolor_bijemy2 = 'a';

	if (jaki_kolor_bije == 'B' || jaki_kolor_bije == 'b')
	{
		jaki_kolor_bijemy = 'C';
		jaki_kolor_bijemy2 = 'c';
	}
	if (jaki_kolor_bije == 'C' || jaki_kolor_bije == 'c')
	{
		jaki_kolor_bijemy = 'B';
		jaki_kolor_bijemy2 = 'b';
	}
	if (x > 1 && y > 1)
	{
		if ((Polorzenie_pionków[y-1][x-1] == jaki_kolor_bijemy || (Polorzenie_pionków[y - 1][x - 1] == jaki_kolor_bijemy2)) && Polorzenie_pionków[y - 2][x - 2] == '.')
			return true;
	}
	return false;
}
bool Plansza::bicie_prawy_dol(int x, int y)
{
	char jaki_kolor_bije = Polorzenie_pionków[y][x];
	char jaki_kolor_bijemy = 'a';
	char jaki_kolor_bijemy2 = 'a';

	if (jaki_kolor_bije == 'B' || jaki_kolor_bije == 'b')
	{
		jaki_kolor_bijemy = 'C';
		jaki_kolor_bijemy2 = 'c';
	}
	if (jaki_kolor_bije == 'C' || jaki_kolor_bije == 'c')
	{
		jaki_kolor_bijemy = 'B';
		jaki_kolor_bijemy2 = 'b';
	}
	if (x < 6 && y < 6)
	{
		if ((Polorzenie_pionków[y+1][x+1] == jaki_kolor_bijemy || Polorzenie_pionków[y + 1][x + 1] == jaki_kolor_bijemy2) && Polorzenie_pionków[y + 2][x + 2] == '.')
			return true;
	}
	return false;
}
bool Plansza::bicie_prawy_gora(int x, int y)
{
	char jaki_kolor_bije = Polorzenie_pionków[y][x];
	char jaki_kolor_bijemy = 'a';
	char jaki_kolor_bijemy2 = 'a';

	if (jaki_kolor_bije == 'B' || jaki_kolor_bije == 'b')
	{
		jaki_kolor_bijemy = 'C';
		jaki_kolor_bijemy2 = 'c';
	}
	if (jaki_kolor_bije == 'C' || jaki_kolor_bije == 'c')
	{
		jaki_kolor_bijemy = 'B';
		jaki_kolor_bijemy2 = 'b';
	}
	if (y > 1 && x < 6)
	{
		if ((Polorzenie_pionków[y-1][x+1] == jaki_kolor_bijemy || Polorzenie_pionków[y - 1][x + 1] == jaki_kolor_bijemy2) && Polorzenie_pionków[y - 2][x + 2] == '.')
			return true;
	}
	return false;
}

bool Plansza::sprawdz_bicie(Pionek *wsk,int ile)
{
	bool bicie = false;
	for (int i = 0; i < ile; ++i)									// Lece po wszystkich czarnych pionkach
	{																		// Sprawdzanie bicia
		int x = wsk[i].get_pozycja_x();
		int y = wsk[i].get_pozycja_y();
		if (bicie_prawy_dol(x, y))  bicie = true;
		if (bicie_lewy_dol(x, y))   bicie = true;
		if (bicie_lewy_gora(x, y))  bicie = true;
		if (bicie_prawy_gora(x, y)) bicie = true;
	}
	return bicie;
}
bool Plansza::mozliwe_bicie(int x, int y)
{
	bool bicie = false;
	if (bicie_prawy_dol(x, y))  bicie = true;
	if (bicie_lewy_dol(x, y))   bicie = true;
	if (bicie_lewy_gora(x, y))  bicie = true;
	if (bicie_prawy_gora(x, y)) bicie = true;
	return bicie;
}

void Plansza::minmax(bool czy_czarne,int glebokosc)
{
	std::list<Pozycja> Lista_pozycje;
	Pozycja P;
	char tab_minmax[8][8];
	for (int i = 0; i < 8; ++i)							// Kopiowanie do tablicy pomocniczej
	{
		for (int j = 0; j < 8; ++j)
		{
			tab_minmax[i][j] = Polorzenie_pionków[i][j];
		}
	}
	
	//std::cout << "Wynik: " << policz_wage(czy_czarne, tab_minmax)<<"\n";
	if (czy_czarne)
	{
		for (int i = 0; i < glebokosc; ++i)
		{
			if (sprawdz_bicie(tab_Pionek_1, ile_czarnych))
			{
				for (int k = 0; k < ile_czarnych; k++)
				{
					int x = tab_Pionek_1[k].get_pozycja_x();
					int y = tab_Pionek_1[k].get_pozycja_y();
					if (mozliwe_bicie(x, y))
					{
						if (bicie_lewy_dol(x, y))
						{

						}
						if (bicie_lewy_gora(x, y))
						{

						}
						if (bicie_prawy_dol(x, y))
						{

						}
						if (bicie_prawy_gora(x, y))
						{

						}
							
					}
				}
			}
			for (int j = 0; j < ile_czarnych; ++j)
			{
				
			}
		}
	}
	else
	{

	}

}


///////////////////////////////////////////////////////////////////////////////////
bool Plansza::mozliwe_ruchy_czarne()
{
	sf::Event e;
	bool bicie = sprawdz_bicie(tab_Pionek_1, ile_czarnych);						// Sprawdzam czy mozliwe jest bicie
	if (!bicie)
	{
		for (int i = 0; i < ile_czarnych; ++i)									// Lece po wszystkich czarnych pionkach
		{
			if (tab_Pionek_1[i].get_klikniety())								// jesli wcisniety
			{
				int x = tab_Pionek_1[i].get_pozycja_x();
				int y = tab_Pionek_1[i].get_pozycja_y();

				if (ruch_prawy_dol(x, y))										// jesli mozliwy ruch ustaw podpowiedz(czyli to ko³eczko) i dodaj do okna
				{
					tab_Podswietlenia[0].set_pozycja_x(x + 1);
					tab_Podswietlenia[0].set_pozycja_y(y + 1);
					tab_Podswietlenia[0].set_Pozycja(70 + (x + 1) * 100, 70 + ((y + 1) * 100));
					Okno.draw(tab_Podswietlenia[0].Get());
				}
				if (ruch_lewy_dol(x, y))										// jesli mozliwy ruch ustaw podpowiedz i dodaj do okna
				{
					tab_Podswietlenia[1].set_pozycja_x(x - 1);
					tab_Podswietlenia[1].set_pozycja_y(y + 1);
					tab_Podswietlenia[1].set_Pozycja(70 + (x - 1) * 100, 70 + ((y + 1) * 100));
					Okno.draw(tab_Podswietlenia[1].Get());
				}
				if (ruch_prawy_gora(x, y)&& tab_Pionek_1[i].get_damka())
				{
					tab_Podswietlenia[2].set_pozycja_x(x + 1);
					tab_Podswietlenia[2].set_pozycja_y(y - 1);
					tab_Podswietlenia[2].set_Pozycja(70 + (x + 1) * 100, 70 + ((y - 1) * 100));
					Okno.draw(tab_Podswietlenia[2].Get());
				}
				if (ruch_lewy_gora(x, y) && tab_Pionek_1[i].get_damka())
				{
					tab_Podswietlenia[3].set_pozycja_x(x - 1);
					tab_Podswietlenia[3].set_pozycja_y(y - 1);
					tab_Podswietlenia[3].set_Pozycja(70 + (x - 1) * 100, 70 + ((y - 1) * 100));
					Okno.draw(tab_Podswietlenia[3].Get());
				}

				tab_Podswietlenia[0].sprawdz_Zdarzenia(e);						// Sprawdzam czy podpowiedz jest kliknieta
				if (tab_Podswietlenia[0].get_klikniety() && ruch_prawy_dol(x, y))
				{						
					Polorzenie_pionków[y + 1][x + 1] = Polorzenie_pionków[y][x];
					Polorzenie_pionków[y][x] = '.';
					tab_Pionek_1[i].set_klikniety(0);
					if (y + 1 == 7)												// Jezeli dojdzie do konca
					{
						Polorzenie_pionków[y + 1][x + 1] = 'c';					// Ustaw tam damke
					}
					Poka_polozenie_pionkow();
					return true;
				}
				tab_Podswietlenia[1].sprawdz_Zdarzenia(e);						// Sprawdzam czy podpowiedz jest kliknieta
				if (tab_Podswietlenia[1].get_klikniety() && ruch_lewy_dol(x, y))
				{
					Polorzenie_pionków[y + 1][x - 1] = Polorzenie_pionków[y][x];
					Polorzenie_pionków[y][x] = '.';
					tab_Pionek_1[i].set_klikniety(0);
					if (y + 1 == 7)
					{
						Polorzenie_pionków[y + 1][x - 1] = 'c';
					}
					Poka_polozenie_pionkow();
					return true;
				}
				tab_Podswietlenia[2].sprawdz_Zdarzenia(e);
				if (tab_Podswietlenia[2].get_klikniety() && ruch_prawy_gora(x, y))
				{
					Polorzenie_pionków[y - 1][x + 1] = Polorzenie_pionków[y][x];
					Polorzenie_pionków[y][x] = '.';
					tab_Pionek_1[i].set_klikniety(0);
					Poka_polozenie_pionkow();
					return true;
				}
				tab_Podswietlenia[3].sprawdz_Zdarzenia(e);
				if (tab_Podswietlenia[3].get_klikniety() && ruch_lewy_gora(x, y))
				{
					Polorzenie_pionków[y - 1][x - 1] = Polorzenie_pionków[y][x];
					Polorzenie_pionków[y][x] = '.';
					tab_Pionek_1[i].set_klikniety(0);
					Poka_polozenie_pionkow();
					return true;
				}
			}

		}
	}
	else																	// Kiedy jest bicie
	{
		
		for (int i = 0; i < ile_czarnych; ++i)									// Lece po wszystkich czarnych pionkach
		{
			if (tab_Pionek_1[i].get_klikniety())								// jesli wcisniety
			{
				int x = tab_Pionek_1[i].get_pozycja_x();
				int y = tab_Pionek_1[i].get_pozycja_y();
				if (bicie_prawy_dol(x, y))										// jesli dany pionek ma okreslone bicie to ustaw podswietlenie
				{
					tab_Podswietlenia[0].set_pozycja_x(x + 2);
					tab_Podswietlenia[0].set_pozycja_y(y + 2);
					tab_Podswietlenia[0].set_Pozycja(70 + (x + 2) * 100, 70 + ((y + 2) * 100));
					Okno.draw(tab_Podswietlenia[0].Get());
				}
				if (bicie_lewy_dol(x, y))
				{
					tab_Podswietlenia[1].set_pozycja_x(x - 2);
					tab_Podswietlenia[1].set_pozycja_y(y + 2);
					tab_Podswietlenia[1].set_Pozycja(70 + (x - 2) * 100, 70 + ((y + 2) * 100));
					Okno.draw(tab_Podswietlenia[1].Get());
				}
				if (bicie_lewy_gora(x, y))
				{
					tab_Podswietlenia[3].set_pozycja_x(x - 2);
					tab_Podswietlenia[3].set_pozycja_y(y - 2);
					tab_Podswietlenia[3].set_Pozycja(70 + (x - 2) * 100, 70 + ((y - 2) * 100));
					Okno.draw(tab_Podswietlenia[3].Get());
				}
				if (bicie_prawy_gora(x, y))
				{
					tab_Podswietlenia[2].set_pozycja_x(x + 2);
					tab_Podswietlenia[2].set_pozycja_y(y - 2);
					tab_Podswietlenia[2].set_Pozycja(70 + (x + 2) * 100, 70 + ((y - 2) * 100));
					Okno.draw(tab_Podswietlenia[2].Get());
				}
				tab_Podswietlenia[0].sprawdz_Zdarzenia(e);						// Sprawdzam czy podpowiedz jest kliknieta
				if (tab_Podswietlenia[0].get_klikniety() && bicie_prawy_dol(x, y))
				{							// wykonanie ruchu
					Polorzenie_pionków[y + 1][x + 1] = '.';
					Polorzenie_pionków[y + 2][x + 2] = Polorzenie_pionków[y][x];
					Polorzenie_pionków[y][x] = '.';
					tab_Pionek_1[i].set_klikniety(0);
					if (y + 2 == 7)
					{
						Polorzenie_pionków[y + 2][x + 2] = 'c';
					}
					Poka_polozenie_pionkow();
					ile_bialych--;
					return !mozliwe_bicie(x+2,y+2);
				}
				tab_Podswietlenia[1].sprawdz_Zdarzenia(e);						// Sprawdzam czy podpowiedz jest kliknieta
				if (tab_Podswietlenia[1].get_klikniety() && bicie_lewy_dol(x, y))
				{								// wykonanie ruchu
					Polorzenie_pionków[y + 1][x - 1] = '.';
					Polorzenie_pionków[y + 2][x - 2] = Polorzenie_pionków[y][x];
					Polorzenie_pionków[y][x] = '.';
					tab_Pionek_1[i].set_klikniety(0);
					Poka_polozenie_pionkow();        
					if (y + 2 == 7)
					{
						Polorzenie_pionków[y + 2][x - 2] = 'c';
					}
					ile_bialych--;
					return !mozliwe_bicie(x-2, y+2);
				}
				tab_Podswietlenia[2].sprawdz_Zdarzenia(e);						// Sprawdzam czy podpowiedz jest kliknieta
				if (tab_Podswietlenia[2].get_klikniety() && bicie_prawy_gora(x, y))
				{
					Polorzenie_pionków[y - 1][x + 1] = '.';
					Polorzenie_pionków[y - 2][x + 2] = Polorzenie_pionków[y][x];
					Polorzenie_pionków[y][x] = '.';
					tab_Pionek_1[i].set_klikniety(0);
					Poka_polozenie_pionkow();
					ile_bialych--;
					return !mozliwe_bicie(x+2, y-2);
				}
				tab_Podswietlenia[3].sprawdz_Zdarzenia(e);						// Sprawdzam czy podpowiedz jest kliknieta
				if (tab_Podswietlenia[3].get_klikniety() && bicie_lewy_gora(x, y))
				{
					Polorzenie_pionków[y - 1][x - 1] = '.';
					Polorzenie_pionków[y - 2][x - 2] = Polorzenie_pionków[y][x] ;
					Polorzenie_pionków[y][x] = '.';
					tab_Pionek_1[i].set_klikniety(0);
					Poka_polozenie_pionkow();
					ile_bialych--;
					return !mozliwe_bicie(x-2, y-2);
				}


			}
		}
	}
	return false;
}
bool Plansza::mozliwe_ruchy_biale()
{ 
	sf::Event e;
	bool bicie = sprawdz_bicie(tab_Pionek_2, ile_bialych);
	if (!bicie)																		// Jezeli nie wykryto bicia 
	{
		for (int i = 0; i < ile_bialych; ++i)										// lec po wszystkich bialych
		{
			if (tab_Pionek_2[i].get_klikniety())									// jezeli klikniety wykonuj rucchy
			{
				int x = tab_Pionek_2[i].get_pozycja_x();
				int y = tab_Pionek_2[i].get_pozycja_y();
																					
				if (ruch_prawy_gora(x, y))
				{
					tab_Podswietlenia[2].set_pozycja_x(x + 1);
					tab_Podswietlenia[2].set_pozycja_y(y - 1);
					tab_Podswietlenia[2].set_Pozycja(70 + (x + 1) * 100, 70 + ((y - 1) * 100));
					Okno.draw(tab_Podswietlenia[2].Get());
				}
				if (ruch_lewy_gora(x, y))
				{
					tab_Podswietlenia[3].set_pozycja_x(x - 1);
					tab_Podswietlenia[3].set_pozycja_y(y - 1);
					tab_Podswietlenia[3].set_Pozycja(70 + (x - 1) * 100, 70 + ((y - 1) * 100));
					Okno.draw(tab_Podswietlenia[3].Get());
				}
				if (ruch_prawy_dol(x, y)&&tab_Pionek_2[i].get_damka())										// jesli mozliwy ruch ustaw podpowiedz(czyli to ko³eczko) i dodaj do okna
				{
					tab_Podswietlenia[0].set_pozycja_x(x + 1);
					tab_Podswietlenia[0].set_pozycja_y(y + 1);
					tab_Podswietlenia[0].set_Pozycja(70 + (x + 1) * 100, 70 + ((y + 1) * 100));
					Okno.draw(tab_Podswietlenia[0].Get());
				}
				if (ruch_lewy_dol(x, y)&&tab_Pionek_2[i].get_damka())										// jesli mozliwy ruch ustaw podpowiedz i dodaj do okna
				{
					tab_Podswietlenia[1].set_pozycja_x(x - 1);
					tab_Podswietlenia[1].set_pozycja_y(y + 1);
					tab_Podswietlenia[1].set_Pozycja(70 + (x - 1) * 100, 70 + ((y + 1) * 100));
					Okno.draw(tab_Podswietlenia[1].Get());
				}
				/////////////////////////////////////////////////////////////////////////////////////
				tab_Podswietlenia[2].sprawdz_Zdarzenia(e);
				if (tab_Podswietlenia[2].get_klikniety() && ruch_prawy_gora(x, y))
				{
					Polorzenie_pionków[y - 1][x + 1] = Polorzenie_pionków[y][x];
					Polorzenie_pionków[y][x] = '.';
					tab_Pionek_2[i].set_klikniety(0);
					if (y - 1 == 0)												// Jezeli dojdzie do konca
					{
						Polorzenie_pionków[y - 1][x + 1] = 'b';					// Ustaw tam damke
					}
					Poka_polozenie_pionkow();
					return true;
				}
				tab_Podswietlenia[3].sprawdz_Zdarzenia(e);
				if (tab_Podswietlenia[3].get_klikniety() && ruch_lewy_gora(x, y))
				{
					Polorzenie_pionków[y - 1][x - 1] = Polorzenie_pionków[y][x];
					Polorzenie_pionków[y][x] = '.';
					tab_Pionek_2[i].set_klikniety(0);
					if (y - 1 == 0)												// Jezeli dojdzie do konca
					{
						Polorzenie_pionków[y - 1][x - 1] = 'b';					// Ustaw tam damke
					}
					Poka_polozenie_pionkow();
					return true;
				}
				tab_Podswietlenia[0].sprawdz_Zdarzenia(e);						// Sprawdzam czy podpowiedz jest kliknieta
				if (tab_Podswietlenia[0].get_klikniety() && ruch_prawy_dol(x, y))
				{
					Polorzenie_pionków[y + 1][x + 1] = Polorzenie_pionków[y][x];
					Polorzenie_pionków[y][x] = '.';
					tab_Pionek_2[i].set_klikniety(0);
					Poka_polozenie_pionkow();
					return true;
				}
				tab_Podswietlenia[1].sprawdz_Zdarzenia(e);						// Sprawdzam czy podpowiedz jest kliknieta
				if (tab_Podswietlenia[1].get_klikniety() && ruch_lewy_dol(x, y))
				{
					Polorzenie_pionków[y + 1][x - 1] = Polorzenie_pionków[y][x];
					Polorzenie_pionków[y][x] = '.';
					tab_Pionek_2[i].set_klikniety(0);
					Poka_polozenie_pionkow();
					return true;
				}

			}
		}
	}
	else                                                                                  // Jezeli jest bicie
	{
		for (int i = 0; i < ile_bialych; ++i)									// Lece po wszystkich czarnych pionkach
		{
			if (tab_Pionek_2[i].get_klikniety())								// jesli wcisniety
			{
				int x = tab_Pionek_2[i].get_pozycja_x();
				int y = tab_Pionek_2[i].get_pozycja_y();
				if (bicie_prawy_dol(x, y))										// jesli dany pionek ma okreslone bicie to ustaw podswietlenie
				{
					tab_Podswietlenia[0].set_pozycja_x(x + 2);
					tab_Podswietlenia[0].set_pozycja_y(y + 2);
					tab_Podswietlenia[0].set_Pozycja(70 + (x + 2) * 100, 70 + ((y + 2) * 100));
					Okno.draw(tab_Podswietlenia[0].Get());
				}
				if (bicie_lewy_dol(x, y))
				{
					tab_Podswietlenia[1].set_pozycja_x(x - 2);
					tab_Podswietlenia[1].set_pozycja_y(y + 2);
					tab_Podswietlenia[1].set_Pozycja(70 + (x - 2) * 100, 70 + ((y + 2) * 100));
					Okno.draw(tab_Podswietlenia[1].Get());
				}
				if (bicie_lewy_gora(x, y))
				{
					tab_Podswietlenia[3].set_pozycja_x(x - 2);
					tab_Podswietlenia[3].set_pozycja_y(y - 2);
					tab_Podswietlenia[3].set_Pozycja(70 + (x - 2) * 100, 70 + ((y - 2) * 100));
					Okno.draw(tab_Podswietlenia[3].Get());
				}
				if (bicie_prawy_gora(x, y))
				{
					tab_Podswietlenia[2].set_pozycja_x(x + 2);
					tab_Podswietlenia[2].set_pozycja_y(y - 2);
					tab_Podswietlenia[2].set_Pozycja(70 + (x + 2) * 100, 70 + ((y - 2) * 100));
					Okno.draw(tab_Podswietlenia[2].Get());
				}
				//////////////////////////////////////////////////////////////////////////////////////////////////////////
				tab_Podswietlenia[0].sprawdz_Zdarzenia(e);						// Sprawdzam czy podpowiedz jest kliknieta
				if (tab_Podswietlenia[0].get_klikniety() && bicie_prawy_dol(x, y))
				{
												// wykonanie ruchu
					Polorzenie_pionków[y + 1][x + 1] = '.';
					Polorzenie_pionków[y + 2][x + 2] = Polorzenie_pionków[y][x];
					Polorzenie_pionków[y][x] = '.';
					tab_Pionek_2[i].set_klikniety(0);
					Poka_polozenie_pionkow();
					ile_czarnych--;
					return !mozliwe_bicie(x+2, y+2);
				}
				tab_Podswietlenia[1].sprawdz_Zdarzenia(e);						// Sprawdzam czy podpowiedz jest kliknieta
				if (tab_Podswietlenia[1].get_klikniety() && bicie_lewy_dol(x, y))
				{
												// wykonanie ruchu
					Polorzenie_pionków[y + 1][x - 1] = '.';
					Polorzenie_pionków[y + 2][x - 2] = Polorzenie_pionków[y][x];
					Polorzenie_pionków[y][x] = '.';
					tab_Pionek_2[i].set_klikniety(0);
					Poka_polozenie_pionkow();
					ile_czarnych--;
					return !mozliwe_bicie(x-2, y+2);
				}
				tab_Podswietlenia[2].sprawdz_Zdarzenia(e);						// Sprawdzam czy podpowiedz jest kliknieta
				if (tab_Podswietlenia[2].get_klikniety() && bicie_prawy_gora(x, y))
				{
																				// wykonanie ruchu
					Polorzenie_pionków[y - 1][x + 1] = '.';
					Polorzenie_pionków[y - 2][x + 2] = Polorzenie_pionków[y][x];
					Polorzenie_pionków[y][x] = '.';
					tab_Pionek_2[i].set_klikniety(0);
					ile_czarnych--;
					Poka_polozenie_pionkow();
					if (y - 2 == 0)												// Jezeli dojdzie do konca
					{
						Polorzenie_pionków[y - 2][x + 2] = 'b';					// Ustaw tam damke
					}
					return !mozliwe_bicie(x+2, y-2);
				}
				tab_Podswietlenia[3].sprawdz_Zdarzenia(e);						// Sprawdzam czy podpowiedz jest kliknieta
				if (tab_Podswietlenia[3].get_klikniety() && bicie_lewy_gora(x, y))
				{																// wykonanie ruchu
					Polorzenie_pionków[y - 1][x - 1] = '.';
					Polorzenie_pionków[y - 2][x - 2] = Polorzenie_pionków[y][x];
					Polorzenie_pionków[y][x] = '.';
					tab_Pionek_2[i].set_klikniety(0);
					ile_czarnych--;
					if (y -2 == 0)												// Jezeli dojdzie do konca
					{
						Polorzenie_pionków[y - 2][x -2] = 'b';					// Ustaw tam damke
					}
					Poka_polozenie_pionkow();
					return !mozliwe_bicie(x-2, y-2);
				}
			}
		}
	}
	return false;
}


void Plansza::Wysteruj_z_logiki()
{
	int b = 0;
	int a = 0;
	for (int i = 0; i < 8; i++)				//wiadomo	
	{
		for (int j = 0; j < 8; j++)			// wiadomo
		{
			if (Polorzenie_pionków[i][j] == 'C')	// jezeli pionek czarny
			{
				tab_Pionek_1[a].set_Pozycja(70 + j * 100, 70 + (i * 100));
				tab_Pionek_1[a].set_pozycja_x(j);
				tab_Pionek_1[a].set_damka(0);
				tab_Pionek_1[a++].set_pozycja_y(i);
			}
			if (Polorzenie_pionków[i][j] == 'B')   // jezeli pionek bia³y
			{
				tab_Pionek_2[b].set_Pozycja(70 + j * 100, 70 + (i * 100));
				tab_Pionek_1[b].set_damka(0);
				tab_Pionek_2[b].set_pozycja_x(j);
				tab_Pionek_2[b++].set_pozycja_y(i);
			}
			if (Polorzenie_pionków[i][j] == 'c')	// jezeli pionek czarny
			{
				tab_Pionek_1[a].set_Pozycja(70 + j * 100, 70 + (i * 100));
				tab_Pionek_1[a].set_pozycja_x(j);
				tab_Pionek_1[a].set_damka(1);
				tab_Pionek_1[a++].set_pozycja_y(i);
			}
			if (Polorzenie_pionków[i][j] == 'b')   // jezeli pionek bia³y
			{
				tab_Pionek_2[b].set_Pozycja(70 + j * 100, 70 + (i * 100));
				tab_Pionek_2[b].set_damka(1);
				tab_Pionek_2[b].set_pozycja_x(j);
				tab_Pionek_2[b++].set_pozycja_y(i);
			}

		}
	}
}








void Plansza::Show()
{
	bool ktopierwszy = 1;
	Poka_polozenie_pionkow();
	sf::Event e;
	int a = 0, b = 0, c = 0;
	while (Okno.isOpen())
	{
		Okno.clear(Color(a, b, c));	
		while (Okno.pollEvent(e))			// koolejka wydarzen, ktore sie zadzia³a³y od ostatniej klatki
		{
			if (e.type == sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
				Okno.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			{
				
			}		
		}
		/* Dodawanie do Okna Pol szachownicy */
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				Okno.draw(Pole[i][j]);
			}	
		}
		if (ktopierwszy)
		{
			if (mozliwe_ruchy_biale())
			{
			
				 ktopierwszy = 0;
				 minmax(0, 1);
			}
			Wysteruj_z_logiki();
		}
		else
		{
			if (mozliwe_ruchy_czarne())
			{
				 ktopierwszy = 1;
				 minmax(1, 1);
			}
			Wysteruj_z_logiki();
		}
		/* Dodawanie do Okna Pionków */
		for (int i = 0; i < ile_czarnych; ++i)
		{
			Okno.draw(tab_Pionek_1[i].Get());	//Czarne
		}
		for (int i = 0; i < ile_bialych; ++i)
		{
		Okno.draw(tab_Pionek_2[i].Get());	//Bia³e
		}	
		/* Sprawdzanie zdarzen dla Pionków*/
		for (int i = 0; i < ile_czarnych; ++i)
		{
			tab_Pionek_1[i].sprawdz_Zdarzenia(e);
		}
		for (int i = 0; i < ile_bialych; ++i)
		{
			tab_Pionek_2[i].sprawdz_Zdarzenia(e);
		}	
		Okno.display();	//Wiadomo	
	}
}