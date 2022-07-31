#include <iostream>
#include <cstring>
#include "Account.hpp"
#include "search.hpp"

Account::Account(char* ID, char* place)

{
	int len1 = strlen(ID) + 1;
	userID = new char[len1];
	strcpy_s(userID, len1, ID);

	int len2 = strlen(place) + 1;
	herePlace = new char[len2];
	strcpy_s(herePlace, len2, place);
}

Account::Account(const Account& ref)

{
	int len1 = strlen(ref.userID) + 1;
	userID = new char[len1];
	strcpy_s(userID, len1, ref.userID);

	int len2 = strlen(ref.herePlace) + 1;
	herePlace = new char[len2];
	strcpy_s(herePlace, len2, ref.herePlace);
}

char* Account::GetID() const
{
	return userID;
}

int Account::checkDust()
{
	search(herePlace);
	return 0;
}

int Account::changeHere(char* place)
{
	int len2 = strlen(place) + 1;
	herePlace = new char[len2];
	strcpy_s(herePlace, len2, place);

	return 0;
}

Account::~Account()
{
	delete[] userID;
	delete[] herePlace;
}
