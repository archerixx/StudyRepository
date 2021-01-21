#pragma once
#include "PolozeniPredmet.h"

template <class T>
class Kolekcija
{
private:
	T* elementi;
	int max;
	int trenutno;
public:
	Kolekcija(int max = 10);
	~Kolekcija();

	bool addElement(T& elem);
	bool removeElement(T& elem);

	T* operator[] (int lokacija)
	{
		if (lokacija >= 0 && lokacija < trenutno)
			return &elementi[lokacija];
		return nullptr;
	}

	int getTrenutno()
	{
		return trenutno;
	}

	template <class M>
	friend std::ostream& operator<<(std::ostream& os, Kolekcija<M>& obj);
};

template<class T>
inline Kolekcija<T>::Kolekcija(int max)
{
	this->max = max;
	trenutno = 0;
	elementi = new T[this->max];
}

template<class T>
inline Kolekcija<T>::~Kolekcija()
{
	delete[] elementi;
	elementi = nullptr;
}

template<class T>
inline bool Kolekcija<T>::addElement(T& elem)
{
	for (int i = 0; i < this->trenutno; i++)
		if (elem == this->elementi[i])
			return false;
	if (this->trenutno == this->max)
	{
		this->max += 5;
		T* temp = new T[this->max];
		for (int i = 0; i < this->trenutno; i++)
			temp[i] = this->elementi[i];
		delete[] this->elementi;
		this->elementi = temp;
	}
	this->elementi[this->trenutno] = elem;
	this->trenutno++;
	return true;
}

template<class T>
inline bool Kolekcija<T>::removeElement(T& elem)
{
	for (int i=0; i< trenutno; i++)
		if (elem == elementi[i])
		{ 
			for (int j = i; j < trenutno - 1; j++)
			{
				elementi[j] = elementi[j + 1];
			}
			std::cout << std::endl;
			trenutno--;
			return true;
		}
	return false;
}

template<class M>
std::ostream& operator<<(std::ostream& os, Kolekcija<M>& obj)
{
	for (int i = 0; i < obj.trenutno; i++)
		os << obj.elementi[i] << "\n";
	return os;
}

