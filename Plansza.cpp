#include "Plansza.h"
#include <iostream>
/* Konstruktor */
Plansza::Plansza()
{
	int a=ile_bialych=12;
	int b=ile_czarnych=12;
	
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
	/* Ustawienie tabilicy logicznej warcabów  B-bia³e C-czarne .-puste pole */
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
				tab_Pionek_1[--a].set_Pozycja(70 + j * 100, 70 + (i * 100));
				tab_Pionek_1[a].set_pozycja_x(j);
				tab_Pionek_1[a].set_pozycja_y(i);
			}
			if (Polorzenie_pionków[i][j] == 'B')   // jezeli pionek bia³y
			{
				tab_Pionek_2[--b].set_Pozycja(70 + j * 100, 70 + (i * 100));
				tab_Pionek_2[b].set_pozycja_x(j);
				tab_Pionek_2[b].set_pozycja_y(i);
			}
		}
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
	char jaki_kolor_bijemy;

	if (jaki_kolor_bije == 'B')
		jaki_kolor_bijemy = 'C';
	if(jaki_kolor_bije=='C')
		jaki_kolor_bijemy = 'B';

	if (x > 1 && y < 6)
	{
		if (Polorzenie_pionków[++y][--x] == jaki_kolor_bijemy && Polorzenie_pionków[y+2][x-2] == '.')
			return true;
	}
	return false;
}
bool Plansza::bicie_lewy_gora(int x, int y)
{
	return false;
}
bool Plansza::bicie_prawy_dol(int x, int y)
{
	return false;
}
bool Plansza::bicie_prawy_gora(int x, int y)
{
	return false;
}



bool Plansza::mozliwe_ruchy()
{
	for (int i = 0; i < ile_czarnych; ++i)
	{
		if (tab_Pionek_1[i].get_klikniety())
		{
			int x = tab_Pionek_1[i].get_pozycja_x();
			int y = tab_Pionek_1[i].get_pozycja_y();
			std::cout << "-------------Czarne----------------------------------\n";
			std::cout << "x:  " << x << "  y:  " << y << "\n";
			std::cout << "R_prawy dol:  " << ruch_prawy_dol(x, y) << "\n";
			std::cout << "R_lewy dol:   "<<ruch_lewy_dol(x, y)<<"\n";
			std::cout << "R_lewy gora:  " << ruch_lewy_gora( x,y) << "\n";
			std::cout << "R_prawy gora: " << ruch_prawy_gora( x, y) << "\n";
			std::cout << "----------------------------------------------------\n";
		}

	}
	for (int i = 0; i < ile_bialych; ++i)
	{
		if (tab_Pionek_2[i].get_klikniety())
		{
			int x = tab_Pionek_2[i].get_pozycja_x();
			int y = tab_Pionek_2[i].get_pozycja_y();
			std::cout << "-------------Bia³e----------------------------------\n";
			std::cout << "x:  " << x << "  y:  " << y << "\n";
			std::cout << "R_prawy dol:  " << ruch_prawy_dol(x, y) << "\n";
			std::cout << "R_lewy dol:   " << ruch_lewy_dol(x, y) << "\n";
			std::cout << "R_lewy gora:  " << ruch_lewy_gora(x, y) << "\n";
			std::cout << "R_prawy gora: " << ruch_prawy_gora(x, y) << "\n";
			std::cout << "----------------------------------------------------\n";
		}
	}
	return false;
}






void Plansza::Show()
{
	Poka_polozenie_pionkow();
	sf::Event e;
	int a = 0, b = 0, c = 0;
	while (Okno.isOpen())
	{
		
		while (Okno.pollEvent(e))			// koolejka wydarzen, ktore sie zadzia³a³y od ostatniej klatki
		{
			if (e.type == sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
				Okno.close();
			a++;
			b++;
			c++;
			if (a > 254) {
				a = b = c = 0;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			{
				for (int i = 0; i < ile_bialych; ++i)
				{
					mozliwe_ruchy();
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
		Okno.clear(Color(a, b, c));
	}
}