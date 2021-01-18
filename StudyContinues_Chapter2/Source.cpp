#include <iostream>
#include "Datum.h"
#include "Osoba.h"

using namespace std;



int main()
{
	/*
	bool err = false;
	int dan, mjesec, godina;

	Datum d;
	Datum &kd = d;

	cout << d.uzmiGodinu();
	cout << endl << kd.uzmiDan();

	Datum cD(20, 10, 1955);
	Datum cD2(cD);

	cout << endl << cD2.uzmiMjesec();
	
	*/
	//cout << "Unesite datum ";
	//cin >> dan >> mjesec >> godina;
	/*
	Datum danas, rodjenan, sutra;
	danas.napravi(dan, mjesec, godina, err);

	if (err == false)
	{
		cout << "Datum je: " << danas.uzmiDan() << "."
			<< danas.uzmiMjesec() << "." << danas.uzmiGodinu() << " godine" << endl;
	}
	else
		cout << "Pogresan datum ! " << endl;

	rodjenan.kopiraj(danas);
	dan = 20;
	rodjenan.postaviDan(dan, err);

	cout << rodjenan.uzmiDan() << endl;

	if (rodjenan.jednako(danas))
		cout << "Isti datum";
	else
		cout << "Nijes isti";
	*/
	/*
	Osoba o1;

	char ime[10];
	cin.getline(ime, 10);

	cout << o1.getIme();
	const Osoba o2;


	
	//Osoba o2(ime, 15, 'a');

	//cout << o2.getIme();


	Osoba o3(move(o2));
	cout << o3.getIme();
	//cin.getline(ime, 10);
	//o3.setIme(ime);
	
	cout << o2.getIme();

	Osoba o4;
	//o4 = o4.GetOsoba();

	cout << endl << o4.getIme();
	*/
	/*
	Osoba o1("Next", 23, 'n', 15, 12, 1996);

	char ime[10];
	cin.getline(ime, 10);

	cout << o1.getIme();
	cout << endl << o1.getDateDay();
	*/
	/*
	Osoba* o1 = new Osoba;
	Osoba* o2 = new Osoba("Zera", 15, 'M', 15, 12, 1996);

	cout << o2->getDateDay();

	delete o1;
	delete o2;

	Osoba* o = new Osoba[5]; // mora postojati Default const za niz

	delete[] o;
	*/
	/*
	Osoba * o1 = nullptr;
	Osoba o2("Zera", 24, 'M');
	o1 = new Osoba("Lejla", 22, 'Z');

	delete o1;
	o1 = NULL;

	o2.~Osoba();

	Datum d1(4, 5, 3);
	//cout << d1.uzmiGodinu();
	cout << d1.getBrojDana(d1);
	*/


	Osoba o1("Zera", 15, 'M', 35, 15, 12, 1996);
}


