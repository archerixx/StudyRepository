#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <vector>
#include <future>

using namespace std;

string ln = "\n";
/*
void posaljiEmail1()
{	
	cout << "\nPosaljiEmail :: nit ID - " << this_thread::get_id() << ln;
}
void PosaljiEmailPoruke2() {
	cout << ln;
	for (size_t i = 0; i < 100; i++)
	{
		cout << "Poslano " << i + 1 << "/100 email poruka :: nit ID -> "
			<< this_thread::get_id() << endl;
	}
	cout << ln;
}
void PosaljiEmailPoruke3(string sadrzaj, int brojEmailPoruka, int& brojacEmailPoruka) {
	cout << ln;
	for (size_t i = 0; i < brojEmailPoruka; i++)
	{
		cout << "Poslana " << i + 1 << "/" << brojEmailPoruka
			<< " email poruka sadrzaja -> " << sadrzaj << endl;
		brojacEmailPoruka++;
	}
	cout << ln;
}

//kreiramo mutex objekat
mutex cuvarResursa;
void PosaljiPoruku(string poruka) {
	cuvarResursa.lock();//zakljucavamo zajednicki resurs
	cout << poruka << endl;
	cuvarResursa.unlock();//otkljucavamo zajednicki resurs
}
void PosaljiEmailPoruke(string sadrzaj, int brojEmailPoruka, int& brojacEmailPoruka) 
{
	cout << ln;
	string rb;
	for (size_t i = 0; i < brojEmailPoruka; i++)
	{
		PosaljiPoruku("Poruka " + to_string(i + 1) + ", sadrzaj -> " + sadrzaj);
		brojacEmailPoruka++;
	}
	cout << ln;
}
*/

mutex cuvarResursa;

class Student {
	string _ime;
	string _prezime;
	string _email;
public:
	Student(string ime, string prezime, string email) {
		_ime = ime; _prezime = prezime; _email = email;
	}
	string GetImePrezime()const { return _ime + " " + _prezime; }
	string GetEmail()const { return _email; }
	string ToString()const { return _ime + " " + _prezime + " " + _email; }
};

class MailServis {
	void Posalji(string mail) {
		cuvarResursa.lock();
		cout << ln << mail << ln;
		cuvarResursa.unlock();
	}
public:
	void PosaljiMail(vector<Student> studenti, string sadrzaj) {
		string mail = "";
		for (Student s : studenti)
		{
			mail = "To: " + s.GetEmail() + "\n";
			mail += "Postovani " + s.GetImePrezime() + ",\n";
			mail += sadrzaj + "\n";
			mail += "FIT Team";
			Posalji(mail);
			/*simuliramo slanje maila na nacin da trenutnoj niti "pauziramo" izvrsenje u trajanju od 2 sekunde*/
			this_thread::sleep_for(chrono::seconds(2));
		}
	}

	int BrojPoslanihMailova(vector<Student> studenti, string sadrzaj) {
		string mail = "";
		int brojMailova = 0;
		for (Student s : studenti)
		{
			mail = "To: " + s.GetEmail() + "\n";
			mail += "Postovani " + s.GetImePrezime() + ",\n";
			mail += sadrzaj + "\n";
			mail += "FIT Team";
			Posalji(mail);
			/*simuliramo slanje maila na nacin da trenutnoj niti "pauziramo" izvrsenje u trajanju od 2 sekunde*/
			this_thread::sleep_for(chrono::seconds(2));
			brojMailova++;
		}
		return brojMailova;
	}
};

class DLSistem {
	vector<Student> _studenti;
	vector<string> _obavijesti;
	MailServis _mailServis;
public:
	bool DodajStudenta(Student noviStudent) {
		for (Student s : _studenti)
			if (s.ToString() == noviStudent.ToString())
				return false;
		_studenti.push_back(noviStudent);
		return true;
	}
	void DodajObavijest(string obavijest) {
		_obavijesti.push_back(obavijest);
		_mailServis.PosaljiMail(_studenti, obavijest);
	}

