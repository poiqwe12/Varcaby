#include "Plansza.h"
#include <iostream>
/* Konstruktor */
Plansza::Plansza()
{
	int a=ile_bialych=12;
	int b=ile_czarnych=12;
	int c = 0;

	Okno.create(VideoMode(840, 840, 32), "Warcaby");	// Utworzenie Okna
	/* Konfiguracja okna */
	Okno.setActive(true);
	Okno.setKeyRepeatEnabled(false);		// pozwalaj na to by samoczynnie powtarza� sie wcisnienty w oknie pcicisk
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
				(Pole[i][j]).setFillColor(Color(173, 190, 166));
			}
			else
			{
				(Pole[i][j]).setFillColor(Color(40, 40, 40));
			}
			Pole[i][j].setPosition(20 + j * 100, 20 + (i * 100));
		}
	}
	/* Ustawienie tabilicy logicznej warcab�w  B-bia�e C-czarne .-puste pole */
	for (int i = 0; i < 8; i++)				//wiadomo	
	{
		for (int j = 0; j < 8; j++)			// wiadomo
		{
			if ((i + j) % 2 != 0)			// tylko dla czarnych pol szachownicy
			{
				if (i < 3)					// Dla tych na g�rze
				{
					Polorzenie_pionk�w[i][j] = 'C';
				}
				else if (i > 4)				// Dla tych na dole
				{
					Polorzenie_pionk�w[i][j] = 'B';
				}
				else						// Dla pol czarnych niezajetych przez pionki
				{
					Polorzenie_pionk�w[i][j] = '.';
				}
			}
			else							// Dla Pol bia�ych
			{
				Polorzenie_pionk�w[i][j] = '.';
			}
		}
	}
	/* Tworzenie pionk�w czarnych */
	for (int i = 0; i < 12; ++i)
	{
		tab_Pionek_1[i].set_Window(&Okno);
		tab_Pionek_1[i].set_Kolor(20, 20, 20);
	}
	/* Tworzenie pionk�w bia�ych */
	for (int i = 0; i < 12; ++i)
	{
		tab_Pionek_2[i].set_Window(&Okno);
		tab_Pionek_2[i].set_Kolor(235, 235, 235);
	}
	for (int i = 0; i < 8; i++)				//wiadomo	
	{
		for (int j = 0; j < 8; j++)			// wiadomo
		{
			if (Polorzenie_pionk�w[i][j] == 'C')	// jezeli pionek czarny
			{
				tab_Pionek_1[--a].set_Pozycja(70 + j * 100, 70 + (i * 100));
				tab_Pionek_1[a].set_pozycja_x(j);
				tab_Pionek_1[a].set_pozycja_y(i);
			}
			if (Polorzenie_pionk�w[i][j] == 'B')   // jezeli pionek bia�y
			{
				tab_Pionek_2[--b].set_Pozycja(70 + j * 100, 70 + (i * 100));
				tab_Pionek_2[b].set_pozycja_x(j);
				tab_Pionek_2[b].set_pozycja_y(i);
			}
		}
	}
	/* Tworzenie podswietlen dla mozliwych ruch�w ruch�w  */
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
			std::cout << "|" << Polorzenie_pionk�w[i][j];
		}
		std::cout << "|" << "\n";
	}
}
/*              Metody od ruch�w                      */
bool Plansza::ruch_lewy_dol(int x, int y)
{
	if (x > 0 && y < 7)
	{
		if (Polorzenie_pionk�w[++y][--x] == '.')
			return true;
	}
	return false;
}
bool Plansza::ruch_lewy_gora(int x, int y)
{
	if (x > 0 && y > 0)
	{
		if (Polorzenie_pionk�w[--y][--x] == '.')
			return true;
	}
	return false;
}
bool Plansza::ruch_prawy_dol(int x, int y)
{
	if (x <7 && y < 7)
	{
		if (Polorzenie_pionk�w[++y][++x] == '.')
			return true;
	}
	return false;
}
bool Plansza::ruch_prawy_gora(int x, int y)
{
	if (y > 0 && x < 7)
	{
		if (Polorzenie_pionk�w[--y][++x] == '.')
			return true;
	}
	return false;
}
/*     BIcia   */
bool Plansza::bicie_lewy_dol(int x, int y)
{
	char jaki_kolor_bije = Polorzenie_pionk�w[y][x];
	char jaki_kolor_bijemy;

	if (jaki_kolor_bije == 'B')
		jaki_kolor_bijemy = 'C';
	if(jaki_kolor_bije=='C')
		jaki_kolor_bijemy = 'B';

	if (x > 1 && y < 6)
	{
		if (Polorzenie_pionk�w[y+1][x-1] == jaki_kolor_bijemy && Polorzenie_pionk�w[y+2][x-2] == '.')
			return true;
	}
	return false;
}
bool Plansza::bicie_lewy_gora(int x, int y)
{
	char jaki_kolor_bije = Polorzenie_pionk�w[y][x];
	char jaki_kolor_bijemy;

	if (jaki_kolor_bije == 'B')
		jaki_kolor_bijemy = 'C';
	if (jaki_kolor_bije == 'C')
		jaki_kolor_bijemy = 'B';
	if (x > 1 && y > 1)
	{
		if (Polorzenie_pionk�w[y-1][x-1] == jaki_kolor_bijemy && Polorzenie_pionk�w[y - 2][x - 2] == '.')
			return true;
	}
	return false;
}
bool Plansza::bicie_prawy_dol(int x, int y)
{
	char jaki_kolor_bije = Polorzenie_pionk�w[y][x];
	char jaki_kolor_bijemy;

	if (jaki_kolor_bije == 'B')
		jaki_kolor_bijemy = 'C';
	if (jaki_kolor_bije == 'C')
		jaki_kolor_bijemy = 'B';
	if (x < 6 && y < 6)
	{
		if (Polorzenie_pionk�w[y+1][x+1] == jaki_kolor_bijemy && Polorzenie_pionk�w[y + 2][x + 2] == '.')
			return true;
	}
	return false;
}
bool Plansza::bicie_prawy_gora(int x, int y)
{char jaki_kolor_bije = Polorzenie_pionk�w[y][x];
	char jaki_kolor_bijemy;

	if (jaki_kolor_bije == 'B')
		jaki_kolor_bijemy = 'C';
	if(jaki_kolor_bije=='C')
		jaki_kolor_bijemy = 'B';
	if (y > 1 && x < 6)
	{
		if (Polorzenie_pionk�w[y-1][x+1] == jaki_kolor_bijemy && Polorzenie_pionk�w[y - 2][x + 2] == '.')
			return true;
	}
	return false;
}



