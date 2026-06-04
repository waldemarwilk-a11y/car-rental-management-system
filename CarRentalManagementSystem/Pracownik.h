#pragma once
#include "Login.h"
class Pracownik :public Login {
public:
	void LogowanieA(char user_n[], char pass[]);
	void RejestrujA();
	void SpisKlientow();
	void SzukajAuto();
	void UsunAuto();
	void Export();
	void ModAuto();
	void DodAuto();
	void ListaAut();
	void Menu();
};
