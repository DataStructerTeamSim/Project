#include "Player.h"

void giveTurnToPlayer(Player& player, list<Card>& onTable);
bool numberMatch(list<Card>& onTable);
bool playerInput(bool match);


int main() {
	//덱 셔플
	Deck d = Deck();
	//플레이어 생성 -> 사용자는 player 0;
	Player p[4]; //배열이 아닌 돌아가는 리스트 처리 vector생각 중 

	//덱 제공
	for (int i = 0; i < 4; i++) {
		p[i].setMyDeck(d.giveCardToPlayer());
	}

	int i = 0;
	//게임 시작
	while (1) {//전체적인 게임 진행 - 플래이어의 승패 결정
		bool numbermatch = false;
		bool playerinput = false;
		list<Card> onTable;
		do{//플레이어에게 턴을 제공
			giveTurnToPlayer(p[i], onTable);
			numbermatch = numberMatch(onTable);
			playerinput = playerInput(judge1);
		} while (!numbermatch && !playerinput);
		// *넘버는 맞았는데 플레이어 인풋이 없을 경우
		//랜덤 변수를 활용하여 플레이어를 제외한 컴퓨터 승자 결정 후 승자에게 onTable카드 주기
		
		// *넘버가 틀렷는데 플레이어 인풋이 있을 경우
		//플래이어에 opps함수 사용해서 컴퓨터에게 한 장씩 주기
		
		// * 넘버도 맞고 플레이어도 인풋도 있을 경우
		//플레이어에 onTable 리스트 주기
		
		
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
}
