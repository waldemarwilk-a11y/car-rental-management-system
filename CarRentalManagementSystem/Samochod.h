#pragma once
class Samochod
{
protected:
	char nazwaMM[30];
	int ID;
	int rok;
	bool stan;
public:
	inline void getdata();
	inline void putdata();
	inline void mod();
	bool stan_wyp() {
		return stan;
	}
	int get_ID() {
		return ID;
	}
	char* get_nazwaMM() {
		return nazwaMM;
	}
	void wyp() {
		this->stan = 1;
	}
};
