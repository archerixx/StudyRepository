#pragma once

#include "Baza.h"	

class Tacka :public Oblik
{
protected:
	double x, y;
public:
	Tacka(double x = 0, double y = 0)
	{
		this->x = x;
		this->y = y;
	}
	void print() final
	{
		std::cout << x << " " << y;
	}
	virtual const char* getIme()const
	{
		return "Tacka";
	}
};