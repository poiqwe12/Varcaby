#include "Plansza.h"

/* Konstruktor */
Plansza::Plansza()
{
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
			//Pole[i][j].setOutlineColor(sf::Color::Black);
			//Pole[i][j].setOutlineThickness(5);
			if ((i + j) % 2 == 0)
			{
				(Pole[i][j]).setFillColor(Color::White);
			}
			else
			{
				(Pole[i][j]).setFillColor(Color::Black);
			}
			Pole[i][j].setPosition(20+j * 100, 20 + (i * 100));
		}
	}
	/* Czcionka */
	Font ttf;
	ttf.loadFromFile("arial.ttf");
	String s("1");
	Text txt(s,ttf);
	txt.setCharacterSize(18);
	txt.setFillColor(Color(90, 90, 90));
	txt.setPosition(10, 40);
	
	
}


/* Destruktor */
Plansza::~Plansza()
{

}


void Plansza::Show()
{
	sf::Event e;

	while (Okno.isOpen())
	{
		Okno.clear(sf::Color::Blue);
		while (Okno.pollEvent(e))			// koolejka wydarzen, ktore sie zadzia³a³y od ostatniej klatki
		{
			if (e.type == sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
				Okno.close();
		}
	
		
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				Okno.draw(Pole[i][j]);
			}
		}
		Okno.draw(txt);
		
		
		Okno.display();
	}
}