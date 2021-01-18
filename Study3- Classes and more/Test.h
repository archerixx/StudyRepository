#pragma once
#pragma warning(disable:4996)

/*
class test
{
public:
	int broj;
	test(int b);
};

class testSec
{
public:
	test t1;
	float cijena;
	float randB;
	float& c;
	const int aID;
	static int a;

	testSec(float randB, float cijena, int b);
	void print();
	static int GetA();
};

class prem
{
public:
	int* broj;
	prem(int b);
	prem(prem& org);
	prem(prem&& org);
	~prem();
};

class testClan
{
public:
	char ime[10];
	char prezime[15];

	testClan(const char ime[15]);
};
*/
/*
class Osoba
{
private: 
	int * broj;
	char* ime;
public:
	Osoba(int, const char*);
	Osoba(Osoba& org);

	Osoba& operator=(const Osoba& org);
	bool operator==(const Osoba& compare) const;

	~Osoba();
};
*/
/*
class Koordinate
	{
	private:
		float x;
		float y;
		
	public:
		Koordinate(float x = 0, float y = 0)
		{
			this->x = x;
			this->y = y;
		}
		friend std::ostream& operator<<(std::ostream& os, const Koordinate& k); // mora se korsiting
		// ili "using namespace std" ili koristi prefixi "std::" za ovaj overload operator
		
		friend std::istream & operator>>(std::istream &, Koordinate &);

		Koordinate operator+(Koordinate drugi);

		Koordinate operator++();
		Koordinate operator++(int);


		float getX()
		{
			return x;
		}
		float getY()
		{
			return y;
		}
};


class FITs
{
private: 
	char* text;
public:
	FITs(const char* t);
	FITs(const FITs& org);
	~FITs();

	FITs operator+(const FITs &drugi);
	int operator()();
	FITs operator()(int start, int br);
	FITs operator+=(const FITs &drugi);
	bool operator==(const FITs &drugi);
	bool operator!=(const FITs& drugi);

	char operator[](int element);
	char operator[](const char* rijec); // probni, izgleda da se moze overload operator
	friend std::ostream& operator<<(std::ostream&, FITs&);

	char* getT();
};
*/


template <class T>

class test
{
private:
	T* niz;
	int vel;
	int br;
public:
	test();
	test(const test& org);
	~test();

	
	void add(T clan);
	/*
	T operator[](int index);

	template <class M>
	friend std::ostream& operator<<(std::ostream& os, const test<M>& obj);

	void sortirajMoj();
	void sortN1();
	*/
};
/*
template <class M>
std::ostream& operator<<(std::ostream& os, const test<M>& obj)
{
	for (int i = 0; i < obj.vel; i++)
		os << obj.niz[i] << " ";
	return os;
}
*/

template <class N>
class Kol
{
public:
	N vel;

	Kol()
	{
		vel.broj = 4;
	}

	void add()
	{
		vel.broj += 5;
	}

};

class testKol
{
public:
	int broj;

	testKol()
	{
		broj = 5;
	}

};
