#pragma once
#include "Krug.h"
#include <iostream>

using namespace std;

class cilindar : public krug
{
	friend std::ostream& operator<<(std::ostream& os, const cilindar& cili)
	{
		os << static_cast<krug>(cili) << "\nVisina= " << cili.visina;
		return	os;
	}
protected:
	float visina;
public:
	cilindar(float visina, float radius, double x, double y) :krug(radius, x, y)
	{
		setVisina(visina);
	}
	void setVisina(double visina)
	{
		this->visina = visina;
	}
	float getVisina() const
	{
		return visina;
	}
	float povrsina() const
	{
		return krug::getPovrsina()*2 + 2 * 3.14 * radius * visina;
	}
	float volumen() const
	{
		return krug::getPovrsina() * ( visina);
	}

	
};