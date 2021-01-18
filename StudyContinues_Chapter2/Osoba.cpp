#include <iostream>
#include "Osoba.h"
#include "Datum.h"

using namespace std;

Osoba::Osoba()
{
	this->ime = new char[10];
	strcpy_s(ime, 11, "Igor");
	starost = 24;
	spol = 'M';
	cijena = 5;
}

Osoba::Osoba(const char* ime, int starost, char spol)
{
		this->ime = new char[strlen(ime) + 1];
		strcpy_s(this->ime, strlen(ime) + 1, ime);
		this->starost = starost;
		this->spol = spol;
}

Osoba::Osoba(const char* ime, int starost, char spol, int d, int m, int g) :date(d, m, g)
{
	this->ime = new char[strlen(ime) + 1];
	strcpy_s(this->ime, strlen(ime) + 1, ime);
	this->starost = starost;
	this->spol = spol;
}
Osoba::Osoba(const char* ime, int starost, char spol, Datum randomDate) :date(randomDate.uzmiDan(), randomDate.uzmiMjesec(), randomDate.uzmiGodinu())
{
	this->ime = new char[strlen(ime) + 1];
	strcpy_s(this->ime, strlen(ime) + 1, ime);
	this->starost = starost;
	this->spol = spol;
}

Osoba::Osoba(const Osoba&& orginal)
{
	this->ime = orginal.ime;
	this->starost = orginal.starost;
	this->spol = orginal.spol;
}

Osoba Osoba::GetOsoba()
{
	Osoba temp("Novo", 20, 'n');
	return temp;
}

Osoba::Osoba(Osoba& copyFromOsoba)
{
	ime = copyFromOsoba.ime;
	starost = copyFromOsoba.starost;
	spol = copyFromOsoba.spol;
}

void Osoba::setIme(char* imeN)

{
	this->ime = new char[strlen(imeN)];
	strcpy_s(ime, strlen(imeN) + 1, imeN);
}

char * Osoba::getIme() const
{
	return this->ime;
}

int Osoba::getDateDay() const
{
	return date.uzmiDan();
}