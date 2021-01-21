#pragma once

class Predmet
{
public:
	Predmet(int ID, const char* nazivPredmeta, const char* nazivPredavaca);
	Predmet(Predmet& org);
	~Predmet();
	
	int getPredmetID()
	{
		return *predmetID;
	}

	void dodajPredavaca(const char* imePredavaca);

	friend std::ostream& operator<<(std::ostream& os, Predmet& obj);

protected:
	int* predmetID;
	char* nazivPredmeta;
	char* nazivPredavaca[5];
	int profBr;
};

Predmet::Predmet(int ID, const char* nazivPredmeta, const char* nazivPredavaca)
{
	predmetID = new int;
	*predmetID = ID;
	
	this->nazivPredmeta = new char[strlen(nazivPredmeta) + 1];
	strcpy_s(this->nazivPredmeta, strlen(nazivPredmeta) + 1, nazivPredmeta);
	this->profBr = 0;
	this->nazivPredavaca[profBr] = new char[strlen(nazivPredavaca) + 1];
	strcpy_s(this->nazivPredavaca[profBr], strlen(nazivPredavaca) + 1, nazivPredavaca);

	profBr++;
}

inline Predmet::Predmet(Predmet& org)
{
	this->predmetID = org.predmetID;

	this->nazivPredmeta = new char[strlen(org.nazivPredmeta) + 1];
	strcpy_s(this->nazivPredmeta, strlen(org.nazivPredmeta) + 1, org.nazivPredmeta);

	profBr = org.profBr;

	for (int i = 0; i < profBr; i++)
	{
		this->nazivPredavaca[i] = new char[strlen(org.nazivPredavaca[i]) + 1];
		strcpy_s(this->nazivPredavaca[i], strlen(org.nazivPredavaca[i]) + 1, org.nazivPredavaca[i]);
	}
	
	
}

Predmet::~Predmet()
{
	delete predmetID;
	delete[] nazivPredmeta;
	for (int i=0; i<profBr; i++)
		delete[] nazivPredavaca[i];
}


void Predmet::dodajPredavaca(const char* imePredavaca)
{
	if (profBr == 5)
		//throw exception("Prekoracen broj predavaca");
		std::cout << "k";
	for (int i = 0; i < profBr; i++)
	{
		if (strcmp(nazivPredavaca[i], imePredavaca) == 0)
			//throw exception("Predavac vec postoji");
			std::cout << "k";
	}
	nazivPredavaca[profBr] = new char[strlen(imePredavaca) + 1];
	strcpy_s(nazivPredavaca[profBr], strlen(imePredavaca) + 1, imePredavaca);
	profBr++;
}

std::ostream& operator<<(std::ostream& os, Predmet& obj)
{
	os << "Predmet ID: " << *obj.predmetID
		<< "\nImena predavaca za predmet " << obj.nazivPredmeta << " su ";
	for (int i=0; i<obj.profBr;i++)
		os << obj.nazivPredavaca[i] << " ";
	os << "\n";
	return os;
}