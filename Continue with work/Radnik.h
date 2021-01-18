#pragma once
#include "Zaposlenik.h"
#include "RadnikNaSat.h"
#include "Direktor.h"

class radnik : public RadnikNaSat, public Direktor
{
private:
	char* posao;
	double novac;
public:
	radnik(const char* posao, double novac,const  char* ime,const char* prezime, double sedmicnaPlata, double iznos, double sati):Zaposleni(ime, prezime), Direktor(sedmicnaPlata), RadnikNaSat(iznos, sati)
	{
		this->posao = new char[strlen(posao) + 1];
		strcpy_s(this->posao, strlen(posao) + 1, posao);

		this->novac = novac;
	}

	virtual double Zarada() const final
	{
		return novac;
	}
	virtual void print() const final
	{
		std::cout << "Prosjecna plata za radnika ";
		Zaposleni::print();
		cout << " koji radi posao " << posao << " je " << novac*RadnikNaSat::getSati();
	}
};
