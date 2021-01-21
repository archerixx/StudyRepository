#include <iostream>
#include "Datum.h"
#include "Predmet.h"
#include "PolozeniPredmet.h"
#include "Kolekcija.h"

using namespace std;

const char* ln = "\n------------------------------------\n";

const char* alociraj(const char* sadrzaj)
{
	char* noviSazdraj = new char(strlen(sadrzaj) + 1);
	strcpy_s(noviSazdraj, strlen(sadrzaj) + 1, sadrzaj);
	return noviSazdraj;
}


int main()
{
	Datum * d = new Datum[3];
	
	d[0].setDatum(15, 12, 1996);

	cout << d[0];

//	Predmet p(1, "Mat", "Sabin");

	//cout << p;

	PolozeniPredmet pp1(15, 12, 1996, 10, 1, "Hemija", "Zerin");
	PolozeniPredmet pp2(15, 12, 1996, 10, 1, "Biologija", "Emir");

	
	if (pp1 == pp2)
	{
		cout << "Isti";
	}

	pp1.dodajPredavaca("Emir");

	pp2 = pp1;

	cout << endl <<  pp2;
}