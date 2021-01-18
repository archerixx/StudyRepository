#pragma once

#include "Datum.h"

class Osoba
{
private:
	char* ime;
	int starost;
	char spol;
	Datum date;

	float cijena;
	float& c = cijena;
public:
	Osoba();
	Osoba(const char* ime, int starost, char spol);
	Osoba(const char* ime, int starost, char spol, int d, int m, int g);
	Osoba(const char* ime, int starost, char spol, Datum date);
	//Osoba(const char* ime, int starost, char spol, Datum datum) :date(datum) {};
	Osoba(Osoba&); //copy of constructor
	Osoba(const Osoba&& orginal);

	Osoba GetOsoba(); //copy const po parametru fj
	
	Osoba(const char* imeN, int starost, char spol, int cij, int d, int m, int g) :c(cijena) 
	{
		this->ime = new char[strlen(ime) + 1];
		strcpy_s(this->ime, strlen(ime) + 1, ime);
		this->starost = starost;
		this->spol = spol;

	};
	

	void setIme(char* ime);
	//void setSpol(int starost);
	//void setStarost(char spol);

	char* getIme() const;
	//int getStarost() const;
	//char getSpol() const;

	int getDateDay() const;

	~Osoba()
	{
		delete []ime;
		ime = NULL;
	}
};