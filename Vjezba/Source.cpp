#include <iostream>
#include "Datum.h"
#include "Predmet.h"
#include "PolozeniPredmet.h"
#include "Kolekcija.h"
#include "Student.h"
#include <exception>
#include "Iznimci.h"

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
	try
	{
		Student s1(190038, alociraj("Zerin Tursic"));
		Datum* d1 = new Datum(15, 1, 2020);

		s1.dodajPolozeni(1, alociraj("Math"), alociraj("Zerin"), d1, 10);
		s1.dodajPolozeni(1, alociraj("Bio"), alociraj("Berin"), d1, 8);

		cout << s1;
		
	}
	catch (iznimka& a)
	{
		cout << a.getPoruka();
	}
	
	
}