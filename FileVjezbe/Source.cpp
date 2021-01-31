#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const char* crt = "\n==============================================\n";

struct Student
{
	int id;
	char ime[10];
};
//funckija za unos i ispis atributa objekta
void unos(Student & s){
	cout << "Unesite ime i prezime: \n";
	cin.getline(s.ime, 10);

	cout << "ID studenta: \n";
	cin >> s.id;
	cin.ignore();
}
void ispis(Student& s)
{
	cout << "Ime studenta: " << s.ime << endl;
	cout << "ID studenta " << s.id << endl;
}


//predzanje file vjezbe
/*
void UnosSadrzaja(const char* fileName)
{
	cout << crt << "Unos sadrzaja: " << crt;
	string tekst;

	ofstream upis(fileName);
	if (upis.fail())
	{
		cout << "\nFAIL!\n";
	}
	else
	{
		cout << "Unesite tekst koji zelite spremiti u file: \n";
		getline(cin, tekst);
		upis << tekst;
		cout << crt << "Sadrzaj je uspian u file uspjesno! " << crt;
	}
	upis.close();
}
void PrikazSadrzaja(const char* fileName)
{
	cout << crt << "Ispis sadrzaja: " << crt;
	char znak;
	//koristimo ios::_Nocreate mod - file mora postojati
	ifstream ispis(fileName);
	if (ispis.fail())
		cout << "\nFAIL\n";
	else
	{
		cout << crt << "File " << fileName << " sadrzi: " << crt;
		while (ispis.get(znak))
			cout << znak;
		cout << crt << "Sadrzaj file uspjesno ispisan" << crt;
	}
	ispis.close();
}
void dodavanjeSadrzaja(const char* fileName)
{
	cout << crt << "Dodavanje sadrzaja: " << crt;
	string tekst;
	//file mora postojati pa se koristi - ios::_Nocreate
	//da bi novi sadrzaj bio dodan na kraj file-a koristi se- ios::app
	ofstream dodaj(fileName, ios::_Nocreate | ios::app);
	if (dodaj.fail())
		cout << "\nFAIL\n";
	else
	{
		cout << "Upisite tekst koji zelite dodati: \n";
		getline(cin, tekst);
		dodaj << "\n";
		dodaj << tekst;
		cout << crt << "Sadrzaj je uspjesno dodan" << crt;
	}
	dodaj.close();
}
void kopiranjeSadrzaja(const char* fileName)
{
	cout << crt << "Kopiranje sadzraja: " << crt;
	string copyToFileName;
	char znak;
	cout << "Unesite novo ime file-a u koji zelite kopirati postojeci file sadrzaj: ";
	getline(cin, copyToFileName);
	ifstream copyFile(fileName, ios::in | ios::_Nocreate);
	//otvaram fila gdje cemo kopirati
	ofstream unos(copyToFileName, ios::app);
	if (!copyFile.fail())
	{
		if (!unos.fail())
		{
			while (copyFile.get(znak)) //uzimamo naredni karakter
				unos << znak; //upisujemo karakter u novi file
			cout << crt << "Sadrzaj iz file-a " << fileName << " u novi file " << copyToFileName << crt;
		}
		else
			cout << "\nFAIL\n";
	}
	else
	{
		cout << "\nFAIL\n";
	}
	copyFile.close();
	unos.close();
}
int fileSize(const char * fileName)
{
	cout << crt << "Velicina file-a: " << crt;
	ifstream ispis(fileName);
	int velicina = -1; // need to check if needs to be assigned to -1

	if (ispis.fail())
		cout << "\nFail\n";
	else
	{
		//pomjeramo pokazivac na kraj file-a
		ispis.seekg(0, ios::end);
		//ocitivama poziciju pokazivaca, sto predstavlja broj bajta
		velicina = ispis.tellg();
		cout << crt <<"Velicina fajla je: " << velicina << " bajta." << crt;
	}
	ispis.close();
	return velicina;
}
void pretragaSadrzajaChar(const char* fileName)
{
	cout << crt << "Ovdje ce se vrsiti pretraga karaktera u sadrzaju file-a: " << crt;
	char znak, trazeni;
	int ukupno(0), pronadjeni(0);

	ifstream checkFile(fileName, ios::in | ios::_Nocreate);
	cout << "Unesite znak koji zelite pretraziti: \n";
	cin >> trazeni;
	//cin.ignore(100, '\n'); //not sure if needed

	if (checkFile.fail())
		cout << "\nFAIL\n";
	else
	{
		while (checkFile.get(znak))
		{
			if (trazeni == znak)
				pronadjeni++;
			ukupno++;
		}
		cout << crt << "File " << fileName << " ima ukupno: " << ukupno << " znakova\n";
		cout << "Znakova '" << trazeni << "' u ovom tekstu ima " << pronadjeni << crt;
	}
	checkFile.fail();
}
void pretragaSadrzajaString(const char* fileName)
{
	cout << crt << "Ovdje ce se vrsiti pretraga rijeci u sadrzaju file-a: " << crt;
	ifstream ispisFile(fileName, ios::in | ios::_Nocreate);
	const int max = 100;
	char* rijec = new char[max];
	string trazena;
	int pronadjeno=0;
	getline(cin, trazena);
	int br = 0;

	if (ispisFile.fail())
		cout << "\nFail\n";
	else
	{
		while (!ispisFile.eof())
		{
			ispisFile.getline(rijec, max);
			for (int i = 0; i <= max; i++)
			{

				if (rijec[i] == trazena[0])
				{
					int temp = i;
					for (int j = 0; j <= trazena.size(); j++)
					{
						if (rijec[temp] == trazena[j])
							br++;
						temp++;
					}
				}
				else
					br = 0;

				if (br == trazena.size())
				{
					pronadjeno++;
					br = 0;
				}
			}
		}
	}
	cout << pronadjeno;
	ispisFile.close();
}
void brisanjeSadrzaja(const char* fileName)
{
	cout << crt << "Ovdje ce se vrsiti brisanje sadrzaja iz file-a: " << crt;
	ofstream fileOpen(fileName, ios::trunc);
	if (fileOpen.fail())
		cout << "\nFAIL\n";
	else
		cout << crt << "Sadrzaj file-a " << fileName << " je obrisan" << crt;
	fileOpen.close();
}
void showMenu(int& izbor)
{
	do
	{
		cout << crt << "Manipulisanje file-ovima: " << crt;
		cout << "1. Upisi sadrzaj u fajl. " << endl;
		cout << "2. Prikazi sadrzaj fajla. " << endl;
		cout << "3. Dodaj novi sadrzaj fajlu. " << endl;
		cout << "4. Kopiraj sadrzaj fajla u drugi fajl. " << endl;
		cout << "5. Pretrazuj sadrzaj fajla (karakter). " << endl; 
		cout << "6. Pretrazuj sadrzaj fajla (rijec). " << endl; 
		cout << "7. Prikazi velicinu fajla. " << endl;
		cout << "8. Brisi sadrzaj fajla. " << endl;
		cout << "9. Rad sa novim fajlom. " << endl;
		cout << "10. Izadji iz programa. " << crt; 
		cout << "Unesite vas izbor: "; 
		cin >> izbor; cin.ignore(); 
		system("cls");
	} while (izbor < 1 || izbor >10);
}
*/



