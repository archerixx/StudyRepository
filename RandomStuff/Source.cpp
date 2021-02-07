#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include <conio.h>


using namespace std;

class dani {
	string dan;
public:
	dani(string dan = "")
	{
		this->dan = dan;
	}
};

void fj(const int& a)
{
	int& y = const_cast<int&>(a);
	++y;
}

enum Dan { Pon, Uto, Sri, Cet, Pet, Sub, Ned };
void fj2(Dan dan);


double stepen(double x, int n)
{
	double p(1);
	int n1 = abs(n);
	while (n1 != 0)
	{
		if (n1 % 2 == 1)
			p *= x;
		n1 /= 2;
		x *= x;
	}
	if (n >= 0)
		return p;
	return 1 / p;
}

int main()
{
	/*
	enum radniDan{pon, uto, sri, cet, pet};
	radniDan dan;
	dan = pet;
	cout << dan;
	*/
	char a = 'a';
	//fj(a);

	//fj2(Sri);

	//cout << stepen(2, 10);

	//getch() - ceka pritisak na tipku
	while (a == '\n')
	{ 
		if (_getch())
		{ 
			cin >> a;
			 cout << "\nPritisak na tipku\n";
		}
	}
}

void fj2(Dan dan)
{
	Dan pocetni_Dan = Sri;
	cout << " P U S C P S N\n";
	cout << setw(2 * pocetni_Dan) << "";

	for (int j = 1; j <= 7; j++)
	{
		cout << setw(2) << j;
		if (pocetni_Dan != Ned)
			pocetni_Dan = Dan(pocetni_Dan + 1);
		else
		{
			pocetni_Dan = Pon;
			cout << endl;
		}
	}
}