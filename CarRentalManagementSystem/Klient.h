#pragma once
#include "Login.h"
class Klient :public Login {
public:
	void Zarejestruj();
	int SprawdzIstnienieUzyt(char[]);
	void login(char user_n[], char pass[]);
	int PokazAuto();
	void Wypozycz();
	void fakt(int);
	void MenuKlienta();
	int SzukajAutoPlik(int);
};