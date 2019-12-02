#include "Player.h"
#include<time.h>
#include<conio.h>
void giveTurnToPlayer(Player& player, list<Card>& onTable);
bool numberMatch(list<Card> onTable);
bool playerInput(bool match, Player& player,list<Card>& onTable);
char showfruit();

int main() {
	
	//덱 셔플
	Deck d = Deck();
	//플레이어 생성 -> 사용자는 player 0;
	Player p[4];
	int turn = 1,show=0;
	
	//덱 제공
	for (int i = 0; i < 4; i++) {
		p[i].setMyDeck(d.giveCardToPlayer());
	}

	int i = 0;
	//게임 시작
	while (1) {//전체적인 게임 진행 - 플래이어의 승패 결정
		bool judge1 = false;
		bool judge2 = false;
		list<Card> onTable;
		do {//플레이어에게 턴을 제공
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
	//player의 cin을 받음
	//match가 true일 경우 COMPUTERWAiT 초 만큼 입력대기시간 받음
	//true를 리턴
	//match가 false일 경우 2초만큼 대기
	//만일 2초 안에 player가 입력을 했다면 true리턴
	//2초가 넘아갈 동안 입력 x 시 false 리턴
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