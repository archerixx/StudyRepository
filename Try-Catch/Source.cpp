#include <iostream>
#include "Kalkulator.h"

using namespace std;

void racun()
{
	Kalk k;

	k.dodaj(5);
	k.dodaj(4);
	k.korjen();

	cout << k.getSuma() << endl;

	Kalk k1(-5);
	
	k.dijeli(0);
	k.dodaj(4);

	//k1.korjen();
	k1.dijeli(5);
	cout << k1.getSuma() << endl;
	
}

int main()
{

	try
	{
		racun();
	}
	catch (LosaOperacija &o)
	{
		cout << o << endl;
	}
	/*
	catch (NedozvoljenRacun & nK)
	{
		cout << nK.getPoruka() << endl;
		//DijeljenjeSaNulom::getDijeljenik;
	}
	catch (DijeljenjeSaNulom &d)
	//////////////////////
	/* catch (exception &ex)
	 {
		ex.what(); ispisuje poruku
	 }
	catch (double& broj)
	{
		cout << "Greska, broj " << broj << "se ne moze dijeliti sa nulom";
	}
	*/
	////////////////////////
	/*
	{
		cout << d.getPoruka() << endl;
		cout << "Broj " << d.getDijeljenik() << " se ne moze dijelit sa Nulom";
	}
	*/
}

