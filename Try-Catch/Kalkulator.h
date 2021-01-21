#pragma once
#include <exception>

class NedozvoljenRacun
{
private:
	char* poruka;
public:
	NedozvoljenRacun(const char* poruka="Nedozvoljena operacija")
	{
		this->poruka = new char[strlen(poruka) + 1];
		strcpy_s(this->poruka, strlen(poruka) + 1, poruka);
	}
	
	const char* getPoruka()
	{
		return poruka;
	}
};

class NegativanKorjen: public NedozvoljenRacun
{
private:
	char* text;
public:
	NegativanKorjen(const char* text, const char* poruka):NedozvoljenRacun(poruka)
	{
		this->text = new char[strlen(text) + 1];
		strcpy_s(this->text, strlen(text) + 1, text);
	}

	const char* getText()
	{
		return text;
	}
};

class DijeljenjeSaNulom: public NedozvoljenRacun
{
private: 
	double dijeljenik;
public:
	DijeljenjeSaNulom(double dijeljenik, const char * poruka):NedozvoljenRacun(poruka)
	{
		this->dijeljenik = dijeljenik;
	}
	double getDijeljenik() const
	{
		return dijeljenik;
	}
};

class LosaOperacija
{
private:
	int linijaCoda;
	char lokacija[100];
	char datum[100];
	char vrijeme[100];
	char poruka[100];
	char funkcija[100];
public:
	LosaOperacija(int linija, const char* lokacija, const char* datum, const char* vrijeme, const char* poruka, const char* funkcija)
	{
		linijaCoda = linija;
		strcpy_s(this->vrijeme, 100, vrijeme);
		strcpy_s(this->datum, 100, datum);
		strcpy_s(this->lokacija, 100, lokacija);
		strcpy_s(this->poruka, 100, poruka);
		strcpy_s(this->funkcija, 100, funkcija);
	}
	friend std::ostream& operator<<(std::ostream& os, LosaOperacija& obj);
	
};

std::ostream& operator<<(std::ostream& os, LosaOperacija& obj)
{
	os << "Vrijeme: " << obj.datum << " " << obj.vrijeme << "\nFile: " << obj.lokacija << std::endl;
	os << "Linija coda: " << obj.linijaCoda << "\nFunkcija: " << obj.funkcija << "\nGreska: " << obj.poruka << std::endl;
	return os;
}

class Kalk
{
private:
	double suma;
public:
	Kalk(double broj=0)
	{
		this->suma = broj;
	}

	double dodaj(double broj)
	{
		suma = suma + broj;
		return suma;
	}

	double mnozi(double broj)
	{
		suma = suma * broj;
		return suma;
	}

	double dijeli(double broj) throw (DijeljenjeSaNulom, LosaOperacija) 
		// da funkcija ne baca izuzetak: throw() ili noexcept
	{
		if (broj == 0)
			//throw DijeljenjeSaNulom(suma, "Nedozvoljena operacija dijeljenja sa nulom");
			//throw exception("Nedozvoljena operacija dijeljenja sa nulom");
			//throw (broj)
			throw LosaOperacija(__LINE__, __FILE__, __DATE__, __TIME__, "Nije dozvoljeno dijelitit sa nula", __FUNCTION__);
		suma = suma / broj;
		return suma;
	}

	double korjen()
	{
		if (suma < 0)
			throw NegativanKorjen("Negativan broj pod korjenom", "Nedozvoljena operacija korjenovanja sa negativnim brojem");
		suma = sqrt(suma);
		return suma;
	}

	double getSuma()
	{
		return suma;
	}
};
