#include "Pionek.h"
#include <iostream>

/* Konstruktor*/
Pionek::Pionek()
{
	Kolko.setRadius(40);
	Kolko.setPointCount(9);
	
	Kolko.setOutlineThickness(3);
	Kolko.setOrigin(Vector2f(40, 40));
	najechany = false;
	klikniety = false;
	
}

void Pionek::set_pozycja_x(int p)
{
	pozycja_x = p;
}

void Pionek::set_pozycja_y(int p)
{
	pozycja_y = p;
}

int Pionek::get_pozycja_x()
{
	return pozycja_x;
}

int Pionek::get_pozycja_y()
{
	return pozycja_y;
}

bool Pionek::get_najechany()
{
	return najechany;
}

bool Pionek::get_klikniety()
{
	return klikniety;
}

void Pionek::set_Kolor(int r, int g, int b)
{
	C.r = r;
	C.g = g;
	C.b = b;
	Kolko.setFillColor(Color(r, g, b));
	Kolko.setOutlineColor(Color(255-r, 255-g, 255-b));
}
void Pionek::set_Rozmiar(float radius)
{
	Kolko.setRadius(radius);
}
void Pionek::set_klikniety(bool a)
{

	klikniety = a;
	if(!klikniety)
		Kolko.setFillColor(Color(C.r, C.g, C.b));
	if(klikniety) 
		Kolko.setFillColor(Color::Red);
}
void Pionek::set_Pozycja(float x, float y)
{
	Kolko.setPosition(x,y);
}
void Pionek::sprawdz_Zdarzenia(Event &e)
{
	Vector2i pozycja = sf::Mouse::getPosition(*Okienko);
	Vector2f W = Kolko.getPosition();
	//std::cout << "poz.x " << pozycja.x << "\t poz.y " << pozycja.y << "\n";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		std::cout << "Klik: " << klikniety << "\n";
		std::cout << "Najechan: " << najechany << "\n";
	}
	if (pozycja.x > (W.x - Kolko.getRadius())&& pozycja.x < (W.x + Kolko.getRadius())&&    // Sprawdza czy kusor myszy jest nad pionkiem
		pozycja.y >(W.y - Kolko.getRadius()) && pozycja.y < (W.y + Kolko.getRadius()))
	{
		najechany = true;																	// jesli tak to podswietla go 
		if(!klikniety) Kolko.setFillColor(Color(C.r+20, C.g + 20, C.b+20));
	}
	else                                                                           // Jezeli kursor jest poza pionkiem
	{
		najechany = false;					
		if (!klikniety) Kolko.setFillColor(Color(C.r , C.g , C.b));									
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			Kolko.setFillColor(C);
			klikniety = false;
		}
	}
	if (najechany && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{		
		klikniety = 1;
		Kolko.setFillColor(Color::Red);											// Kolor po kliknieciu
	}
}