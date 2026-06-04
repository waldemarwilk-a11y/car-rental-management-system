#include <iostream>
#include <iomanip>
#include <fstream>
#include <conio.h>
#include <string>
#include "Samochod.cpp"
#include "Login.h"
#include "Pracownik.h"
#include "Klient.h"
using namespace std;

class Samochod c;

//przydatne funkcje
int substring(string s1, string s2)
{
	int M = s1.length();
	int N = s2.length();
	for (int i = 0; i <= N - M; i++) {
		int j;
		for (j = 0; j < M; j++)
			if (s2[i + j] != s1[j])
				break;
		if (j == M)
			return i;
	}
	return -1;
}
int str_len(char c[])
{
	int length = 0;
	while (c[length] != '\0')
	{
		length++;
	}
	return length;
}
string conv_to_str(char* a, int size)
{
	int i;
	string s = "";
	for (i = 0; i < size; i++)
	{
		s = s + a[i];
	}
	return s;
}

//######################
//FUNKCJE DLA PRACOWNIKA
void Pracownik::LogowanieA(char user_n[], char pass[])
{
	string imie;
	int ch = 0, round = 0;
	ifstream fin("Pracownik.txt", ios::in);
	if (!(fin)) //sprawdzamy czy plik jest pusty
	{
		cout << "Brak danych o pracownikach!" << endl;
		fin.close();
		return;
	}
	else {
		while (fin >> Login >> Haslo)
		{
			if (strcmp(user_n, Login) == 0 && strcmp(pass, Haslo) == 0)
			{
				imie = conv_to_str(user_n, str_len(user_n));
				size_t found = imie.find("@admin");
				cout << "Witaj " << imie.substr(0, found) << "." << endl;
				round = 1;
				Menu();
			}
			else if (strcmp(user_n, Login) == 0)
			{
				cout << "Wprowadzono bledne haslo" << endl;
				round = 1;
				cout << "Rozwazasz utworzenie konta admina? (y/n): ";
				char ans;
				cin >> ans;
				if (ans == 'y' || ans == 'Y') {
					this->RejestrujA();
				}
				else {
					cout << "Mi³ego dnia!" << endl;
				}
			}
		}
		fin.close();
		if (round == 0)
		{
			cout << "Ten uzytkownik nie istnieje" << endl;
		}
	}
}
void Pracownik::RejestrujA()
{
	ofstream fout("Pracownik.txt", ios::app);
	cout << "Podaj login admina koncowka @admin: ";
	cin >> Login;
	cout << "Podaj preferowane haslo: ";
	cin >> Haslo;
	fout << Login << " " << Haslo << endl;
	fout.close();
}
void Pracownik::SpisKlientow()
{
	ifstream fin("Klient.txt", ios::in);
	if (!(fin)) //sprawdzanie czy plik jest pusty
	{
		cout << "Brak danych klientow" << endl;
		fin.close();
		return;
	}
	while (fin >> Login >> Haslo)
	{
		cout << "|" << setw(20) << Login << "|" << setw(10) << Haslo << "|" << endl;
	}
	fin.close();
}
void Pracownik::DodAuto() {
	char ch = 'y';
	ofstream fout("Samochody.txt", ios::out | ios::app);
	while (ch == 'y' | ch == 'Y')
	{
		c.getdata();
		fout.write((char*)&c, sizeof(c));
		cout << "\nChcesz dodac jeszcze jeden? (y/n): ";
		cin >> ch;
	}
	cout << "\nDane samochodu zostaly dodane\n" << endl;
	fout.close();
}

void Pracownik::ListaAut()
{
	ifstream fin("Samochody.txt", ios::in);

	if (!(fin))
	{
		cout << "Brak danych" << endl;
		fin.close();
		return;
	}
	cout << "\nLISTA SAMOCHODOW\n";
	cout << "\n========================================================\n";
	cout << "| " << left << setw(25) << "Model"
		<< "| " << setw(8) << "ID"
		<< "| " << setw(18) << "Status"
		<< "|\n";
	cout << "========================================================\n";

	while (fin.read((char*)&c, sizeof(c)))
	{
		c.putdata();
	}

	cout << "========================================================\n";

	fin.close();
}

