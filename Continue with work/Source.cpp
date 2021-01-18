#include <iostream>
#include <functional>
#include <tuple>
#include "Tacka.h"
#include "Krug.h"
#include <iomanip>
#include "Zaposlenik.h"
#include "RadnikNaSat.h"
#include "Primjer1.h"
#include "Cilindar.h"
#include "Inh.h"
#include "Direktor.h"
#include "RadnikPoKomadu.h"
#include "Radnik.h"

using namespace std;

/*
struct Student
{
	char ime[10];
};
pair <Student, int> GetPair()
{
	return make_pair(Student{ "Zerin" }, 1);
}
tuple <int, Student, float, char> GetTri()
{
	return make_tuple(3, Student{ "Zerin" }, 5.4, 'M');
}
*/



int main()
{
	/*
	int a=95, b=62;

	auto pok = [a,b]()
	{
		return a > b;
	};

	if (pok())
		cout << "Veci a";
	else
		cout << "veci b";

	///////////
	bool (*pok1)(int, int)= [](int a, int b)
	{
		return a > b;
	};

	cout << endl << pok1(a,b);

	///////////
	function<bool()> pok2 = [a, b]()
	{
		return a < b;
	};

	cout << endl << pok2();
	*/
	/*
	Student s;
	int broj=10;

	pair <int, float> par1(20, 1.5);
	pair <int, float> par2 = make_pair(1, 5.2); //inicijalizacija

	cout << par1.first;
	cout << endl << par1.second;// prvi nacin poziva

	cout << endl << get<0>(par2) << endl << get<1>(par2); // drugi nacin poziva

	tie(s, broj) = GetPair(); // vraca i dodjeljuje vrijdnosti fuknciji

	cout << endl << s.ime << endl << broj;
	*/
	/*
	Student s;
	int ID;

	tuple<int, Student, float, char> tri(2, Student{ "Lejla" }, 7.8, 'Z');

	cout << get<0>(tri) << " " << get<1>(tri).ime << " " << get<3>(tri);
	cout << endl;

	tie(ID, s, ignore, ignore) = GetTri();

	cout << ID << endl << s.ime;
	*/
	/*
	// vrsenje castinga bazne klase u pokazivac izvedene klase

	tacka* tPtr = NULL;
	tacka t(2,5);
	krug* kPtr = NULL;
	krug k(3.2, 3,4);

	cout << "\nTacka t: " << t;
	cout << "\nKrug k: " << k;

	//tretiranje klase "krug" kao "tacka" (vidi samo dio bazne klase)
	tPtr = &k;
	cout << "\nKrug preko pokazivaca tacke " << *tPtr;

	//tretiranje "krug" kao "krug" sa cast-om
	//cast pokazivac bazne klase u pokazivac izvedene
	kPtr = static_cast<krug*>(tPtr);
	cout << "\nKrug preko pokazivacna kruga: " << *kPtr;
	cout << "\nPovrsina od k preko pokazivaca kruga: " << kPtr->getPovrsina() << endl;

	///////////////////////////
	// WARNING: tetiranje "tacka" kao "krug"
	tPtr = &t;

	//cast pokazivaca bazne klase u pokazivac izvedene klase
	kPtr = static_cast<krug*>(tPtr);

	cout << "\nTacka t preko pokazivaca na krug: " << *kPtr;
	cout << "\nPovrsina objekta na koji pokazuje krug pokazivac: " << kPtr->getPovrsina() << endl;
	*/
	/*
	RadnikNaSat r(40, 10, "Zerin", "Tursic");
	r.print();
	*/
	/*
	{
	prTacka t(1, 5);
	}
	cout << endl;

	prKrug k1(3.4, 7, 8);
	cout << endl;

	prKrug k2(51.2, 9, 10);
	*/
	/*
	cilindar c(2, 3, 6, 4);
	cout << "\nx: " << c.getX()
		<< "\ny: " << c.getY()
		<< "\nRadius: " << c.getR()
		<< "\nVisina: " << c.getVisina() << endl;

	c.setVisina(10);
	c.setRadius(1);
	c.setTacka(7, 8);

	cout << "\nNova lokacija, radius i viinsa od c: \n" << c << endl;

	cout << "\n P: " << c.povrsina();

	tacka& tRef = c;
	cout << "\nCilindar kao tacka: " << tRef << endl;

	krug& kRef = c;
	cout << "\nCilindar kao krug: " << kRef << endl;
	kRef.getPovrsina();
	*/
	/*
	Baza b1(3), *bPtr=NULL;
	bazaBr2 br2('S'), *brPtr=NULL;

	inh	i(4.2, 5, 'a');

	cout << "\nB1: " << b1.getData()
		<< "\nBr2: " << br2.getData()
		<< "\nInh: " << i<< endl;

	//Podaci se mogu izvuci pojedinsacno preko izvedene baze
	cout << "\n Int: " << i.Baza::getData()
		<< "\n Slovo: " << i.bazaBr2::getData()
		<< "\n Double: " << i.getData() << endl;

	// Inh se moze tretirati kao obj baznih klasa
	bPtr = &i;
	cout << bPtr->getData() << endl;

	//////
	brPtr = &i;
	cout << brPtr->getData() << endl;
	
	brPtr = static_cast<inh*>(bPtr);
	cout << endl << brPtr->getData();

	inh* ptrI;
	ptrI = static_cast<inh*>(bPtr);

	cout << *ptrI;
	*/

	RadnikNaSat r1(800, 40);

	Zaposleni* ptrZap;

	ptrZap = &r1;

	//cout << ptrZap->getIme();
	//ptrZap->Zaposleni::print();

	cout << endl;
	ptrZap->print();

	Direktor d1(800);
	ptrZap = &d1;

	ptrZap->print();

	radnikPoKomadu rPoK(400, 300, 3);
	ptrZap = &rPoK;

	ptrZap->print();


	RadnikNaSat* radPtr= nullptr;
	
	//radPtr = &r1;

	//ptrZap = radPtr;
	
	//cout << endl;
	//ptrZap->print();
	ptrZap = &r1;
	radPtr = dynamic_cast<RadnikNaSat*>(ptrZap);

	radPtr->setSati(30);
	cout << endl << radPtr->getSati();


	radnik rad("IT", 50, "Zerin", "Tursic", 400, 1500, 40);

	cout << endl << endl;

	rad.print();
}