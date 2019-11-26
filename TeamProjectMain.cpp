#include "Player.h"
#include <conio.h>

void giveTurnToPlayer(Player* player, list<Card>& onTable);
bool numberMatch(list<Card>& onTable);
bool playerInput(bool match);
void computerWin(Player* computer, list<Card>& onTable);


int main() {
	//덱 셔플
	Deck d = Deck();
	//플레이어 생성 -> 사용자는 player 0;
	Player player;
	Player computer[COMPUTERNUM];
	vector<Player*> p;

	p.push_back(&player);
	for (int i = 0; i < COMPUTERNUM; i++)
		p.push_back(&computer[i]);
	vector<Player*>::iterator iter;
	//덱 제공
	for (iter = p.begin(); iter != p.end();iter++) {
		(*iter)->setMyDeck(d.giveCardToPlayer());
	}

	int i = 0;
	iter = p.begin();
	//게임 시작
	while (1) {//전체적인 게임 진행 - 플래이어의 승패 결정
		
		bool numbermatch = false;
		bool playerinput = false;
		list<Card> onTable;
		do {
			if ((*iter)->myDeckEmpty())
				continue;
			giveTurnToPlayer(*iter, onTable);
			//onTable에 있는 fruit, number 출력
			numbermatch = numberMatch(onTable);
			playerinput = playerInput(numbermatch);
			//10퍼센트의 확률로 break -> 컴퓨터가 실수할 경우
		} while (!numbermatch && !playerinput);

		// *넘버는 맞았는데 플레이어 인풋이 없을 경우
		if(numbermatch && !playerinput){
			srand(time(NULL));
			//랜덤 변수를 활용하여 플레이어를 제외한 컴퓨터 승자 결정 후 승자에게 onTable카드 주기
			int computernum = rand() % (p.size() - 1);
			computerWin(&computer[computernum], onTable);
		}

		// *넘버가 틀렷는데 플레이어 인풋이 있을 경우
		if (!numbermatch && playerinput) {
			//플래이어에 opps함수 사용해서 컴퓨터에게 한 장씩 주기
		}

		// * 넘버도 맞고 플레이어도 인풋도 있을 경우
		if (numbermatch && playerinput) {
			//플레이어에 onTable 리스트 주기
		}

		// * 컴퓨터가 실수할 경우
		if (!numbermatch && !playerinput) {
			// 
		}


	}
	return 0;
}
void giveTurnToPlayer(Player* player, list<Card>& onTable) {
	//플레이어에게 turn을 주고 front카드를 onTable에 넣기
}
bool numberMatch(const list<Card>& onTable) {
	//onTable에 있는 카드들의 fruit와 number를 매치하여 같은 fruit의 number합이 5면 true리턴
	//onTable 있는 카드가 4개 이상일 경우 뒤 부터 시작해서 4개까지 읽기고 매치 시켜서 합이 5이면 true 리턴 (rbegin)
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
	clock_t endwaitT = clock() + COMPUTERWAIT * CLOCKS_PER_SEC;
	clock_t endwaitF = clock() + (COMPUTERWAIT + 1)*CLOCKS_PER_SEC;
	if (match == true)
	{
		while (clock() < endwaitT)
		{
			if (kbhit())
			{

			}
		}
		return true;
	}
	else
	{
		while (clock() < endwaitF)
		{
			if (kbhit())
				return true;
		}
		return false;
	}
}
void computerWin(Player* computer, list<Card>& onTable) {
	// computer인자의 덱에 onTable 리스트를 이어 붙이는 함수
}