	int DodajBrojObavjesti(string obavijest)
	{
		_obavijesti.push_back(obavijest);
		return _mailServis.BrojPoslanihMailova(_studenti, obavijest);
	}
};


int main()
{
	/*
	cout << "\nMAIN :: nit ID - " << this_thread::get_id() << ln;
	//kreiramo novu nit nThread
	thread nThread(posaljiEmail1);
	//funkcija posaljiEmail se izvrsava u ovkiru nove niti nThreat
	cout << ln << "nThread::ID - " << nThread.get_id();
	//povezujemo glavnu i nThread nit na nacin da se 
	nThread.join();
	cout << ln << "nThread::ID - " << nThread.get_id() << ln;
	//primjetite ID nThreada nakon povezivanja sa glavnom niti
	*/

	///////drugi primjer
	/*
	cout << ln << "MAIN :: nit ID -> " << this_thread::get_id() << ln;
	//kreiramo novu nit nThread
	thread nThread(PosaljiEmailPoruke2);
	//funkcija PosaljiEmailPoruke se izvrsava u okviru nThreada
	cout << ln << "nThread :: ID -> " << nThread.get_id();
	nThread.detach();//odvajamo glavnu i nThread nit
	
	cout << ln << "Broj konkuretnih niti: " << thread::hardware_concurrency() << ln;
	*/

	//slanje po referenci u threadu, ovakvo koristenje thread-ova dovodi do cudnog ispisa
	// jer threadovi koriste zajednicki resurs, tj u ovom slucaju 'cout'
	/*
	int brojacEmailPoruka = 0;
	thread nThread1(PosaljiEmailPoruke,
		"Odgodjeno predavanje iz predmeta PRIII", 5, ref(brojacEmailPoruka));
	thread nThread2(PosaljiEmailPoruke,
		"Prvi ispit ce biti organizovan u ponedjeljak 23.01.2019. godine.", 17, ref(brojacEmailPoruka));

	nThread1.join();
	nThread2.join();
	cout << ln << "Ukupno poslano " << brojacEmailPoruka << " email poruka/e!" << ln;	
	*/

	//koristenje mutex-a
	/*
	int brojacEmailPoruka = 0;
	thread nThread1(PosaljiEmailPoruke,	"Odgodjeno predavanje", 5, ref(brojacEmailPoruka));
	thread nThread2(PosaljiEmailPoruke,	"Prvi ispit ce biti organizovan", 17, ref(brojacEmailPoruka));
	nThread1.join();
	nThread2.join();
	cout << ln << "Ukupno poslano " << brojacEmailPoruka << " email poruka/e!" << ln;
	*/

	//multithread with class
	/*
	int brojMailova=0;
	Student denis("Denis", "Music", "denis@edu.fit.ba"),
		jasmin("Jasmin", "Azemovic", "jasmin@edu.fit.ba"),
		adel("Adel", "Handzic", "adel@edu.fit.ba"),
		larisa("Larisa", "Dedovic", "larisa@edu.fit.ba");
	DLSistem dlwms;
	dlwms.DodajStudenta(denis);
	dlwms.DodajStudenta(jasmin);
	dlwms.DodajStudenta(adel);
	dlwms.DodajStudenta(larisa);
	thread mailThread1(&DLSistem::DodajObavijest, dlwms,
		"Odgodjeno predavanje iz predmeta PRIII");
	thread mailThread2(&DLSistem::DodajObavijest, dlwms,
		"Prvi ispit ce biti organizovan u ponedjeljak 23.01.2017. godine");
	thread mailThread3(&DLSistem::DodajObavijest, dlwms,
		"Ovjera semestra pocinje u ponedjeljak 16.01.2017. godine");
	future<int> mailThread4 = async(&DLSistem::DodajBrojObavjesti, dlwms,
		"Sve ocjene iz polozenih predmeta se moraju upisati do kraja skolske godine");
	
	mailThread1.join();
	mailThread2.join();
	dlwms.DodajObavijest("OBAVIJEST KOJU SMO DODALI U GLAVNOJ NITI!");
	mailThread3.join();

	brojMailova = mailThread4.get();
	cout << endl << brojMailova << endl;
	*/
}