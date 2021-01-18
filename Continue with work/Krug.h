#pragma once
#include "Tacka.h"
#include <iomanip>
#include <iostream>

using std::setiosflags;
using std::setprecision;

class krug :public tacka
{
protected:
	float radius;

public:
	krug(float radius=0, double x=0 , double y=0):tacka(x,y)
	{
		setRadius(radius);
	}
	krug(const krug& org) :tacka(org.x, org.y)
	{
		radius = org.radius;
	}
	~krug()
	{
		std::cout << "\nDesktruktor kruga";
	}


	void setRadius(float r)
	{
		this->radius = r;
	}
	float getR() const
	{
		return radius;
	}
	float getPovrsina() const
	{
		return 3.14 * radius * radius;
	}


	friend std::ostream& operator<<(std::ostream& os, const krug& k)
	{
		os << "\nCentar=" << static_cast<tacka>(k)
			<< "\nRadisu=" /*<< setiosflags(ios::fixed | ios::showpoint)*/
			<< setprecision(2) << k.radius;

		return os;
	}
};