int main()
{
	//unos/ispis filea
	/*
	ofstream upis; // ili upis("NewFile.txt");
	upis.open("NewFile.txt");

	//upis u file
	upis << "This is text file for this project";
	upis << "\nNewFile se nalazi u istom direktoriju kao program";

	//kraj filea
	upis.close();

	upis.open("C:\\Temp\\ProgTestFile\\TestFile.txt");
	upis << "Test new file location";
	upis.close();


	ifstream ispis;
	ispis.open("NewFile.txt");
	
	if (ispis.fail())
		cout << "Greska: Nemoguce otvoriti fajl!\n";
	else
		cout << "File sadrzi\n";

	ispis.close();
	*/
	/*
	ofstream upis("ProjectFile1.txt");
	if (upis.fail())
		cout << "Upis::Greska: File se ne moze otvoriti! \n";
	else
	{
		upis << "Univerzitet \"DzB\"\n"
			<< "FIT \n"
			<< "Sjeverni Logor 12, Mostar\n"
			<< "Tel: +38761239828\n";
	}
	upis.close();

	ifstream ispis("ProjectFile1.txt");
	if (ispis.fail())
	{
		cout << "Upis::Greska: File se ne moze otvoriti! \n";
	}
	else
	{
		char znak;
		//sve dok u File-u postoji sadrzaj, funkcija get() uzima znak po znak
		//i phranjuje ga u varrijablu znak 
		while (ispis.get(znak))
		{
			cout << znak; //ispisuje znak po znak
		}
	}
	ispis.close();
	*/

	//smjestanje naziva filea u varijablu
	/*
	const char* nazivFile = "ProjectFile2.txt";
	ofstream upis(nazivFile);
	*/
	
	//ispis pomocu nizova karaktera
	/*
	const int max = 100;
	char jedanRed[max];
	const char* nazivFile = "noviFile.txt";

	ofstream unos(nazivFile);
	if (unos.fail())
		cout <<  "Fail\n";
	else
	{
		unos << crt << "Fakultet info nauka\n";
	}
	unos.close();

	ifstream ispis(nazivFile);
	if (ispis.fail())
		cout << "Fail\n";
	else
	{
		///////////////////////
		//ispis prvog reda
		ispis.getline(jedanRed, max);
		cout << jedanRed << endl;
		//ispis drugog reda
		ispis.getline(jedanRed, max);
		cout << jedanRed << endl;
		/////////////////////
		while (!ispis.eof()) // eof() - ispisuje sve do kraja fajla, tj preuzima po jedan red teksta i pohrani ga u red (jedanRed);
		{
			ispis.getline(jedanRed, max);
			cout << jedanRed << endl;
		}
		///////////////////
		while(ispis.getline(jedanRed, max))
			cout << jedanRed << endl;
		/////////////////
	}
	ispis.close();
	*/
	
	//korisnik unosi sadzraj
	/*
	string name, text;
	int brojMjesta;
	cout << "Unesite ime filea: \n";
	getline(cin, name);

	ofstream unos(name, ios::out | ios::app); // ios:: su modovi za fstream klasu

	if (unos.fail())
		cout << "Fail!\n";
	else
	{
		cout << "Unesite neki text za file\n (unesite 'exit' kada zelite da stanete)\n";
		while (text != "exit")
		{
			getline(cin, text);
			if (text == "exit")
				break;
			unos << text + "\n";
		}		
	}
	unos.close();


	ifstream ispis(name);
	char znak;

	cout << "Pomjeri pokazivac za koliko mjesat: ";
	cin >> brojMjesta;
	ispis.seekg(brojMjesta); //pomjeranje pokazivac za brojMjesta

	if(ispis.is_open()) // provjera da li je File otvoren ili zatvoren
		while (ispis.get(znak))
		{
			cout << "Trenutni pokazivac: " << ispis.tellg(); //trenutna lokacija pokazivaca
			cout << znak;
		}
	ispis.close();
	*/
	
	//konvertovanje teksta iz File-a u brojeve
	/*
	string fileName= "PIN.txt";
	const int max = 5;

	int pinoviIn[max]; //pin se unosi u ovaj niz, koji ce se proslijediti fajlu
	int pinoviOut[max]; //pin iz fajla se upisuje u ovaj niz

	ofstream unos(fileName);

	for (int i = 0; i < max; i++)
	{
		cout << "Unesite " << i << ". cetveroclani pin: ";
		cin >> pinoviIn[i];
		unos << pinoviIn[i] << endl;
	}
	unos.close();

	ifstream ispis(fileName);
	if (ispis.fail())
		cout << "Fail!";
	else
	{
		char charPin[max];
		cout << "Ucitani pinovi: \n";
		for (int i = 0; i < max; i++)
		{
			//iscitavamo pinov iz fajla i upisujemo u niz charPin
			ispis.getline(charPin, max);
			//konverujemo ucitani pin
			pinoviOut[i] = atoi(charPin);
			cout << i << ". PIN: " << pinoviOut[i] << endl;
		}
	}
	ispis.close();
	*/
	
	//binarni file
	
	const int max = 20;
	char imeFile[max];

	//objekat koji cemo upisati u file
	Student s;
	//objekat koji cemo inicijalizirati pomocu file-a
	Student sNew;

	cout << "Student: ";
	unos(s);
	cout << "Ime fajla: ";
	cin.getline(imeFile, max);

	//otvaranje file-a za upis u BINARNOM formatu 'ios::binary' mod
	ofstream objekatUnos(imeFile, ios::out | ios::binary);
	//koristeci funkciju write() objekat 's' upisujemo u file
	objekatUnos.write((char*)(&s), sizeof(s));
	objekatUnos.close();

	cout << "Sadrzaj file-a " << imeFile << " prebacujemo u novi objekat: \n";
	ifstream objekatIspis(imeFile, ios::in | ios::binary);
	//sadrzajem fajla, koristeci funkciju read(), inicijalizujemo atribute novog objekta
	objekatIspis.read((char*)(&sNew), sizeof(sNew));
	ispis(sNew);
	objekatIspis.close();
	

	// nacin da se sadrzaj file-a prebaci u string
	/*
	const char* fileName = "testniFile.txt";
	ofstream testFile(fileName);
	testFile << "Ovdje nema malo mnogo teksta, ali ce biti malo dovoljno za test\n";
	testFile << "Jos malo cemo dodatni zbog novog reda, ali i zezancija";
	testFile.close();

	///// nacin da se sadrzaj file-a prebaci u string
	ifstream ispis(fileName);
	string str((std::istreambuf_iterator<char>(ispis)), istreambuf_iterator<char>());
	ispis.close();

	cout << str << endl;

	cout << str.rfind("nema");
	//cout << fileSize(fileName);
	*/

	/*
	int izbor=1;
	int max = 30;
	char fileName[30];
	do
	{
		cout << crt << "Unesite ime file-a i izaberite koju opciju zelite od ponudjenih: \n";
		cin.getline(fileName, max);
		do
		{
			showMenu(izbor);
			switch (izbor)
			{
				case 1:
					UnosSadrzaja(fileName);
					break;
				case 2:
					PrikazSadrzaja(fileName);
					break;
				case 3:
					dodavanjeSadrzaja(fileName);
					break;
				case 4:
					kopiranjeSadrzaja(fileName);
					break;
				case 5:
					pretragaSadrzajaChar(fileName);
					break;
				case 6: 
					pretragaSadrzajaString(fileName);
					break;
				case 7: 
					fileSize(fileName);
					break;
				case 8: 
					brisanjeSadrzaja(fileName);
					break;
			}
		} while (izbor != 9 && izbor != 10);
	} while (izbor != 10);
	system("pause");
	*/


}