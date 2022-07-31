#pragma once

class Account
{
private:
	char* userID;
	char* herePlace;

public:
	Account(char* ID, char* place);
	Account(const Account& ref);
	char* GetID() const;
	int checkDust();
	int changeHere(char* place);
	~Account();
};

