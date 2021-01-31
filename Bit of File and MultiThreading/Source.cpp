#include <iostream>
#include "test.h"
#include <vector>
#include <fstream>
#include <string>

using namespace std;

/*
void testFj(vector<test> argTest)
{
	for (test t1 : argTest)
		cout << t1.getX() << endl;
}
*/

string ln = "\n--------------------------------------------------\n";
class Config {
	static string fajlPretplatnici;
	static string fajlObavijesti;
public:
	static string GetFajlPretplatnici() { return fajlPretplatnici; }
	static string GetFajlObavijesti() { return fajlObavijesti; }
};
string Config::fajlPretplatnici = "Novipretplatnici.txt";
string Config::fajlObavijesti = "Noviobavijesti.txt";

class Pretplatnik {
	string _ime;
	string _prezime;
	string _email;
public:
	Pretplatnik(string ime = "", string prezime = "", string email = "") {
		_ime = ime; _prezime = prezime;
		_email = email;
	}
	string GetImePrezime()const { return _ime + " " + _prezime; }
	string GetIme()const { return _ime; }
	string GetPrezime()const { return _prezime; }
	string GetEmail()const { return _email; }
	string ToString()const { return _ime + " " + _prezime + " " + _email; }
};

class MailServis {
public:
	void PosaljiMail(vector<Pretplatnik> pretplatnici, string sadrzaj) {
		string mail = "";
		for (Pretplatnik p : pretplatnici)
		{
			if (p.GetEmail() != "") {
				mail = "To: " + p.GetEmail() + "\n\n";
				mail += "Postovani " + p.GetImePrezime() + ",\n\n";
				mail += sadrzaj + "\n\n";
				mail += "TelecomProvider Team";
				cout << mail << ln;
			}
		}
	}
};

class TelecomProvajder {
	vector<Pretplatnik> _pretplatnici;
	vector<string> _obavijesti;
	MailServis _mailServis;
	void SaveData() {
		ofstream upis(Config::GetFajlPretplatnici());
		if (!upis.fail()) {
				for (size_t i = 0; i < _pretplatnici.size(); i++) {
					upis << _pretplatnici[i].GetIme() << endl;
					upis << _pretplatnici[i].GetPrezime() << endl;
					upis << _pretplatnici[i].GetEmail() << endl;
				}
			upis.close();
		}
		ofstream upis1(Config::GetFajlObavijesti());
		if (!upis1.fail()) {
			for (size_t i = 0; i < _obavijesti.size(); i++)
				upis1 << _obavijesti[i] << endl;
			upis1.close();
		}
	}
	void LoadData() {
		ifstream ispis(Config::GetFajlPretplatnici());
		//drugi nacin da provjerimo da li je neki fajl prazan
		if (ispis.peek() != ifstream::traits_type::eof())
			while (!ispis.eof()) {
				string ime, prezime, email;
				getline(ispis, ime);
				getline(ispis, prezime);
				getline(ispis, email);
				Pretplatnik temp(ime, prezime, email);
				_pretplatnici.push_back(temp);
			}
		ispis.close();
		ifstream ispis1(Config::GetFajlObavijesti());
		if (ispis1.peek() != ifstream::traits_type::eof())
			while (!ispis1.eof()) {
				string temp;
				getline(ispis1, temp);
				_obavijesti.push_back(temp);
			}
		ispis1.close();
	}
public:
	TelecomProvajder() { LoadData(); }
	~TelecomProvajder() { SaveData(); }
	bool DodajPretplatnika(Pretplatnik pretplatnik) {
		for (Pretplatnik p : _pretplatnici)
			if (p.ToString() == pretplatnik.ToString())//ili samo provjeriti email
				return false;
		_pretplatnici.push_back(pretplatnik);
		return true;
	}
	void DodajObavijest(string obavijest) {
		_obavijesti.push_back(obavijest);
		_mailServis.PosaljiMail(_pretplatnici, obavijest);
	}
	vector<Pretplatnik>& GetPretplatnici() { return _pretplatnici; }
	vector<string>& GetObavijesti() { return _obavijesti; }
	MailServis& GetMailServer() { return _mailServis; }
};

int main()
{
	//drugi nacin da provjerimo da li je neki fajl prazan
	// - if (ispis.peek() != ifstream::traits_type::eof())

	/*
	test t1, t2(3), t3(5);

	vector<test> tNiz;
	tNiz.push_back(t1);
	tNiz.push_back(t2);
	tNiz.push_back(t3);
	
	testFj(tNiz);
	*/

	//file u string
	/*
	string imeU = "zera aha";
	string what = "more mores";
	ofstream upis("neki.txt", ios::binary);

	upis << imeU;
	upis << what;
	upis.close();

	ifstream ispis("neki.txt", ios::binary);
	string imeI;
	char znak;
	//ispis >> imeI;
	while (ispis.get(znak))
		cout << "novi";
	//pokusaj pomjeranja pokazivaca na pocetak i ubacivanja sadrzaja filea u string iako je vec ispisan FAIL
	ispis.seekg(0, ispis.beg);
	cout << ispis.tellg();
	cout << endl;
	getline(ispis, imeI);
	ispis.close();
	cout << endl << "nothing left ?" << imeI;
	*/

	Pretplatnik denis("Denis", "Music", "denis@edu.fit.ba"),	
		jasmin("Jasmin", "Azemovic", "jasmin@edu.fit.ba"),
		adel("Adel", "Handzic", "adel@edu.fit.ba"),
		larisa("Larisa", "Dedovic", "larisa@edu.fit.ba");

	TelecomProvajder BHTelecom;
	BHTelecom.DodajPretplatnika(denis);
	BHTelecom.DodajPretplatnika(jasmin);
	BHTelecom.DodajPretplatnika(adel);
	BHTelecom.DodajPretplatnika(larisa);
	BHTelecom.DodajObavijest("Radovi na unapredjenu internet veze ce se obaviti u petak 31.05.2019. godine u 14:00h");
	BHTelecom.DodajObavijest("Prekid isporuke TV sadrzaja je planiran za cetvrtak 30.05.2019. godine u periodu od 11:00 - 13:00h");
	cin.get();
	return 0;
}