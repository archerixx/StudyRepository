#include <iostream>
#include "header.h"

using namespace std;

void neparniNiz(double** niz, int red, int kol)
{
	int j = 0;
	for (int i = 0; i < red; i++)
	{
		while (j != kol)
		{
			if (j % 2 == 0)
				niz[i][j] = rand() % 10 + 1;
			else
				niz[i][j] = niz[i][j - 1] / 2;
			j++;

		}
		if (kol % 2 == 0)
			j = 1;
		else
			j = 0;
	}
}
void ispisNiz(double** niz, int red, int kol)
{
	for (int i = 0; i < red; i++)
	{
		for (int j = 0; j < kol; j++)
		{
			cout << niz[i][j] << " ";
		}
		cout << endl;
	}
}

void unos(Figura** niz, int red, int kol)
{
	for (int i = 0; i < red; i++)
	{
		for (int j = 0; j < kol; j++)
		{
			//cout << "ID: ";
			//(*(*(niz + i) + j)).ID;
			//cin >> (*(*(niz+i)+j)).ID;
			//cin.ignore();
			//cout << "Naziv: ";
			//(*(*(niz + i) + j)).nazivFigure = new char[10];
			//cin.getline((*(*(niz + i) + j)).nazivFigure, 10);
			cout << "Visina: ";
			(*(*(niz + i) + j)).visinaFigure = new float;
			cin >> *(*(*(niz + i) + j)).visinaFigure;
		}
	}
}
float* prosjekVisine(Figura** niz, int red, int kol)
{
	float sum = 0;
	float br = 0;
	int temp = 0;
	for (int i = red - 1; i >= 0; i--)
	{

		for (int j = 0; j < kol; j++)
		{
			if (j > i)
			{
				if (temp % 2 == 0)
				{
					if (j % 2 == 0)
					{
						sum += *(*(*(niz + temp) + j)).visinaFigure;
						cout << "\n i je " << temp << " a j je " << j << " broj je " << *(*(*(niz + i) + j)).visinaFigure;
						cout << endl;
						br++;
					}
				}
				else
				{
					if (j % 2 != 0)
					{
						sum += *(*(*(niz + temp) + j)).visinaFigure;
						cout << "\n i je " << temp << " a j je " << j << " broj je " << *(*(*(niz + i) + j)).visinaFigure;
						cout << endl;
						br++;
					}
				}
			}
		}
		temp++;
	}
	sum = sum / br;
	return &sum;
}
