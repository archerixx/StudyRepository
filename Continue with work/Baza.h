#pragma once

class Baza
{
protected:
	int var;
public:
	Baza(int x)
	{
		var = x;
	}
	int getData() const
	{
		return var;
	}
};