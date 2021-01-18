#pragma once

class Datum {

private:
	int dan;
	int mjesec;
	int godina;
	bool ispravanDatum(int d, int m, int g) const;
	bool prestupnaGodina(int g) const;

public:
	//Datum(int d=1, int m = 1, int g = 2000) :dan(15),mjesec(12),godina(2000) {};
	Datum(int d=10, int m=2, int g=2000);
	//Datum();
	Datum(Datum& org);

	void napravi(int d, int m, int g, bool& err);
	void postaviDan(int d, bool& err);
	void postaviMjesec(int m, bool& err);
	void postaviGodinu(int g, bool& err);
	
	int uzmiDan() const;
	int uzmiMjesec() const;
	int uzmiGodinu() const;

	void kopiraj(const Datum& d);
	
	bool jednako(const Datum& d) const;

	int getBrojDana(Datum date);
};