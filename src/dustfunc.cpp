#include <iostream>
#include <cstring>
#include "dustfunc.hpp"
#include "Account.hpp"


const int NAME_LEN = 20;
const int TOTAL_ID = 100;

void ShowMenu(void)
{
	std::cout << std::endl << "----------Menu---------" << std::endl;
	std::cout << "1. ID ����" << std::endl;
	std::cout << "2. ����ġ ������ Ȯ��" << std::endl;
	std::cout << "3. ����ġ ����" << std::endl;
	std::cout << "4. ���α׷� ����" << std::endl;
}

void MakeID(Account* idArr[], int& idNum)
{
	char id[NAME_LEN];
	char place[NAME_LEN];
	std::cout << "[ID ����]" << std::endl;
	std::cout << "ID �Է�: ";
	std::cin >> id;
	for (int i = 0; i < idNum; i++)
	{
		if (strcmp(idArr[i]->GetID(), id) == 0)
		{
			std::cout << "�ߺ�ID" << std::endl;
			return;
		}
	}
	std::cout << "����ġ�� �Է��ϼ���.(��, ��, ��)" << std::endl;
	std::cin >> place;
	std::cout << std::endl;
	idArr[idNum++] = new Account(id, place);
}

void ShowDust(Account* idArr[], int& idNum)
{
	char id[NAME_LEN];

	std::cout << "[����ġ ������ Ȯ��]" << std::endl;
	std::cout << "ID : ";
	std::cin >> id;
	for (int i = 0; i < idNum; i++)
	{

		if (strcmp(idArr[i]->GetID(), id) == 0)
		{

			std::cout << std::endl << "��ø� ��ٷ��ּ���..." << std::endl << std::endl;
			idArr[i]->checkDust();
			return;
		}
	}

	std::cout << "ID �Է� ����." << std::endl;

}

void ChangePlace(Account* idArr[], int& idNum)
{
	char id[NAME_LEN];
	char place[NAME_LEN];

	std::cout << "ID �Է�: ";
	std::cin >> id;
	for (int i = 0; i < idNum; i++)
	{
		if (strcmp(idArr[i]->GetID(), id) == 0)
		{
			std::cout << "����� ����ġ�� �Է��ϼ���.(��, ��, ��)" << std::endl;
			std::cin >> place;
			std::cout << std::endl;
			idArr[i] = new Account(id, place);
			return;
		}
	}
	std::cout << "ID �Է� ����." << std::endl;

}



