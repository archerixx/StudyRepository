#pragma once
#include "Zaposlenik.h"

class RadnikNaSat : virtual public Zaposleni
{
private: 
	double iznos; //po satu
	double sati; //sati rada u sedmici
public:
	RadnikNaSat(double iznos, double sati)
	{
		this->iznos = iznos;
		this->sati = sati;
	}
	
	void setSatnica(double iznos)
	{
		this->iznos = iznos;
	}
	void setSati(double sati)
	{
		this->sati = sati;
	}
	virtual double Zarada() const
	{
		return iznos * sati;
	}
	
	double getSati() const
	{
		return sati;
	}

	virtual void print() const // predefinisana funkcija bazne klase
	{
		std::cout << "\nRadnikNaSat::print() izvrsava\n";
		Zaposleni::print(); // funkcija print iz bazne klase
		std::cout << " je radnik na sat sa platom od: " << Zarada() << "KM\n";
	}
};
