#include "Player.h"
#include<time.h>
#include<conio.h>

int main()
{
	int checkarr[4] = { 0,0,0,0 };
	list<Card>::iterator it;
	list<Card> onTable;
	realSetCard();
	Card arrmax[60];
	copy(grape, grape + 14, arrmax);//삽입용 배열만들기
	copy(banana, banana + 14, arrmax+14);
	copy(strawberry, strawberry + 14, arrmax+28);
	copy(apple, apple + 14, arrmax+42);

	for (size_t i = 0; i < 10; i++)//임의로 onTable 설정 
	{
		onTable.push_front(arrmax[rand()%56]);
	}

	for (size_t i = 0; i < 56; i++)//올바르게 복사됬나 확인
	{
		cout << arrmax[i].fruit<< " "<< arrmax[i].number<<endl;
	}
	//test
	it = onTable.begin();
	for (size_t i = 0; i < 4; i++)
	{
		switch (it->fruit)
		{
		case 0:
			checkarr[0] += it->number;
		case 1:
			checkarr[1] += it->number;
		case 2:
			checkarr[2] += it->number;
		case 3:
			checkarr[3] += it->number;
		default:
			break;
		}
		it++;
	}
	for (size_t i = 0; i < 4; i++)
	{
		if (checkarr[i] == 5)
		{
			cout << " " <<"true"<<" ";
			it = onTable.begin();
			for (size_t i = 0; i < 4; i++)
			{
				cout << it->fruit << " " << it->number << " ";
				it++;
			}
			return 0;
		}
	}
	cout <<checkarr[0] << checkarr[1] << checkarr[2] << checkarr[3] << "false";
}

