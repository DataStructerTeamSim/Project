#include "Player.h"
#include<time.h>
#include<conio.h>
void giveTurnToPlayer(Player& player, list<Card>& onTable);
bool numberMatch(list<Card> onTable);
bool playerInput(bool match, Player& player,list<Card>& onTable);
char showfruit();

int main() {
	
	//�� ����
	Deck d = Deck();
	//�÷��̾� ���� -> ����ڴ� player 0;
	Player p[4];
	int turn = 1,show=0;
	
	//�� ����
	for (int i = 0; i < 4; i++) {
		p[i].setMyDeck(d.giveCardToPlayer());
	}

	int i = 0;
	//���� ����
	while (1) {//��ü���� ���� ���� - �÷��̾��� ���� ����
		bool judge1 = false;
		bool judge2 = false;
		list<Card> onTable;
		do {//�÷��̾�� ���� ����
			cout << turn << " turn"<<endl;
			giveTurnToPlayer(p[i], onTable);
			for (list<Card>::iterator it = onTable.begin(); it != onTable.end(); it++)
			{
				cout << " " << it->fruit<<it->number;
				show++;
				if (show>=4)
				{
					show = 0;
					break;
				}
			}
			cout << endl;
			judge1 = numberMatch(onTable);
			judge2 = playerInput(judge1,p[i],onTable);
			i++;
			if (i==4)
			{
				i = 0;
			}
			turn++;
		} while (!judge1 || !judge2);
	}
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
		cout << " show checkarr "<<i<<" = " << checkarr[i] << " ";
		if (checkarr[i] == 5)
		{
			save.clear();
			return true;
		}
		cout << endl;
	}
	save.clear();
	return false;
}
bool playerInput(bool match, Player& player,list<Card>& onTable) {
	//player�� cin�� ����
	//match�� true�� ��� COMPUTERWAiT �� ��ŭ �Է´��ð� ����
	//true�� ����
	//match�� false�� ��� 2�ʸ�ŭ ���
	//���� 2�� �ȿ� player�� �Է��� �ߴٸ� true����
	//2�ʰ� �Ѿư� ���� �Է� x �� false ����
	clock_t endwaitT,endwaitF;
	endwaitT = clock() + COMPUTERWAIT * CLOCKS_PER_SEC;
	endwaitF = clock() + (COMPUTERWAIT + 1)*CLOCKS_PER_SEC;
	if (match == true)
	{
		while (clock()<endwaitT)
		{
			if (kbhit())
			{
				
			}
		}
		cout << "win check";
		return true;
	}

	else
	{
		while (clock()<endwaitF)
		{
			if (kbhit())
				return true;
		}
		return false;
	}
}