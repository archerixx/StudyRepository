#include <iostream>
#include "Test.h"
#include "Test.cpp"
#include "Zivotinje.h"

using namespace std;

/*
prem GetBroj()
{
	prem p(3);
	return p;
}
*/
/*
template <class T>
T dodaj(T a, T b)
{
	return a + b;
}
template <class T>
T poredi(T a, T b)
{
	if (a > b)
		return a;
	else
		return b;
}
*/

int main()
{
	/*
	test t(5);

	testSec newTest(3, 4.2, 5);
	test t1(3);

	t1 = t;
	cout << t1.broj;

	cout << endl << newTest.randB;

	newTest.print();
	
	cout << endl << newTest.GetA();

	cout << endl << testSec::GetA();
	*/
	/*
	prem p1 = GetBroj();
	prem pTemp(3);
	prem p2 = move(pTemp);
	*/
	/*
	Osoba o1(15, "Zera");

	Osoba o2(15, "Bera");

	if (o1 == o2)
		cout << "Isti";
	else
		cout << "Razli";
	
	Koordinate k1(1,2);
	//cin >> k1;
	//cout << k1;

	Koordinate k2(3, 4);
	//Koordinate k3((++k2));

	Koordinate k4 = k1 + k2;

	cout << k4.getX() << endl << k4.getY();
	*/
	/*
	FITs f1("Zera");
	FITs f2("Lelaj");
	

	//FITs f3 = f1 + f2;
	FITs f3 = f1 + f2;
	
	cout << f3.getT();

	cout << endl << f3();

	FITs f4("temp");
	f4 += f2;

	cout << endl << f4.getT();
	
	cout << endl << f1[1];

	cout << endl << f1;

	cout << endl << f1["Hmm"];

	cout << endl << f1[1];

	cout << endl <<   f1.operator[](2);

	Koordinate k1(1,2);
	Koordinate k2(3, 4);

	Koordinate k3 = k1 + k2;

	cout << endl << k3.getX();

	if (f1 == f2)
		cout << endl << "isti";
	else
		cout << endl << "nisu";
	*/

	//cout << dodaj(1, 3);
	//cout << poredi("a", "b");
	//cout << poredi('a', 'b');
	/*
	
	test<int> t1(5);

	t1.add(5);
	t1.add(2);
	t1.add(7);
	t1.add(1);
	t1.add(4);

	cout << t1;

	test<int> t2=t1;
	cout << endl << t2;

	cout << endl << t1[2];
	
	//t1.sortirajMoj();
	t1.sortN1();

	cout << endl << t1;
	
	Zivotinja z1;
	Zivotinja z2("Macka", 10);
	Zivotinja z3("Pas", 3);

	cout << endl << z2;

	if (z3 < z2)
		cout << z3;
	else
		cout << z2;

	cin >> z1;

	cout << endl << z1;
	////////////////

	test<int> t1(5);
	//test<Zivotinja> t2(2);

	t1.add(124);
	t1.add(24);
	t1.add(421);
	t1.add(42);
	t1.add(74);

	t1.sortirajMoj();

	cout << t1 << endl;

	

	//Zivotinja z1;
	
	//Kol<Zivotinja<int>> k1(2);
	*/

	//Kol<int> k1;
	testKol *k2 = new testKol;


	Kol<testKol> k3;
	cout << endl << k3.vel.broj;
	k3.add();
	cout << endl << k3.vel.broj;

	test<Zivotinja> *t1;

	Zivotinja z1;
	Zivotinja z2;

	//t1->add(z1);
	//t1->add(z2);

}