#pragma once

class Oblik
{
public:
	virtual double getP() const;
	virtual double getZ() const;
	virtual const char* getIme() const=0;
	virtual void print()=0;
};

double Oblik::getP() const
{
	return 0;
}

double Oblik::getZ() const
{
	return 0;
}