void Pracownik::SzukajAuto()
{
	int id_wpis;
	char found = 'n';
	cout << "\nPodaj ID samochodu, ktorego szukasz ";
	cin >> id_wpis;
	//szukanie w pliku
	ifstream fin1("Samochody.txt", ios::in);
	while (fin1.read((char*)&c, sizeof(c)))
	{
		if (c.get_ID() == id_wpis)
		{
			c.putdata();
			found = 'y';
		}
	}
	fin1.close();
	if (found == 'y') { return; }

	if (found == 'n') { cout << "\nSamochodu o ID " << id_wpis << "nie ma w pliku.\n"; }
	return;
}
void Pracownik::ModAuto() //funkcja do modyfikacji pliku 
{
	int id_wpis;
	char found = 'n';
	cout << "\nPodaj ID samochodu, ktorego chcesz modyfikowac: ";
	cin >> id_wpis;

	//szukanie i modyfikacja pliku
	fstream fio1("Samochody.txt", ios::in | ios::out);
	fio1.seekg(0);
	while (!fio1.eof())
	{
		int loc = fio1.tellg(); //obecna lokacja zapisana w loc
		fio1.read((char*)&c, sizeof(c));
		if (c.get_ID() == id_wpis)
		{
			c.mod();
			found = 'y';
			fio1.seekg(loc); //przesuniêcie wskaŸnika do aktualnego miejsca
			fio1.write((char*)&c, sizeof(c));
			cout << "\nDane pojazdu o ID  " << id_wpis << " zostaly zaktualizowane" << endl;
			break;
		}
	}
	fio1.close();
	if (found == 'y') { return; }
	if (found == 'n') { cout << "\nSamochod o ID " << id_wpis << "samochodu o ID nie ma w pliku.\n"; }
	return;
}
void Pracownik::UsunAuto() //funkcja usuwajaca samochod
{
	int id_wpis;
	char found = 'n';
	cout << "\nWpisz ID pojazdu ktory chcesz usunac: ";
	cin >> id_wpis;

	ifstream fin1("Samochody.txt", ios::in);
	ofstream fout1("temp1.txt", ios::out | ios::app);
	while (fin1.read((char*)&c, sizeof(c)))
	{
		if (c.get_ID() == id_wpis)
		{
			found = 'y';
		}
		else {
			fout1.write((char*)&c, sizeof(c)); //zapisywanie do tymczasowego pliku
		}
	}
	fin1.close();
	fout1.close();
	remove("Samochody.txt");
	rename("temp1.txt", "Samochody.txt");
	if (found == 'y') {
		cout << "Dane usuniete pomyslnie" << endl;
		return;
	}
	else {
		cout << "Pozycja nieodnaleziona" << endl;
	}
}
void Pracownik::Menu()
{
	int ch, op;
	int choose;
	do {
		cout << "============================================================\n";
		cout << "              PANEL ADMINISTRATORA\n";
		cout << "============================================================\n";
		cout << "\nWybierz opcje \n 1.Dodaj Samochod \n 2.Wyswietl liste samochodow \n 3.Znajdz samochod \n 4.Zmodyfikuj dane samochodu \n 5.Usun dane samochodu\n 6.Lista Zarejestrowanych Klientow\n 7.Wyjdz" << endl;
		cout << "Podaj wybor: ";
		cin >> ch;
		switch (ch)
		{
		case 1:
			DodAuto();
			break;
		case 2:
			ListaAut();
			break;
		case 3:
			cout << "Szukanie danych o pojezdzie\n";
			SzukajAuto();
			break;
		case 4:
			cout << "Zmodyfikuj dane\n";
			ModAuto();
			break;
		case 5:
			cout << "Usuwanie danych samochodu\n";
			UsunAuto();
			break;
		case 6:
			cout << "Konta klientow" << endl;
			SpisKlientow();
			break;
		case 7:
			cout << "Dziekuje za skorzystanie z programu. Milego dnia!!" << endl;
			break;
		default:
			cout << "Nieprawidlowy wybor\n";
		}
	} while (ch != 7);
	return;
}
//###################
//FUNKCJE DLA KLIENTA
int Klient::SprawdzIstnienieUzyt(char uname[])
{
	int flag = 0;
	ifstream fin("Klient.txt", ios::in);
	while (fin >> Login >> Haslo)
	{
		if (strcmp(uname, Login) == 0) {
			flag = 1;
		}
	}
	fin.close();
	if (flag == 1)
	{
		return 1;
	}
	return 0;
}
void Klient::Zarejestruj()
{
	char new_name[100];
	char pass[50];
	int val;
	ofstream fout("Klient.txt", ios::app);
	do {
		cout << "Podaj login: ";
		cin >> new_name;
		//sprawdzanie czy uzytkownik istnieje
		val = SprawdzIstnienieUzyt(new_name);
		if (val == 1) { cout << "Uzytkownik o tej nazwie juz istnieje " << endl; }
	} while (val == 1);
	cout << "Podaj haslo: ";
	cin >> pass;
	fout << new_name << " " << pass << endl;
	fout.close();
}
int Klient::PokazAuto()
{
	ifstream fin("Samochody.txt", ios::in);

	if (!(fin))
	{
		cout << "\nBrak danych o samochodach.\n";
		fin.close();
		return 1;
	}

	cout << "\n========================================================\n";
	cout << "| " << left << setw(25) << "Model"
		<< "| " << setw(8) << "ID"
		<< "| " << setw(18) << "Status"
		<< "|\n";
	cout << "========================================================\n";

	cout << "\nDOSTEPNE SAMOCHODY:\n\n";

	while (fin.read((char*)&c, sizeof(c)))
	{
		if (c.stan_wyp() == 0)
		{
			c.putdata();
		}
	}

	fin.close();

	fin.open("Samochody.txt", ios::in);

	cout << "\nNIEDOSTEPNE SAMOCHODY:\n\n";

	while (fin.read((char*)&c, sizeof(c)))
	{
		if (c.stan_wyp() == 1)
		{
			c.putdata();
		}
	}

	cout << "========================================================\n";

	fin.close();

	return 0;
}
void Klient::Wypozycz()
{
	int id_wypozycz;
	char found = 'n';
	int check;

	cout << "\n========================================================\n";
	cout << "                WYPOZYCZENIE POJAZDU\n";
	cout << "========================================================\n";

	do
	{
		cout << "\nPodaj ID samochodu: ";
		cin >> id_wypozycz;

		check = SzukajAutoPlik(id_wypozycz);

		if (check == 0)
		{
			cout << "\nPodane ID nie istnieje.\n";
		}

	} while (check == 0);

	fstream fio("Samochody.txt", ios::in | ios::out);

	while (fio.read((char*)&c, sizeof(c)))
	{
		streampos loc = fio.tellg() - static_cast<streamoff>(sizeof(c));

		if (c.get_ID() == id_wypozycz && c.stan_wyp() == 0)
		{
			c.wyp();

			found = 'y';

			fio.seekp(loc);

			fio.write((char*)&c, sizeof(c));

			break;
		}
		else if (c.get_ID() == id_wypozycz && c.stan_wyp() == 1)
		{
			cout << "\nWybrany samochod jest juz wypozyczony.\n";

			found = 'n';

			break;
		}
	}

	fio.close();

	if (found == 'n')
	{
		cout << "\nOperacja nie powiodla sie.\n";
		return;
	}

	cout << "\n========================================================\n";
	cout << " Samochod zostal pomyslnie wypozyczony.\n";
	cout << " Dziekujemy za skorzystanie z naszych uslug.\n";
	cout << "========================================================\n";

	fakt(id_wypozycz);
}
int Klient::SzukajAutoPlik(int id_car)
{
	char found = 'n';
	ifstream fio1("Samochody.txt", ios::in);
	while (fio1.read((char*)&c, sizeof(c)))
	{
		if (c.get_ID() == id_car) {
			found = 'y';
		}
	}
	fio1.close();
	if (found == 'y') {
		return 1;
	}
	return 0;
}
void Klient::fakt(int carid)
{
	int see_car, cena;
	string nazwaS;
	int choice, n, nr_rach;
	float suma, zprzed;
	see_car = SzukajAutoPlik(carid);
	if (see_car == 1)
	{
		cena = 270;
		ifstream fin("Samochody.txt", ios::in);
		while (fin.read((char*)&c, sizeof(c)))
		{
			if (c.get_ID() == carid)
			{
				nazwaS = c.get_nazwaMM();
			}
		}
		fin.close();
	}
	system("cls");
	cout << "Dziekujemy za skorzystanie z naszych uslug!" << endl;
	nr_rach = 92482;
	cout << "Podaj liczbe dni, na ktora chcesz wypozyczyc pojazd: ";
	cin >> n;
	suma = n * cena;
	zprzed = 0.3 * suma;
	cout << endl;
	system("cls");
	cout << "------------------------ Rachunek ----------------------------" << endl;
	cout << "|" << setw(30) << "Numer rachunku" << "|" << setw(30) << nr_rach << "|" << endl;
	cout << "|" << setw(30) << "Imie Klienta" << "|" << setw(30) << Login << "|" << endl;
	cout << "|" << setw(30) << "Model samochodu" << "|" << setw(30) << nazwaS << "|" << endl;
	cout << "|" << setw(30) << "ID samochodu" << "|" << setw(30) << carid << "|" << endl;
	cout << "|" << setw(30) << "Numer dni" << "|" << setw(30) << n << "|" << endl;
	cout << "|" << setw(30) << "Suma do zaplacenia" << "|" << setw(30) << suma << "|" << endl;
	cout << "|" << setw(30) << "Zaplata przed " << "|" << setw(30) << zprzed << "|" << endl;
	cout << "|" << setw(30) << "Zaplata po uzyciu" << "|" << setw(30) << suma - zprzed << "|" << endl;
	cout << "==============================================================" << endl;

}
void Klient::MenuKlienta()
{
	int choice;
	cout << "Menu\n 1.Wynajmij\n 2.Wroc do ekranu logowania\n Twoj wybor: ";
	cin >> choice;
	switch (choice)
	{
	case 1:
		int ch;
		int collect;
		cout << setw(30) << "Szybka informacja o cenie" << endl;
		cout << "|" << setw(10) << "Typ" << " |" << setw(15) << "KOSZT ZA DZIEN" << " |" << endl;
		cout << "|" << setw(10) << "Sportowe" << " |" << setw(15) << 270 << " |" << endl;
		cout << "\nWybierz:\n 1.Wypozyczenie\n 2. Wyjscie z programu\n Twoj wybor: ";
		cin >> ch;
		switch (ch)
		{
		case 1:
			collect = PokazAuto();
			if (collect == 0)
				Wypozycz();
			break;
		default:
			cout << "Wybrales zla opcje" << endl;
			break;
		}
		break;
	default:
		break;
	}

}
void Klient::login(char user_n[], char pass[])
{
	string im;
	int round = 0;
	ifstream fin("Klient.txt", ios::in);
	while (fin >> Login >> Haslo)
	{
		if (strcmp(user_n, this->Login) == 0 && strcmp(pass, this->Haslo) == 0)
		{
			im = conv_to_str(user_n, str_len(user_n));
			size_t found = im.find("@");
			cout << "Witamy " << im.substr(0, found) << endl;
			round = 1;
			MenuKlienta();
		}
		else if (strcmp(user_n, this->Login) == 0)
		{
			cout << "Haslo jest bledne" << endl;
			round = 1;
		}
	}
	fin.close();
	if (round == 0)
	{
		char ans;
		cout << "Chcialbys sie zarejestrowac jako Klient? (y/n): ";
		cin >> ans;
		if (ans == 'y' || ans == 'Y') {
			this->Zarejestruj();
		}
		else {
			cout << "Dobrze. Wiec zycze milego dnia." << endl;
		}
	}
}



