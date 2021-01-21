#pragma once

class iznimka
{
	char* poruka;
public:
	iznimka(const char* poruka)
	{
		this->poruka = new char[strlen(poruka) + 1];
		strcpy_s(this->poruka, strlen(poruka) + 1, poruka);
	}

	const char* getPoruka()
	{
		return poruka;
	}
};