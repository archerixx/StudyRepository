#pragma once
#include "Zaposlenik.h"


class Direktor :virtual public Zaposleni
{
private:
	double sedmicaPlata;
public:
	Direktor(double sedmicnaPlata = 0)
	{
		this->sedmicaPlata = sedmicnaPlata;
	}
	void setSedmicnaPlata(double sedmicaPlata)
	{
		this->sedmicaPlata = sedmicaPlata;
	}
	
	double getPlata()
	{
		return sedmicaPlata;
	}

	virtual double Zarada() const
	{
		return sedmicaPlata;
	}
	virtual void print() const
	{
		std::cout << "Sedmica plata Direktroa ";
		Zaposleni::print();
		cout << " je: " << sedmicaPlata;
	}
};
