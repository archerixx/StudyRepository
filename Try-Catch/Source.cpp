#include <iostream>
#include "Kalkulator.h"

using namespace std;

int main()
{
	Kalk k;

	k.dodaj(5);
	k.dodaj(4);
	k.korjen();

	cout << k.getSuma() << endl;

	Kalk k1(-5);

	try
	{
		//k.dijeli(0);
		k.dodaj(4);

		//k1.korjen();
		k1.dijeli(5);
		cout << k1.getSuma() << endl;
	}
	catch (NedozvoljenRacun & nK)
	{
		cout << nK.getPoruka() << endl;
		DijeljenjeSaNulom::getDijeljenik;
	}
	catch (DijeljenjeSaNulom &d)
	{
		cout << d.getPoruka() << endl;
		cout << "Broj " << d.getDijeljenik() << " se ne moze dijelit sa Nulom";
	}
	
}