#include <iostream>
#include <string>
#include <thread>

using namespace std;

string ln = "\n";

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
	cout << ln << "MAIN :: nit ID -> " << this_thread::get_id() << ln;
	//kreiramo novu nit nThread
	thread nThread(PosaljiEmailPoruke2);
	//funkcija PosaljiEmailPoruke se izvrsava u okviru nThreada
	cout << ln << "nThread :: ID -> " << nThread.get_id();
	nThread.detach();//odvajamo glavnu i nThread nit
	cin.get();
	
}