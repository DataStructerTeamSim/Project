#include "Player.h"
#include<time.h>
#include<conio.h>
void giveTurnToPlayer(Player& player, list<Card>& onTable);
bool numberMatch(list<Card>& onTable);
bool playerInput(bool match);


int main() {
	//덱 셔플
	Deck d = Deck();
	//플레이어 생성 -> 사용자는 player 0;
	Player p[4];

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
			giveTurnToPlayer(p[i], onTable);
			judge1 = numberMatch(onTable);
			judge2 = playerInput(judge1);
		} while (!judge1 || !judge2);
	}
	return 0;
}
void giveTurnToPlayer(Player& player, list<Card>& onTable) {
	//플레이어에게 turn을 주고 front카드를 onTable에 넣기
}
bool numberMatch(const list<Card>& onTable) {
	//onTable에 있는 카드들의 fruit와 number를 매치하여 같은 fruit의 number합이 5면 true리턴
	//없으면 false
}
bool playerInput(bool match) {
	//player의 cin을 받음
	//match가 true일 경우 COMPUTERWAiT 초 만큼 입력대기시간 받음
	//true를 리턴
	//match가 false일 경우 2초만큼 대기
	//만일 2초 안에 player가 입력을 했다면 true리턴
	//2초가 넘아갈 동안 입력 x 시 false 리턴
	clock_t endwait;
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