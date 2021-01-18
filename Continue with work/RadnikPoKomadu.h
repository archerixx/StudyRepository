#pragma once
#include "Zaposlenik.h"

class radnikPoKomadu : public Zaposleni 
{
private:
	double plata;
	double bonus;
	int kolicina;
public:
	radnikPoKomadu(double plata, double bonus, int kolicina)
	{
		this->plata = plata;
		this->bonus = bonus;
		this->kolicina = kolicina;
	}

	void setPlata(double plata)
	{
		this->plata = plata;
	}
	
	void setBonus(double bonus)
	{
		this->bonus = bonus;
	}

	void setKolicina(int kolicina)
	{
		this->kolicina = kolicina;
	}

	virtual double Zarada() const final
	{
		return kolicina*(plata + bonus);
	}

	virtual void print() const final
	{
		std::cout << "Plata " << kolicina << " ljudi je " << Zarada();
	}
};