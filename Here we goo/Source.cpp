#include <iostream>
#include "Baza.h"
#include "Izvedena.h"
#include "Drugi_IZveden.h"

using namespace std;

int main()
{
	Oblik* o = new Tacka(2, 3);
	Tacka* t = new Krug(1,5,5);

	cout << o->getIme() << endl;
	cout << t->getIme() << endl;
	cout << o->getP() << endl;
	cout << t->getP() << endl;
	o->print();
	cout << endl;
	t->print();
	cout << endl;

	delete o;
	delete t;
}