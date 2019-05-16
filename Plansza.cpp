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
	Okno.setKeyRepeatEnabled(false);		// pozwalaj na to by samoczynnie powtarza� sie wcisnienty w oknie pcicisk
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
				tab_Pionek_1[a].set_pozycja_x(i);
				tab_Pionek_1[a].set_pozycja_y(j);
			}
			if (Polorzenie_pionk�w[i][j] == 'B')   // jezeli pionek bia�y
			{
				tab_Pionek_2[--b].set_Pozycja(70 + j * 100, 70 + (i * 100));
				tab_Pionek_2[b].set_pozycja_x(i);
				tab_Pionek_2[b].set_pozycja_y(j);
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
			std::cout << "|" << Polorzenie_pionk�w[i][j];
		}
		std::cout << "|" << "\n";
	}
}

void Plansza::Show()
{
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
			a++;
			b++;
			c++;
			if (a > 254) {
				a = b = c = 0;
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
		
		
		Okno.display();	//Wiadomo
	}
}