bool Plansza::mozliwe_ruchy_czarne()
{
	sf::Event e;
	for (int i = 0; i < ile_czarnych; ++i)									// Lece po wszystkich czarnych pionkach
	{																		// Sprawdzanie bicia
		int x = tab_Pionek_1[i].get_pozycja_x();
		int y = tab_Pionek_1[i].get_pozycja_y();
		if(bicie_prawy_dol(x, y));
		if(bicie_lewy_dol(x, y));
		if(bicie_lewy_gora(x, y));
		if(bicie_prawy_gora(x, y));
	

	}

	for (int i = 0; i < ile_czarnych; ++i)									// Lece po wszystkich czarnych pionkach
	{
		if (tab_Pionek_1[i].get_klikniety())								// jesli wcisniety
		{
			int x = tab_Pionek_1[i].get_pozycja_x();
			int y = tab_Pionek_1[i].get_pozycja_y();
			
			if (ruch_prawy_dol(x, y))										// jesli mozliwy ruch ustaw podpowiedz i dodaj do okna
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
			tab_Podswietlenia[0].sprawdz_Zdarzenia(e);						// Sprawdzam czy podpowiedz jest kliknieta
			if (tab_Podswietlenia[0].get_klikniety()&& ruch_prawy_dol(x, y))
			{
				Polorzenie_pionk�w[y][x] = '.';								// wykonanie ruchu
				Polorzenie_pionk�w[y + 1][x + 1] = 'C';
				tab_Pionek_1[i].set_klikniety(0);
				Poka_polozenie_pionkow();
				return true;
			}
			tab_Podswietlenia[1].sprawdz_Zdarzenia(e);
			if (tab_Podswietlenia[1].get_klikniety()&& ruch_lewy_dol(x, y))
			{
				Polorzenie_pionk�w[y][x] = '.';
				Polorzenie_pionk�w[y + 1][x - 1] = 'C';
				tab_Pionek_1[i].set_klikniety(0);
				Poka_polozenie_pionkow();
				return true;
			}
		}

	}
	return false;
}
bool Plansza::mozliwe_ruchy_biale()
{ 
	sf::Event e;
	int i;
	for (i = 0; i < ile_bialych; ++i)
	{
		if (tab_Pionek_2[i].get_klikniety())
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

			tab_Podswietlenia[2].sprawdz_Zdarzenia(e);
			if (tab_Podswietlenia[2].get_klikniety() && ruch_prawy_gora(x, y))
			{
				Polorzenie_pionk�w[y][x] = '.';
				Polorzenie_pionk�w[y - 1][x + 1] = 'B';
				tab_Pionek_2[i].set_klikniety(0);
				Poka_polozenie_pionkow();
				return true;
			}
			tab_Podswietlenia[3].sprawdz_Zdarzenia(e);
			if (tab_Podswietlenia[3].get_klikniety() && ruch_lewy_gora(x, y))
			{
				Polorzenie_pionk�w[y][x] = '.';
				Polorzenie_pionk�w[y - 1][x - 1] = 'B';
				tab_Pionek_2[i].set_klikniety(0);
				Poka_polozenie_pionkow();
				return true;
			}
			
			
		}	
	}
	
	return false;
}

