#pragma once
#pragma warning(disable:4996)


class Zivotinja
{
private:
	char* vrsta;
	int* tezina;
public:
	Zivotinja();
	//Zivotinja(const char* vrsta, int tezina);
	~Zivotinja();

	bool operator<(const Zivotinja&);
	Zivotinja operator=(const Zivotinja&);

	friend std::ostream& operator<<(std::ostream& os, const Zivotinja& obj);
	friend std::istream& operator>>(std::istream& is, const Zivotinja& obj);
};
