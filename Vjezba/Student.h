#pragma once
#include "PolozeniPredmet.h"
#include "Kolekcija.h"

class Student
{
private:
	int brojIndeksa;
	char* imePrezime;
	Kolekcija<PolozeniPredmet> polozeni;
public:
	Student(int brojIndeksa, const char* imePrezime);
	~Student();

	bool dodajPolozeni(int predmetID, const char* nazivPredmeta, const char* nazivPredavaca, Datum* date, int ocjena);
	bool UkloniPredmetPoID(int ID);

	friend std::ostream& operator<<(std::ostream& os, Student& obj);
};

Student::Student(int brojIndeksa, const char* imePrezime)
{
	this->brojIndeksa = brojIndeksa;

	this->imePrezime = new char[strlen(imePrezime) + 1];
	strcpy_s(this->imePrezime, strlen(imePrezime) + 1, imePrezime);
}

inline Student::~Student()
{
	delete[] imePrezime;
	imePrezime = nullptr;
}

bool Student::dodajPolozeni(int predmetID, const char* nazivPredmeta, const char* nazivPredavaca, Datum* date, int ocjena)
{
	PolozeniPredmet* temp = new PolozeniPredmet(predmetID, nazivPredmeta, nazivPredavaca, date, ocjena);
	return polozeni.addElement(*temp);
}

inline bool Student::UkloniPredmetPoID(int ID)
{
	PolozeniPredmet* temp = nullptr;
	for (int i = 0; i < polozeni.getTrenutno(); i++)
	{
		temp = polozeni[i];
		if (temp != nullptr)
		{
			if (temp->getPredmetID() == ID)
			{
				polozeni.removeElement(*temp);
				return true;
			}
		}
	}
	return false;
}

std::ostream& operator<<(std::ostream& os, Student& obj)
{
	os << obj.brojIndeksa << " " << obj.imePrezime << "\n";
	os << obj.polozeni << "\n";
	return os;
}
