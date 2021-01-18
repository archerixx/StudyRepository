#include <iostream>
#include "Test.h"
#include "Zivotinje.h"


using namespace std;


Zivotinja::Zivotinja()
{
	delete[] vrsta;
	vrsta = new char[10];
	strcpy_s(vrsta, 10, "");

	delete tezina;
	tezina = new int;
	*tezina = 0;
}
/*
Zivotinja::Zivotinja(const char* vrsta, int tezina)
{
	delete[] this->vrsta;
	this->vrsta = new char[strlen(vrsta) + 1];
	strcpy_s(this->vrsta, strlen(vrsta) + 1, vrsta);

	delete this->tezina;
	this->tezina = new int;
	*this->tezina = tezina;
}
*/
Zivotinja::~Zivotinja()
{
	delete[] vrsta;
	vrsta = NULL;

	delete tezina;
	tezina = NULL;
}

bool Zivotinja::operator<(const Zivotinja& druga)
{
	return (*this->tezina < *druga.tezina);
}

Zivotinja Zivotinja::operator=(const Zivotinja& druga)
{
	if (this != &druga)
	{
		delete[] vrsta;
		vrsta = NULL;

		delete tezina;
		tezina = NULL;
	}

	vrsta = new char[strlen(druga.vrsta) + 1];
	strcpy_s(vrsta, strlen(druga.vrsta) + 1, druga.vrsta);

	tezina = new int;
	tezina = druga.tezina;

	return *this;
}

std::ostream& operator<<(std::ostream& os, const Zivotinja& obj)
{
	os << "Vrsta: " << obj.vrsta << std::endl << "Tezina: " << *obj.tezina << std::endl;
	return os;
}

std::istream& operator>>(std::istream& is, const Zivotinja& obj)
{
	is >> obj.vrsta >> *obj.tezina;
	return is;
}