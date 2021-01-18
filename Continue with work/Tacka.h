#pragma once
#include <iostream>
using namespace std;


class tacka
{
protected:
	double x;
	double y;

public:
	tacka(double x = 0, double y = 0)
	{
		this->x = x;
		this->y = y;
		//krace bi bilo da iskoristimo setTacka(x,y); funkciju
	}
	~tacka()
	{
		std::cout << "\ndestruktor tacke";
	}
	void setTacka(double x, double y)
	{
		this->x = x;
		this->y = y;
	}

	double getX() const
	{
		return x;
	}
	double getY() const
	{
		return y;
	}

	friend std::ostream& operator<<(std::ostream& os, const tacka& t)
	{
		os << "\nx:" << t.x << " y:" << t.y;
		return os;
	}
};