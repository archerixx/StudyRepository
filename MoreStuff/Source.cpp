#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <list>
#include <regex>

using namespace std;

class Student
{
private:
	int* rb;
	string* ime;
public:

	Student(int rb, string ime)
	{
		this->rb = new int;
		*this->rb = rb;

		this->ime = new string;
		*this->ime = ime;
	}

	bool operator<(Student & obj)
	{
		if (*this->rb < *obj.rb)
			return true;
		else
			return false;
	}

	friend ostream& operator<<(ostream& os, const Student& obj)
	{
		os << "Redni broj; " << *obj.rb << " Student: " << *obj.ime;
		return os;
	}

};

string intToString(int broj)
{
	stringstream obj;
	obj << broj;

	return obj.str(); //funkcija str() vraca string konvertovane vrijednosti
	//pohranjene u stringstream objektu
}

int main()
{
	//strings
	/*
	//cout << "what a        break\b\b";

	string s = "Mega vega";
	string s1 = "Mega svega";
	string s2 = s;

	cout << endl << s.size() << endl << s.capacity() << endl << s.max_size() << endl;  	
	s.reserve(16); 
	cout << s.capacity() << endl;

	if (s.compare(s1)==0)
		cout << "yep\n";
	int br = 0;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == s2[i])
		{
			br++;
		}
		else
		{ 
			cout << "my bejb was jajt\n";
			break;
		}
	}

	if (br == s.size())
		cout << "strings aj came\n";

	string back(2, '\b');
	//cout << s1 << back;

	int start = s1.find(" ");

	string ss;
	cin >> ss;
	s1.replace(start, ss.size(), ss);

	cout << endl << s1;
	string sTest;
	if (sTest.empty())
		cout << "\nprazan";
	else
		cout << "\npun";

	
	char* nizKar = new char[ss.length()+1];

	ss.copy(nizKar, ss.length(), 0);
	ss[ss.length()] = '\n';

	cout << endl << nizKar; // nije bas lijep izlaz

	ss._Copy_s(nizKar, ss.length() + 1, ss.size());

	cout << endl << nizKar;

	////////////
	cout << intToString(5)+ "Zerin";
	*/
	//vectors, iterators
	/*
	Student* s1 = new Student(3, "Zera");
	Student* s2 = new Student(1, "Lejla");

	
	vector<Student*> s;
	vector<Student*>::iterator itS;
	cout << "\nwhat";
	s.push_back(s1);
	s.push_back(s2);
	
	for (itS = s.begin(); itS != s.end(); itS++)
	{
		cout << endl << **itS;
	}

	sort(s.begin(), s.end());
	cout << endl << endl;
	for (itS = s.begin(); itS != s.end(); itS++)
	{
		cout << endl << **itS;
	}
	*/
	/*
	Student s1(3, "Zera");
	Student s2(1, "Lejla");


	vector<Student> s;
	vector<Student>::iterator itS; // - pokazivac na kontainer
	s.push_back(s1);
	s.push_back(s2);
	
	for (itS = s.begin(); itS != s.end(); itS++)
	{
		cout << endl << *itS;
	}

	sort(s.begin(), s.end());
	cout << endl << endl;
	for (itS = s.begin(); itS != s.end(); itS++)
	{
		cout << endl << *itS;
	}

	cout << endl;
	//s.erase(s.begin() + lokacija_brisanja); - brisanje jendog clana
	//s.erase(s.begin(), s.end(); - brisanje svih clanova
	//random_shuffle(s.begin(), s.end()); -mjesanje svih clanova u skupu
	//s.pop_back(); -brisanje zadnjeg elemnta iz skupa

	ostream_iterator<Student> out_it(cout, "\n");
	copy(s.begin(), s.end(), out_it);
	*/
	//lists
	/*
	ostream_iterator<string> out(cout, "\n");
	
	list<string> godineStudija;

	//dodavanje elemenata na kraj liste
	godineStudija.push_back("treca");
	godineStudija.push_back("cetvrta");
	//dodavanje elemenata na pocetak liste
	godineStudija.push_front("druga");
	godineStudija.push_front("prva");

	copy(godineStudija.begin(), godineStudija.end(), out);
	*/
	/*
	list<string> fit(3, "fit");

	string lokacije[] = { "Zenica", "Sarajevo" , "Tuzla" };

	fit.insert(fit.end(), lokacije, lokacije + 3);

	//copy(fit.begin(), fit.end(), out);

	fit.remove("fit");

	//copy(fit.begin(), fit.end(), out);

	list<string> lokacija2 = fit;

	//copy(lokacija2 .begin(), lokacija2.end(), out);

	list<string> lokacija3;

	lokacija3.push_back("Zagreb");
	lokacija3.push_back("Osijek");
	lokacija3.push_back("Rijeka");

	lokacija2.splice(lokacija2.begin(), lokacija3);
	copy(lokacija2.begin(), lokacija2.end(), out);

	lokacija2.push_front("Osijek");
	lokacija2.push_front("Rijeka");

	lokacija2.sort();
	cout << endl;
	//copy(lokacija2.begin(), lokacija2.end(), out);
	lokacija2.unique();
	copy(lokacija2.begin(), lokacija2.end(), out);
	*/
	int fk;
	//gramatika regex
	/*
	/*
	string s1 = "fakultet fit mostar";
	string s2 = "fit";

	string pravilo = "f[a-z]{1,3}t";
	smatch odgovaraPravilu; //koristi se da zadrzi dio teksta koji zadovoljava pravilo pozvano u regex_search

	regex reg(pravilo);

	if (regex_search(s1, odgovaraPravilu, reg))
	{
		cout << s1 << " - zadovoljava pravilo: " << pravilo << endl; 
		cout << "Pronadjeno: " << odgovaraPravilu.str() << endl;
	}

	if (regex_search(s2, reg))
		cout << s2 << " -zadovoljava pravilo: " << pravilo;
	*/
	/*
	string tekst = "fakultet fit se nalazi u mostaru 45. fiat je oficjelno vozilo studenta fit-a";

	string pravilo = "[\d]";
	smatch tekstOdgovaraPravilu;

	regex reg(pravilo);
	sregex_iterator iter_pocetak(tekst.begin(), tekst.end(), reg); //'s' ispred regex oznacava
	//da je rijec o regex iteratoru koji je namjenjen za string
	// da je rijec o obicnom nizu karaktera onda bi se koristio 'regex_iterator'

	sregex_iterator iter_kraj; // it_kraj se kreira koristeci defaultni konstruktor 
	//i postavlja na vrijednost kraja kontejnera,
	//te nam sluzi prvenstveno za potrebe izvrsenja while petlje

	while (iter_pocetak != iter_kraj)
	{
		cout << "Pronadjeno " << iter_pocetak->str() << " na lokaciji " << iter_pocetak->position() << endl;
		iter_pocetak++;
	}
	*/
	/////// koristenje gramatike
	/*
	string ime="Zerin", prezime="Tursic";
	string korisnickoIme = ime + "." + prezime;
	string pravilo = "(?=(" + ime + "|" + prezime + "))";
	string lozinka;
	*/
	/// simple passwarod
	/*
	regex regLoz(pravilo);
	do
	{
		getline(cin, lozinka);
	} while (regex_search(lozinka, regLoz)); // ili: while(regex_search(lozinka, regex(pravilo)));

	cout << "yey" << endl;
	*/
	///complex password
	/*
	cout << "Pw mora imati namanje 7 znakova \nvelika slova \nmala slova \nbrojeve ";
	cout <<	"\nnajmanje 2 ponavljanja jednog od ovih znakova: '@', '*', ',', '_'\n";

	pravilo = "(?=.{7,})(?=.+\\d)(?=.*[a-z])(?=.*[A-Z])(?=.*[!*@]{2})";
	cout << endl;
	//pravilo = "(?=er)";
	regex regComplexLoz(pravilo);
	//int i = 3;
	do
	{
		
		getline(cin, lozinka);
	} while (!regex_search(lozinka, regComplexLoz));

	cout << korisnickoIme << endl;
	cout << lozinka;
	*/
	//regex_match telefonski broj
	/*
	string pravilo, tel;
	cout << "38761222333\n";
	cout << "+38761222333\n";
	cout << "+387(61)222333\n";

	/*
	(\\+)? -  opcionalan znak + na pocetku (nijedna ili jedna)
	(\\d{3}) - tri broja (npr. 387)
	(\\()? - opcionalna lijeva zagrada
	(\\d{2}) - dva broja (npr. 61)
	(\\))? - opcionalna desna zagrada
	([-.])? - opcionalni znak "." ili "-"
	(\\d{3}) - tri broja (npr. 222)
	([-.]?) - opcionalni znak "." ili "-"
	(\\d{3}) - tri broja (npr. 333)
	////////////////////////

	pravilo = "(\\+)?(\\d{3})(\\()?(\\d{2})([)])?([-.])?(\\d{3})([-.]?)(\\d{3})";

	cout << endl;
	do
	{
		getline(cin, tel);
	} while (!regex_match(tel, regex(pravilo)));
	*/
	//zamjena i store pravila
	/*
	//zamejna dupliranih rijeci sa jednom rijecju
	string pravilo = "([A-Za-z]+) \\1";
	//[A-Za-z]+)\\1 ---- pronalazi dupla slova unutar rijeci,
	//a posto je koristenjem zagrada formirana grupa, 
	//onda se broj 1 odnosi na prvu grupu tj. njeno ponavljanje 
	//(ako se pronadje rijec Apple ona ce predstavljati grupu,
	//onda bi nakon nje opet trebala doci rijec Apple)
	//posto se zagradama moze definisati vise grupa
	/////////////////
	regex reg(pravilo);
	string zamjeniSa;

	string tekst = "FIT Univerziteta \"Dzemal Bijedic\" u Mostaru je postao  oficijalni Pearson VUE Testing centar. Pearson VUE (Pearson Virtual University Enterprise) vodeca je medjunarodna organizacija za polaganja industrijskih certifikata cije usluge koriste mnoge poznate firme i organizacije kao sto su Adobe, Apple Apple IT, Cisco, C++ Institute, VMware, Symantec, Oracle, Novell, Nokia Solutions and networks, Linux Professional Institute, Juniper Networks, CompTIA, Citrix i mnogi drugi.";

	//zamjeni duple rijeci sa jednom
	tekst = regex_replace(tekst, reg, "$1");

	cout << endl << tekst << endl;

	pravilo = "\\bFIT\\b"; //pronadji rijec FIT

	reg = pravilo;

	tekst = regex_replace(tekst, reg, "Fakultet Info Tehn");

	cout << endl << tekst << endl;


	string newP;
	do
	{
		getline(cin, pravilo);
		if (pravilo == "STOP")
			break;
		
		newP = "\\b" + pravilo + "\\b";
		reg = newP;
		cout << endl;
		getline(cin, zamjeniSa);
		regex_replace(tekst, reg, zamjeniSa);
		system("cls");
		cout << endl << tekst << endl;
	} while (pravilo != "STOP");
	*/
}