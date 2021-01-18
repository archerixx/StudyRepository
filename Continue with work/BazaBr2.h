#pragma once

class bazaBr2
{
protected:
	char slovo;
public:
	bazaBr2(char c)
	{
		slovo = c;
	}
	char getData() const
	{
		return slovo;
	}
};