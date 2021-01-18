#pragma once
#include <exception>

class NedozvoljenRacun
{
private:
	char* poruka;
public:
	NedozvoljenRacun(const char* poruka="Nedozvoljena operacija")
	{
		this->poruka = new char[strlen(poruka) + 1];
		strcpy_s(this->poruka, strlen(poruka) + 1, poruka);
	}
	
	const char* getPoruka()
	{
		return poruka;
	}
};

class NegativanKorjen: public NedozvoljenRacun
{
private:
	char* text;
public:
	NegativanKorjen(const char* text, const char* poruka):NedozvoljenRacun(poruka)
	{
		this->text = new char[strlen(text) + 1];
		strcpy_s(this->text, strlen(text) + 1, text);
	}

	const char* getText()
	{
		return text;
	}
};

class DijeljenjeSaNulom: public NedozvoljenRacun
{
private: 
	double dijeljenik;
public:
	DijeljenjeSaNulom(double dijeljenik, const char * poruka):NedozvoljenRacun(poruka)
	{
		this->dijeljenik = dijeljenik;
	}
	double getDijeljenik() const
	{
		return dijeljenik;
	}
};



class Kalk
{
private:
	double suma;
public:
	Kalk(double broj=0)
	{
		this->suma = broj;
	}

	double dodaj(double broj)
	{
		suma = suma + broj;
		return suma;
	}

	double mnozi(double broj)
	{
		suma = suma * broj;
		return suma;
	}

	double dijeli(double broj)
	{
		if (broj == 0)
			throw DijeljenjeSaNulom(suma, "Nedozvoljena operacija dijeljenja sa nulom");
		
		suma = suma / broj;
		return suma;
	}

	double korjen()
	{
		if (suma < 0)
			throw NegativanKorjen("Negativan broj pod korjenom", "Nedozvoljena operacija korjenovanja sa negativnim brojem");
		suma = sqrt(suma);
		return suma;
	}

	double getSuma()
	{
		return suma;
	}
};
