//#pragma once
#ifndef header_h
#define header_h



struct Figura{
	int ID;
	char* nazivFigure;
	float* visinaFigure;
};

struct Datum {
	int mjesec;
	int godina;
};


void neparniNiz(double**, int, int);
void ispisNiz(double**, int, int);
void unos(Figura**, int, int);
float* prosjekVisine(Figura**, int, int);

#endif // !header.h