#pragma once
#include "Predmet.h"
#include "Datum.h"

class PolozeniPredmet : public Predmet
{
private:
	Datum* datumPolaganja = new Datum;
	int* ocjena;
public:
	PolozeniPredmet();
	PolozeniPredmet(int d, int m, int g, int ocjena, int ID, const char* nazivPredmeta, const char* nazivPredavaca);
	PolozeniPredmet(int ID, const char* nazivPredmeta, const char* nazivPredavaca, Datum* date, int ocjena);
	PolozeniPredmet(PolozeniPredmet& org);

	bool operator==(PolozeniPredmet& obj);

	PolozeniPredmet& operator=(PolozeniPredmet& obj);

	friend std::ostream& operator<<(std::ostream& os, PolozeniPredmet& obj);
};

PolozeniPredmet::PolozeniPredmet() :Predmet(0, "-", "-")
{
	ocjena = new int;
	*ocjena = 5;
}

PolozeniPredmet::PolozeniPredmet(int d, int m, int g, int ocjena, int ID, const char* nazivPredmeta, const char* nazivPredavaca) :Predmet(ID, nazivPredmeta, nazivPredavaca)
{
	datumPolaganja->setDatum(d, m, g);
	this->ocjena = new int;
	*this->ocjena = ocjena;
}

PolozeniPredmet::PolozeniPredmet(int ID, const char* nazivPredmeta, const char* nazivPredavaca, Datum* date, int ocjena) :Predmet(ID, nazivPredmeta, nazivPredavaca), datumPolaganja(date)
{
	this->ocjena = new int;
	*this->ocjena = ocjena;
}

inline PolozeniPredmet::PolozeniPredmet(PolozeniPredmet& org):Predmet(org), datumPolaganja(org.datumPolaganja)
{
	this->ocjena = new int;
	*ocjena = *org.ocjena;
}

inline bool PolozeniPredmet::operator==(PolozeniPredmet& obj)
{
	if (datumPolaganja==obj.datumPolaganja && *ocjena==*obj.ocjena 
		&& *predmetID==*obj.predmetID && strcmp(obj.nazivPredavaca[obj.profBr-1], nazivPredavaca[profBr-1]) == 0
		&& strcmp(obj.nazivPredmeta, nazivPredmeta) == 0 && (obj.profBr - 1)==(profBr - 1))
	{
		return true;
	}
	else
		return false;
}

inline PolozeniPredmet& PolozeniPredmet::operator=(PolozeniPredmet& obj)
{
	if (*this == obj)
		return *this;
	else
	{

		delete datumPolaganja;
		delete ocjena;
		
		//predmetID=NULL;
		delete[] nazivPredmeta;
		
		for (int j = 0; j < profBr;j++)
			delete[] nazivPredavaca[j];
			
		this->datumPolaganja = obj.datumPolaganja;
		this->ocjena = new int;
		*this->ocjena = *obj.ocjena;
		
		*predmetID = *obj.predmetID;

		this->nazivPredmeta = new char[strlen(obj.nazivPredmeta) + 1];
		strcpy_s(this->nazivPredmeta, strlen(obj.nazivPredmeta) + 1, obj.nazivPredmeta);

		this->profBr = obj.profBr;
		
		for (int i=0; i<profBr; i++)
		{ 
			this->nazivPredavaca[i] = new char[strlen(obj.nazivPredavaca[i]) + 1];
			strcpy_s(this->nazivPredavaca[i], strlen(obj.nazivPredavaca[i]) + 1, obj.nazivPredavaca[i]);
		}
		
		return *this;
	}
}

std::ostream& operator<<(std::ostream& os, PolozeniPredmet& obj)
{
	os << "Predmet " << obj.nazivPredmeta << " je polozen " << *obj.datumPolaganja << " sa ocjenom "
		<< *obj.ocjena;
	return os;
}