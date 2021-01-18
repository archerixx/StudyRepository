#pragma once
#include "Baza.h"
#include "BazaBr2.h"

class inh:public Baza, public bazaBr2
{
private:
	double broj;
public:
	inh(double broj, int var, char slovo) :Baza(var), bazaBr2(slovo)
	{
		this->broj = broj;
	}
	double getData() const
	{
		return broj;
	}
	double getBroj() const
	{
		return broj * broj;
	}
	friend std::ostream& operator<<(std::ostream& os, const inh& obj)
	{
		os << "\nBroj iz inh: " << obj.broj << "\nBroj iz baze1: " << obj.var
			<< "\nSlovo iz baze2: " << obj.slovo << endl;
		return os;
	}
};