#include <iostream>
#include <cstring>
#include "dustfunc.hpp"
#include "Account.hpp"


const int NAME_LEN = 20;
const int TOTAL_ID = 100;

void ShowMenu(void)
{
	std::cout << std::endl << "----------Menu---------" << std::endl;
	std::cout << "1. ID 생성" << std::endl;
	std::cout << "2. 현위치 대기상태 확인" << std::endl;
	std::cout << "3. 현위치 변경" << std::endl;
	std::cout << "4. 프로그램 종료" << std::endl;
}

void MakeID(Account* idArr[], int& idNum)
{
	char id[NAME_LEN];
	char place[NAME_LEN];
	std::cout << "[ID 생성]" << std::endl;
	std::cout << "ID 입력: ";
	std::cin >> id;
	for (int i = 0; i < idNum; i++)
	{
		if (strcmp(idArr[i]->GetID(), id) == 0)
		{
			std::cout << "중복ID" << std::endl;
			return;
		}
	}
	std::cout << "현위치를 입력하세요.(읍, 면, 동)" << std::endl;
	std::cin >> place;
	std::cout << std::endl;
	idArr[idNum++] = new Account(id, place);
}

void ShowDust(Account* idArr[], int& idNum)
{
	char id[NAME_LEN];

	std::cout << "[현위치 대기상태 확인]" << std::endl;
	std::cout << "ID : ";
	std::cin >> id;
	for (int i = 0; i < idNum; i++)
	{

		if (strcmp(idArr[i]->GetID(), id) == 0)
		{

			std::cout << std::endl << "잠시만 기다려주세요..." << std::endl << std::endl;
			idArr[i]->checkDust();
			return;
		}
	}

	std::cout << "ID 입력 오류." << std::endl;

}

void ChangePlace(Account* idArr[], int& idNum)
{
	char id[NAME_LEN];
	char place[NAME_LEN];

	std::cout << "ID 입력: ";
	std::cin >> id;
	for (int i = 0; i < idNum; i++)
	{
		if (strcmp(idArr[i]->GetID(), id) == 0)
		{
			std::cout << "변경된 현위치를 입력하세요.(읍, 면, 동)" << std::endl;
			std::cin >> place;
			std::cout << std::endl;
			idArr[i] = new Account(id, place);
			return;
		}
	}
	std::cout << "ID 입력 오류." << std::endl;

}



