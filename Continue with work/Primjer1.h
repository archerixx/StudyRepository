#pragma once

class prTacka
{
protected:
	int x, y;
public:
	prTacka(int x, int y)
	{
		this->x = x;
		this->y = y;
		std::cout << "Tacka konst: radius je: " << "[" << x << "," << y << "]" << std::endl;
	}
	~prTacka()
	{
		std::cout << "prTacka destrukro:" << "[" << x << "," << y << "]" << std::endl;
	}
};

class prKrug : public prTacka
{
private:
	double r;
public:
	prKrug(double r, int x, int y) :prTacka(x, y)
	{
		this->r = r;
		std::cout << "Krug konst: radius je: " << r << "[" << x << "," << y << "]" << std::endl;
	}
	~prKrug()
	{
		std::cout << "Krug destr: radius je: " << r << "[" << x << "," << y << "]" << std::endl;
	}
};