void Plansza::Wysteruj_z_logiki()
{
	int b = ile_czarnych;
	int a = ile_bialych;
	for (int i = 0; i < 8; i++)				//wiadomo	
	{
		for (int j = 0; j < 8; j++)			// wiadomo
		{
			if (Polorzenie_pionk�w[i][j] == 'C')	// jezeli pionek czarny
			{
				tab_Pionek_1[--a].set_Pozycja(70 + j * 100, 70 + (i * 100));
				tab_Pionek_1[a].set_pozycja_x(j);
				tab_Pionek_1[a].set_pozycja_y(i);
			}
			if (Polorzenie_pionk�w[i][j] == 'B')   // jezeli pionek bia�y
			{
				tab_Pionek_2[--b].set_Pozycja(70 + j * 100, 70 + (i * 100));
				tab_Pionek_2[b].set_pozycja_x(j);
				tab_Pionek_2[b].set_pozycja_y(i);
			}
		}
	}
}






void Plansza::Show()
{
	bool ktopierwszy = 0;
	Poka_polozenie_pionkow();
	sf::Event e;
	int a = 0, b = 0, c = 0;
	while (Okno.isOpen())
	{
		Okno.clear(Color(a, b, c));
		
		
		
		while (Okno.pollEvent(e))			// koolejka wydarzen, ktore sie zadzia�a�y od ostatniej klatki
		{
			if (e.type == sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
				Okno.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			{
				a++;
				b++;
				c++;
				if (a > 254) {
					a = b = c = 0;
				}
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
			if(mozliwe_ruchy_biale()) ktopierwszy = 0;
		}
		else
		{
			if(mozliwe_ruchy_czarne()) ktopierwszy=1;
		}
		/* Dodawanie do Okna Pionk�w */
		for (int i = 0; i < ile_czarnych; ++i)
		{
			Okno.draw(tab_Pionek_1[i].Get());	//Czarne
		}
		for (int i = 0; i < ile_bialych; ++i)
		{
		Okno.draw(tab_Pionek_2[i].Get());	//Bia�e
		}	
		/* Sprawdzanie zdarzen dla Pionk�w*/
		for (int i = 0; i < ile_czarnych; ++i)
		{
			tab_Pionek_1[i].sprawdz_Zdarzenia(e);
		}
		for (int i = 0; i < ile_bialych; ++i)
		{
			tab_Pionek_2[i].sprawdz_Zdarzenia(e);
		}
		
		
		Wysteruj_z_logiki();
		Okno.display();	//Wiadomo
		
	}
}