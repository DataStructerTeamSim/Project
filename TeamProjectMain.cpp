#include "Player.h"
#include<time.h>
#include<conio.h>
#include<windows.h>
void giveTurnToPlayer(Player& player, list<Card>& onTable);
bool numberMatch(list<Card> onTable);
bool playerInput(bool match, Player* p,list<Card>& onTable);
void showfruit(list<Card>::iterator it);
int main() {
	
	//�� ����
	Deck d = Deck();
	//�÷��̾� ���� -> ����ڴ� player 0;
	Player *p=new Player[4];
	int turn = 1,show=0,Suviver=4, suviver;
	
	//�� ����
	for (int i = 0; i < 4; i++) {
		p[i].setMyDeck(d.giveCardToPlayer());
	}
	
	int i = 0;
	//���� ����
	
	while (/*p[0].myDeckEmpty() == false   &&*/Suviver != 1) {//��ü���� ���� ���� - �÷��̾��� ���� ����
		
		bool judge1 = false;
		bool judge2 = false;
		list<Card> onTable;
		do {//�÷��̾�� ���� ����
			
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
	//�÷��̾�� turn�� �ְ� frontī�带 onTable�� �ֱ�
	player.myTurn();
	onTable.push_front(player.show_Front_Card());
}
bool numberMatch(const list<Card> onTable) {
	//onTable�� �ִ� ī����� fruit�� number�� ��ġ�Ͽ� ���� fruit�� number���� 5�� true����
	//������ false
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
	//player�� cin�� ����
	//match�� true�� ��� COMPUTERWAiT �� ��ŭ �Է´��ð� ����
	//true�� ����
	//match�� false�� ��� 2�ʸ�ŭ ���
	//���� 2�� �ȿ� player�� �Է��� �ߴٸ� true����
	//2�ʰ� �Ѿư� ���� �Է� x �� false ����
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
