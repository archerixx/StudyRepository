#include <iostream>
#include "Test.h"


using namespace std;

/*
test::test(int b)
{
	broj = b;
}

int testSec::a = 1;

testSec::testSec(float randB, float cijena, int b):t1(b), c(cijena), aID(a++)
{
	this->cijena = cijena;
	this->randB = randB;

}

void testSec::print()
{
	cout << "\nID" << aID;
	cout << "\nCijena" << cijena;
	cout << "\nRef na cijenu" << c;
	cout << "\nBroj" << t1.broj;
}

int testSec::GetA()
{
	return a;
}

prem::prem(int b)
{
	*broj = b;
}

prem::prem(prem& org)
{
	broj = new int;
	*broj = *org.broj;
}

prem::prem(prem&& org)
{
	broj = org.broj;
	org.broj = nullptr;
}

prem::~prem()
{
	delete broj;
	broj = nullptr;
}
*/
/*
Osoba::Osoba(int broj, const char * ime)
{
	this->broj = new int;
	*this->broj = broj;

	this->ime = new char[strlen(ime)+1];
	strcpy_s(this->ime, strlen(ime) + 1, ime);

}

Osoba::Osoba(Osoba& org)
{
	this->broj = new int;
	this->ime = new char[strlen(org.ime)+1];

	*this->broj = *org.broj;
	strcpy_s(this->ime, strlen(org.ime) + 1, org.ime);
}

Osoba& Osoba::operator=(const Osoba& org)
{
	if (this != &org)
	{
		delete[] ime;
		delete broj;
	}
	
	ime = new char[strlen(org.ime + 1) + 1];
	strcpy_s(ime, strlen(org.ime + 1) + 1, org.ime);
	
	broj = new int;
	*broj = *org.broj;
	
	return *this;
}

bool Osoba::operator==(const Osoba& compare) const
{
	if (strcmp(ime, compare.ime) == 0 && *broj == *compare.broj)
		return true;
	return false;

//krace se moze zapisati:
	//return (strcmp(ime, compare.ime) == 0 && broj == compare.broj)
}

Osoba::~Osoba()
{
	delete this->broj;
	delete[] this->ime;
}

*/
/*
istream& operator>>(istream& CIN, Koordinate & obj)
{
	CIN >> obj.x >> obj.y;
	return CIN;
}

ostream& operator<<(ostream& os, const Koordinate& k)
{
	cout << "x: " << k.x << "y: " << k.y;
	return os;
}

Koordinate Koordinate::operator+(Koordinate drugi)
{
	float sumX = x + drugi.x;
	float sumY = y + drugi.y;
	return Koordinate(sumX, sumY);
}

Koordinate Koordinate::operator++()
{
	x++, y++;
	return *this;
}

Koordinate Koordinate::operator++(int)
{
	Koordinate povratni(x, y);
	x++, y++;
	return povratni;
}


FITs::FITs(const char* t)
{
	text = new char[strlen(t) + 1];
	strcpy_s(text, strlen(t) + 1, t);
}

FITs::FITs(const FITs& org)
{
	text = new char[strlen(org.text) + 1];
	strcpy_s(text, strlen(org.text) + 1, org.text);
	
}

FITs::~FITs()
{
	delete[] text;
	text = NULL;
}

FITs FITs::operator+(const FITs &drugi)
{
	/*
	char* temp = new char[strlen(text)+1];
	temp = text;
	delete[] text;
	text = new char[strlen(temp) + strlen(drugi.text)+2];
	*text = *temp + *drugi.text;
	return *this;
	strcat(text, drugi.text);
	FITs newText(text);
	return newText;
	///////
	char * temp = new char[strlen(text) + strlen(drugi.text) + 1];
	strcpy_s(temp, strlen(text) + strlen(drugi.text) + 1, text);
	strcat_s(temp, strlen(text) + strlen(drugi.text) + 1,drugi.text);

	FITs novi(temp);

	delete[] temp;

	return novi;

}

int FITs::operator()()
{
	return strlen(text);
}

FITs FITs::operator()(int start, int br)
{
	char* temp = new char(br + 1);
	char* pocetak = text + start;

	strcpy_s(temp, br + 1, pocetak);
	temp[br] = '\0'; // funkcija strcpy ne dodaje '\0' na kraju, pa se dodaje manualno (\0 je terminirajuci karakter)
	
	FITs novi(temp);
	delete []temp;
	return novi;
}

FITs FITs::operator+=(const FITs &drugi)
{
	char* temp = new char[strlen(text) + 1];
	strcpy_s(temp, strlen(text) + 1, text);
	
	delete[] text;
	text = new char[strlen(temp) + strlen(drugi.text) + 1];
	strcpy_s(text, strlen(temp) + strlen(drugi.text) + 1, temp);

	delete[] temp;
	temp = NULL;

	strcat(text, drugi.text);
	return *this;
}

bool FITs::operator==(const FITs &drugi)
{
	if (strcmp(text, drugi.text) == 0)
		return true;
	else
		return false;
}

bool FITs::operator!=(const FITs& drugi)
{
	if (text == drugi.text)
		return false;
	else
		return true;
}

char FITs::operator[](int element)
{
	return text[element];
}

char FITs::operator[](const char * rijec)
{
	return rijec[1];
}

char* FITs::getT()
{
	return text;
}

std::ostream& operator<<(std::ostream& OS, FITs& obj)
{
	cout << obj.text;
	return OS;
}
*/





template<class T>
inline test<T>::test()
{
	br = 0;
	vel = 5;
	niz = new T[this->vel];
}

template<class T>
inline test<T>::test(const test& org)
{
	this->br = org.br;
	this->vel = org.vel;
	this->niz = new T[org.vel];
	for (int i = 0; i < vel; i++)
	{
		niz[i] = org.niz[i];
	}
}

template<class T>
inline test<T>::~test()
{
	delete[] niz;
	niz = NULL;
}

template<class T>
void test<T>::add(T clan)
{
	niz[br] = clan;
	br++;
}
/*
template<class T>
inline T test<T>::operator[](int index)
{
	return niz[index];
}

template<class T>
inline void test<T>::sortirajMoj()
{
	T* temp = new T[vel];
	int t = 0;
	int min;
	int tempBr = 0;
	int tempVel = vel;
	while (tempVel != 0)
	{
		for (int i = 1; i < tempVel; i++)
		{
			if (niz[i] < niz[i - 1])
			{
				min = niz[i];
			}
			else
			{
				min = niz[i - 1];
				t = niz[i];
				niz[i] = niz[i - 1];
				niz[i - 1] = t;
			}

		}

		temp[tempBr] = min;
		if (tempVel == 1)
			temp[tempBr] = niz[0];
		tempBr++;

		tempVel = tempVel - 1;
	}


	for (int i = 0; i < tempBr; i++)
	{
		niz[i] = temp[i];
	}
}
template<class T>
inline void test<T>::sortN1()
{
	T temp;
	for (int i = 0; i < vel; i++)
	{
		for (int j = i + 1; j < vel; j++)
		{
			if (niz[i] > niz[j])
			{
				temp = niz[i];
				niz[i] = niz[j];
				niz[j] = temp;
			}
		}
	}
}
*/