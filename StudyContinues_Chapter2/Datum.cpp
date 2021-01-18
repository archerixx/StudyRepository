#include <iostream>
#include "Datum.h"

using namespace std;

bool Datum::ispravanDatum(int d, int m, int g) const
{
	if (g < 0)
		return false;
	if (m < 1 || m > 12)
		return false;

	int min = 1;
	int max = 31;

	if (m == 2)
	{
		if (prestupnaGodina(g))
			max = 29;
		else
			max = 28;
	}
	else if (m == 4 || m == 6 || m == 9 || m == 11)
	{
		max = 30;
	}

	if (d < min || d > max)
		return false;
	else
		return true;

}

bool Datum::prestupnaGodina(int g) const
{
	if ((g % 4 == 0) && (g % 100 != 0))
		return true;
	else
		return false;
}

void Datum::napravi(int d, int m, int g, bool& err)
{
	if (ispravanDatum(d, m, g))
	{
		dan = d;
		mjesec = m;
		godina = g;
		err = false;
	}
	else
		err = true;
}

void Datum::postaviDan(int d, bool& err)
{
	if (ispravanDatum(d, this->mjesec, this->godina))
	{
		dan = d;
		err = false;
	}
	else
		err = true;
}

void Datum::postaviMjesec(int m, bool& err)
{
	if (ispravanDatum(this->dan, m, this->godina))
	{
		mjesec = m;
		err = false;
	}
	else
		err = true;
}

void Datum::postaviGodinu(int g, bool& err)
{
	if (ispravanDatum(this->dan, this->mjesec, g))
	{
		godina = g;
		err = false;
	}
	else
		err = true;
}

int Datum::uzmiDan() const
{
	return this->dan;
}

int Datum::uzmiMjesec() const
{
	return this->mjesec;
}

int Datum::uzmiGodinu() const
{
	return godina; // testiram
}

void Datum::kopiraj(const Datum& d)
{
	this->dan = d.dan;
	this->mjesec = d.mjesec;
	this->godina = d.godina;
}

bool Datum::jednako(const Datum& d) const
{
	if (this->dan == d.dan && this->mjesec == d.mjesec && this->godina == d.godina)
		return true;
	else
		return false;
}
int Datum::getBrojDana(Datum date)
{
	int temp=0, tempM=0, tempG=0;
	date.mjesec--;
	date.godina--;

	while(date.mjesec!=0)
	{ 
		if (date.mjesec == 2)
		{
			if (prestupnaGodina(date.godina))
				tempM += 29;
			else
				tempM += 28;
		}
		else if (date.mjesec == 4 || date.mjesec == 6 || date.mjesec == 9 || date.mjesec == 11)
		{
			tempM += 30;
		}
		else
			tempM += 31;

		date.mjesec--;
	}
	while (date.godina != 0)
	{
		if (prestupnaGodina(date.godina))
			tempG += 366;
		else
			tempG += 365;
		date.godina--;
	}

	temp = date.dan + tempM + tempG;
	return temp;
}
/*
Datum::Datum(int d=1, int m=1, int g=1990)
{
	if (ispravanDatum(d, m, g))
	{
		dan = d;
		mjesec = m;
		godina = g;
	}
}
Datum::Datum()
{
	dan = mjesec = 1;
	godina = 2020;
}
*/

//Datum::Datum(int d, int m, int g) :dan(15), mjesec(12), godina(2000) {};

Datum::Datum(int d, int m, int g)
{
	if (ispravanDatum(d, m, g))
	{
		dan = d;
		mjesec = m;
		godina = g;
	}
}

Datum::Datum(Datum& org)
{
	dan = org.dan;
	mjesec = org.mjesec;
	godina = org.godina;
}
