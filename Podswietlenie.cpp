#include "Podswietlenie.h"
#include <iostream>

/* Konstruktor*/
Podswietlenie::Podswietlenie()
{
	Kolko.setRadius(20);
	Kolko.setPointCount(50);

	
	Kolko.setOrigin(Vector2f(20, 20));
	najechany = false;
	klikniety = false;

}

void Podswietlenie::set_pozycja_x(int p)
{
	pozycja_x = p;
}

void Podswietlenie::set_pozycja_y(int p)
{
	pozycja_y = p;
}

int Podswietlenie::get_pozycja_x()
{
	return pozycja_x;
}

int Podswietlenie::get_pozycja_y()
{
	return pozycja_y;
}

bool Podswietlenie::get_najechany()
{
	return najechany;
}

bool Podswietlenie::get_klikniety()
{
	return klikniety;
}

void Podswietlenie::set_Kolor(int r, int g, int b)
{
	C.r = r;
	C.g = g;
	C.b = b;
	Kolko.setFillColor(Color(r, g, b));
	
}
void Podswietlenie::set_Rozmiar(float radius)
{
	Kolko.setRadius(radius);
}
void Podswietlenie::set_Pozycja(float x, float y)
{
	Kolko.setPosition(x, y);
}
void Podswietlenie::sprawdz_Zdarzenia(Event &e)
{
	Vector2i pozycja = sf::Mouse::getPosition(*Okienko);
	Vector2f W = Kolko.getPosition();
	//std::cout << "poz.x " << pozycja.x << "\t poz.y " << pozycja.y << "\n";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		std::cout << "Klik: " << klikniety << "\n";
		std::cout << "Najechan: " << najechany << "\n";
	}
	if (pozycja.x > (W.x - Kolko.getRadius()) && pozycja.x < (W.x + Kolko.getRadius()) &&    // Sprawdza czy kusor myszy jest nad pionkiem
		pozycja.y >(W.y - Kolko.getRadius()) && pozycja.y < (W.y + Kolko.getRadius()))
	{
		najechany = true;																	// jesli tak to podswietla go 
		Kolko.setFillColor(Color(C.r + 40, C.g + 40, C.b + 40));
	}
	else                                                                           // Jezeli kursor jest poza pionkiem
	{
		najechany = false;
		Kolko.setFillColor(C);
		klikniety = false;
	
	}
	if (najechany && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		klikniety = 1;
		Kolko.setFillColor(Color::Red);											// Kolor po kliknieciu
	}
}