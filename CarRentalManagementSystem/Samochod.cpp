#include "Samochod.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <conio.h>
#include <string>
#include <limits>

using namespace std;

void Samochod::getdata()
{
	cout << "Podaj model i marke samochodu: ";
	scanf_s(" %[^\n]s", nazwaMM, (unsigned)_countof(nazwaMM));

	while (1)
	{
		cout << "Podaj nr ID samochodu: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> ID;

		if (ID >= 1000 && ID <= 9999)
			break;
		else
			cout << "Wymagany jest 4-cyfrowy numer ID." << endl;
	}

	while (1)
	{
		cout << "Wybierz status wypozyczenia (1 - zajety, 0 - dostepny): ";
		cin >> stan;

		if (stan == 0 || stan == 1)
			break;
		else
			cout << "Prosze wybrac 1 lub 0." << endl;
	}
}

void Samochod::putdata()
{
	cout << "| " << left << setw(25) << nazwaMM
		<< "| " << setw(8) << ID
		<< "| " << setw(18)
		<< (stan ? "Wypozyczony" : "Dostepny")
		<< "|\n";
}

void Samochod::mod()
{
	int ch;

	cout << "\nObecne informacje:\n" << endl;
	putdata();

	cout << "\nZmodyfikuj:" << endl;
	cout << "1. Nazwa modelu" << endl;
	cout << "2. ID" << endl;
	cout << "3. Stan wypozyczenia" << endl;
	cout << "4. Wszystko" << endl;
	cout << "Twoj wybor: ";

	cin >> ch;

	switch (ch)
	{
	case 1:
		cout << "Podaj nowy model i marke samochodu: ";
		scanf_s(" %[^\n]s", nazwaMM, (unsigned)_countof(nazwaMM));
		break;

	case 2:
		cout << "Podaj nowe ID: ";
		cin >> ID;
		break;

	case 3:
		cout << "Podaj stan wypozyczenia (1 - zajety, 0 - dostepny): ";
		cin >> stan;
		break;

	case 4:
		getdata();
		break;

	default:
		cout << "Nieprawidlowa opcja." << endl;
	}
}