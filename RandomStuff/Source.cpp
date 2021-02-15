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
<<<<<<< Updated upstream
=======
*/

void mjes(int& m);
bool provjera(int niz[], int vel, int broj);

void getV(const vector<vector<int>>& v)
{
	for (size_t i = 0; i < v.size(); i++)
		cout << i << " ";

	cout << endl;

	size_t sum = 0;
	for (const vector<int>& i : v) {
		sum += i.size();
	}
	cout << sum/v.size() << endl;
}
>>>>>>> Stashed changes

double UnesiKolicinu()
{
	for (;;)
	{
		double kolicina;
		cout << "Unesi: ";
		cin >> kolicina;
		bool dobar_unos = cin && kolicina >= 0;
		if (!cin) cin.clear();
		cin.ignore(1000, '\n');
		if (dobar_unos) return kolicina;
		cout << "Neispravno. ";
	}
}

/*
void sabirciBroja(int n, int k)
{
	static int niz[100], index(0);
	if (k == 1)
	{
		for (int i = 0; i < index; i++)
			cout << niz[i] << "+";
		cout << n << endl;
	}
	else
	{
		for (int i = 1; i <= n -k+1; i++)
		{
			niz[index] = i;
			index++;
			sabirciBroja(n - i, k - 1);
			index--;
		}
	}
}
*/
void premutacija(int n, int k)
{
	static int niz[100], index(0);
	if (k == 1)
	{
		if (provjera(niz, index, n))
		{ 
		for (int i = 0; i < index; i++)
			cout << niz[i] << ",";
		cout << n << endl;
		}
	}
	else
	{
		for (int i = 1; i <= n - k + 1; i++)
		{
			if (provjera(niz, index, i))
			{
				niz[index] = i;
			
			index++;
			premutacija(n - i, k - 1);
			index--;
			}
		}
	}
}

bool provjera(int niz[], int vel, int broj)
{
	for (int i=0; i < vel+1; i++)
	{
		if (niz[i]==broj)
			return false;
	}
	return true;
}

// {1,2,3},{1,3,2},{2,1,3},{2,3,1},{3,1,2},{3,2,1}

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
<<<<<<< Updated upstream
=======
	*/
	/*
//	int m;
//	mjes(m);
	
	//const int& a = 5;
	//cout << a;

	//const int h = 5;
	//const int w = 3;
	//vector<vector<int>> v(h, vector<int>(w));
	//getV(v);
	*/
	/*
	//cout << UnesiKolicinu();
	
	char a;
	//cin.get(a);
	cin >> a;
	bool dobar_unos = cin || a==4;// && a >= 0;

	bool losUnos = !cin;
	if (losUnos)
		cout << "treba opet";

	if (dobar_unos)
		cout << "oke";
	else
		cout << "not";

	cout << endl << a;
	*/
	/*
	bool a = false;

	if (a == true)
		cout << "oke";
	else if(!a)
		cout << "it is true?";
		*/

	//int broj = 6, brojSabiraka=3;
	//sabirciBroja(broj, brojSabiraka);

	int sab = 4, broj=0;
	for (int b = 1; b <= sab; b++)
		broj += b;
	premutacija(broj, sab);
}

void mjes(int& m)
{
	cout << "Unes: ";
	while (1)
	{
		cin >> m;
		if (m >= 1 && m <= 12)
			return;
		cout << "Neispravan unos ";
		if (!cin) cin.clear();
		cin.ignore(100000000, '\n');
	}
>>>>>>> Stashed changes
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