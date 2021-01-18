#pragma once
#include "Izvedena.h"


class Krug:public Tacka
{
protected:
	double r;
public:
	Krug(double r = 3, double x=1, double y=1) :Tacka(x, y)
	{
		this->r = r;
	}
	double getP() const
	{
		return 3.14;
	}
	virtual const char* getIme() const
	{
		return "Krug";
	}
};