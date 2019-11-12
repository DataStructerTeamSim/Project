#include "Player.h"
#include<time.h>
#include<conio.h>

int main()
{
	clock_t endwaitT, endwaitF;
	int match;
	match = rand() % 2;
	endwaitT = clock() + COMPUTERWAIT * CLOCKS_PER_SEC;
	endwaitF = clock() + (COMPUTERWAIT + 1)*CLOCKS_PER_SEC;

	//test
	if (match == 0)
	{
		while (clock()<endwaitT)
		{
			if (kbhit())
			{

			}
		}
		cout<<"true case";
	}
	else
	{
		while (clock()<endwaitF)
		{
			if (kbhit())
			{
				cout << "true case";
				return 0;
			}
		}
		cout<<"false case";
	}
	return 0;
}