int main()
{
	class Samochod c;
	Klient l;
	Pracownik la;
	char Login[100], Haslo[50];
	int choosing;
	string uzyt;

	do {
		cout << "\n";
		cout << "============================================================\n";
		cout << "              WYPOZYCZALNIA SAMOCHODOW\n";
		cout << "============================================================\n";
		cout << " [1] Logowanie\n";
		cout << " [2] Rejestracja pracownika\n";
		cout << " [3] Rejestracja klienta\n";
		cout << " [4] Wyjscie\n";
		cout << "------------------------------------------------------------\n";
		cout << " Twoj wybor: ";
		cin >> choosing;
		switch (choosing)
		{
		case 1: //funkcja logowania ma oddzielaæ pracownika od klienta
			system("cls");
			cout << "\n============================================================\n";
			cout << "                         LOGOWANIE\n";
			cout << "============================================================\n"; 
			cout << "\n\tLogin - ";
			cin >> Login;
			cout << "\tHaslo - ";
			cin >> Haslo;
			uzyt = conv_to_str(Login, str_len(Login));
			if (substring("@admin", uzyt) != -1)
			{
				la.LogowanieA(Login, Haslo);
				choosing = 3;
			}
			else {
				l.login(Login, Haslo);
				choosing = 3;
			}
			break;
		case 2: //rejestracja admina
			la.RejestrujA();
			cout << "Dziekuje za rejestracje." << endl;
			break;
		case 3://rejestracja klienta
			l.Zarejestruj();
			cout << "Dziekuje za rejestracje." << endl;
			break;
		case 4:
			cout << "Milo ze skorzystales z aplikacji. Zycze milego dnia!!!" << endl;
			break;
		default:
			cout << "Zostala wprowadzona bledna wartosc." << endl;
			exit(1);
		}
	} while (choosing != 4);
	return 0;
}