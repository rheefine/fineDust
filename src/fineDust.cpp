#include <iostream>
#include <cstring>
#include "Account.hpp"
#include "dustfunc.hpp"

using namespace std;
const int TOTAL_ID = 100;

int main(void)
{
	char choice[20];
	Account* idArr[TOTAL_ID];
	int idNum = 0;
	while (1)
	{
		ShowMenu();
		cout << "����: ";
		cin >> choice;
		cout << endl;
		if (strcmp(choice, "1") == 0) {
			MakeID(idArr, idNum);
		}
		else if (strcmp(choice, "2") == 0) {
			ShowDust(idArr, idNum);
		}
		else if (strcmp(choice, "3") == 0) {
			ChangePlace(idArr, idNum);
		}
		else if (strcmp(choice, "4") == 0) {
			for (int i = 0; i < idNum; i++)
			{
				delete idArr[i];
			}
			return 0;
		}
		else {
			cout << "�߸��� �޴� ����" << endl;
		}
	}
	return 0;
}