
struct Pozycja
{
	int tab_wagi_pionowe[8];
	int tab_wagi_poziome[8];
	int waga_bicie, waga_damka;
	char tab[8][8];
	int waga_czarnych,waga_bialych;
	Pozycja()
	{
		waga_czarnych = 0;
		waga_bialych = 0;
		tab_wagi_pionowe[0] = 1;
		tab_wagi_pionowe[1] = 3;
		tab_wagi_pionowe[2] = 5;
		tab_wagi_pionowe[3] = 8;
		tab_wagi_pionowe[4] = 11;
		tab_wagi_pionowe[5] = 16;
		tab_wagi_pionowe[6] = 22;
		tab_wagi_pionowe[7] = 29;

		tab_wagi_poziome[0] = 1;
		tab_wagi_poziome[1] = 2;
		tab_wagi_poziome[2] = 3;
		tab_wagi_poziome[3] = 4;
		tab_wagi_poziome[4] = 4;
		tab_wagi_poziome[5] = 3;
		tab_wagi_poziome[6] = 2;
		tab_wagi_poziome[7] = 1;

		waga_bicie = 20;
		waga_damka = 35;
	}
	void policz_wage()
	{	
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if ( tab[i][j] == 'C')
			{
				waga_czarnych = waga_czarnych + tab_wagi_pionowe[i] + tab_wagi_poziome[j];
				//waga +=10;
			}
			if ( tab[i][j] == 'B')
			{
				waga_bialych = waga_bialych + tab_wagi_pionowe[7 - i] + tab_wagi_poziome[j];
				//waga += 10;
			}
			if ( tab[i][j] == 'c')
			{
				waga_bialych = waga_bialych + tab_wagi_poziome[j];
			}
			if (tab[i][j] == 'b')
			{
				waga_czarnych = waga_czarnych + tab_wagi_poziome[j];
			}
		}
	}
	}
};
