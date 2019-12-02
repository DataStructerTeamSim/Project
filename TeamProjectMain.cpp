#include "Player.h"
#include<time.h>
#include<conio.h>
#include<windows.h>
void giveTurnToPlayer(Player& player, list<Card>& onTable);
bool numberMatch(list<Card> onTable);
bool playerInput(bool match, Player* p,list<Card>& onTable);
void showfruit(list<Card>::iterator it);
int main() {
	
	//덱 셔플
	Deck d = Deck();
	//플레이어 생성 -> 사용자는 player 0;
	Player *p=new Player[4];
	int turn = 1,show=0,Suviver=4, suviver;
	
	//덱 제공
	for (int i = 0; i < 4; i++) {
		p[i].setMyDeck(d.giveCardToPlayer());
	}
	
	int i = 0;
	//게임 시작
	
	while (/*p[0].myDeckEmpty() == false   &&*/Suviver != 1) {//전체적인 게임 진행 - 플래이어의 승패 결정
		
		bool judge1 = false;
		bool judge2 = false;
		list<Card> onTable;
		do {//플레이어에게 턴을 제공
			
			cout << turn << " turn"<<endl;
			giveTurnToPlayer(p[i], onTable);
			for (list<Card>::iterator it = onTable.begin(); it != onTable.end(); it++)
			{
				cout << " "; showfruit(it);cout<<" "<< it->number;
				show++;
				if (show>=4)
				{
					show = 0;
					break;
				}
			}
			cout << endl;
			judge1 = numberMatch(onTable);
			judge2 = playerInput(judge1,p,onTable);
			turn++;
			for (size_t j = 0; j < Suviver; j++)
			{
				if (p[j].myDeckEmpty() == true)
				{
					Suviver = Suviver - 1;
					cout << "One player lost." << Suviver << "player left." << endl;
					Player *chp = new Player[Suviver];
					for (size_t k = 0; k < Suviver+1; k++)
					{
						if (k != j)
						{
							chp[k] = p[k];
						}
					}
					for (size_t j = 0; j < Suviver; j++)
					{
						p[j] = chp[j];
					}
					delete[] chp;
				}
				
			}
			i++;
			if (i >= Suviver)
			{
				i = 0;
			}
			
		} while (!judge1 || !judge2);
	}
	cout << Suviver;
	return 0;
}
void giveTurnToPlayer(Player& player, list<Card>& onTable) {
	//플레이어에게 turn을 주고 front카드를 onTable에 넣기
	player.myTurn();
	onTable.push_front(player.show_Front_Card());
}
bool numberMatch(const list<Card> onTable) {
	//onTable에 있는 카드들의 fruit와 number를 매치하여 같은 fruit의 number합이 5면 true리턴
	//없으면 false
	int checkarr[4] = {0,0,0,0};
	list<Card>::iterator it;
	list<Card> save(onTable);
	int i = 0;
	for (it= save.begin(); it != save.end(); it++)
	{
		switch (it->fruit)
		{
		case 0:
			checkarr[0] += it->number;
			break;
		case 1:
			checkarr[1] += it->number;
			break;
		case 2:
			checkarr[2] += it->number;
			break;
		case 3:
			checkarr[3] += it->number;
			break;
		default:
			break;
		}
		i++;
		if (i >= 4)
			break;
	}
	for (size_t i = 0; i < 4; i++)
	{
		if (checkarr[i] == 5)
		{
			save.clear();
			return true;
		}
	}
	save.clear();
	return false;
}
bool playerInput(bool match, Player* p,list<Card>& onTable) {
	//player의 cin을 받음
	//match가 true일 경우 COMPUTERWAiT 초 만큼 입력대기시간 받음
	//true를 리턴
	//match가 false일 경우 2초만큼 대기
	//만일 2초 안에 player가 입력을 했다면 true리턴
	//2초가 넘아갈 동안 입력 x 시 false 리턴
	clock_t endwaitT,endwaitF;
	clock_t start = clock();
	endwaitT = start + COMPUTERWAIT * CLOCKS_PER_SEC;
	endwaitF = start + (COMPUTERWAIT + 1)*CLOCKS_PER_SEC;
	if (match == true)
	{
		while (clock()<endwaitT)
		{
			if (kbhit()==true)
			{
				cout << "you win"<<endl;
				p[0].setMyDeck(onTable);
				return true;
			}
		}
		p[rand() % 3 + 1].setMyDeck(onTable);
		return true;
	}

	else
	{
		while (clock()<endwaitF)
		{
			if (kbhit() == true)
				return true;
		}
		return false;
	}
}
void showfruit(list<Card>::iterator it)
{
	if (it->fruit == 0)
		cout<< "GRAPE";
	else if (it->fruit == 1)
		cout << "STRAWBERRY";
	else if (it->fruit == 2)
		cout << "BANANA";
	else if (it->fruit == 3)
		cout << "APPLE";
	else
		cout << "error";
}
