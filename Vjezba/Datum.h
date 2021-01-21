#pragma once

class Datum
{
public:
	Datum(int dan=1, int mjesec=1, int godina=1900);
	~Datum();

	void setDatum(int dan, int mjesec, int godina);

	bool operator==(Datum& obj);
	Datum& operator=(Datum& obj);


	friend std::ostream& operator<<(std::ostream& os, Datum& obj);

private:
	int * dan, *mjesec, *godina;
};

Datum::Datum(int dan, int mjesec, int godina)
{
	this->dan = new int;
	*this->dan = dan;

	this->mjesec = new int;
	*this->mjesec = mjesec;

	this->godina = new int;
	*this->godina = godina;
}

Datum::~Datum()
{
	delete dan, mjesec, godina;
}

std::ostream& operator<<(std::ostream& os, Datum& obj)
{
	os << "Datum: " << *obj.dan << "." << *obj.mjesec << "." << *obj.godina;
	return os;
}

void Datum::setDatum(int dan, int mjesec, int godina)
{
	this->dan = new int;
	*this->dan = dan;

	this->mjesec = new int;
	*this->mjesec = mjesec;

	this->godina = new int;
	*this->godina = godina;
}

bool Datum::operator==(Datum& obj)
{
	if (*dan == *obj.dan && *mjesec == *obj.mjesec && *godina == *obj.godina)
		return true;
	else
		return false;
}

Datum& Datum::operator=(Datum& obj)
{
	if (*this == obj)
		return *this;
	else
	{
		delete dan, mjesec, godina;

		dan = obj.dan;
		mjesec = obj.mjesec;
		godina = obj.godina;

		return *this;
	}

}
