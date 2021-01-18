#pragma once

using namespace std;

class Zaposleni
{
private:
	char* ime;
	char* prezime;
public:
	Zaposleni(const char* ime = "Zerin", const char* prezime= "Tursic")
	{
		this->ime = new char[strlen(ime) + 1];
		strcpy_s(this->ime, strlen(ime) + 1, ime);

		this->prezime = new char[strlen(prezime) + 1];
		strcpy_s(this->prezime, strlen(prezime) + 1, prezime);
	}
	virtual double Zarada() const = 0;
	
	virtual void print() const
	{
		cout << ime << " " << prezime;
	}

	char* getIme()
	{
		return ime;
	}

	char* getPrezime()
	{
		return prezime;
	}

	virtual ~Zaposleni()
	{
		delete[] ime;
		ime = nullptr;
		delete[] prezime;
		prezime = nullptr;
	}
};