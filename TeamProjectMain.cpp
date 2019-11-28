#include "Player.h"
#include <time.h>
#include <conio.h>
#include <windows.h>

void giveTurnToPlayer(Player* player);
bool numberMatch(vector<Player*> p, int*& arr);
bool playerInput(bool match);
void computerWin(Player* computer, list<list<Card>>& onTable);
void printCard(vector<Player*> p);
void clearFrontCard(vector<Player*>& p);
void whoIsLose(vector<Player*>& p, int& playernum, vector<Player*>::iterator& iter);
bool computerMistake();

int main() {
	//덱 셔플
	Deck d = Deck();
	//플레이어 생성 -> 사용자는 player 0;
	Player player;
	Player computer[COMPUTERNUM];
	vector<Player*> p;
	list<list<Card>> onTable;
	int survieCom = 3;

	player.setMyName("Player");
	p.push_back(&player);
	for (int i = 0; i < COMPUTERNUM; i++) {
		computer[i].setMyName("computer " + to_string(i + 1));
		p.push_back(&computer[i]);
	}

	vector<Player*>::iterator iter;
	//덱 제공
	for (iter = p.begin(); iter != p.end(); iter++) {
		(*iter)->setMyDeck(d.giveCardToPlayer());
		(*iter)->showMyCard();
	}

	int i = 0;
	iter = p.begin();
	//게임 시작
	while (1) {//전체적인 게임 진행 - 플래이어의 승패 결정

		bool numbermatch = false;
		bool playerinput = false;

		do {//플레이어에게 턴을 제공
			if ((*iter)->myDeckEmpty() || (*iter)->getImLoose()) { // 해당 플레이어의 덱이 없을 경우
				iter++;// 다음 사람 지목
				if (iter == p.end())
					iter = p.begin();
				continue;
			}

			giveTurnToPlayer(*iter);
			//onTable에 있는 fruit, number 출력
			printCard(p);

			/* onTable에 있는 카드 출력
			list<Card>::iterator ii;
			for (ii = onTable.begin(), i = 0; i < 4 && ii != onTable.end(); i++, ii++)
				cout << ii->fruit << ii->number << "   ";
			cout << endl;
			*/
			int* arr;
			numbermatch = numberMatch(p, arr);
			playerinput = playerInput(numbermatch);
			
			cout << endl;
			if (computerMistake() && !numbermatch) {
				iter++;
				if (iter == p.end())
					iter = p.begin();
				break;
			}
				
			//10퍼센트의 확률로 break -> 컴퓨터가 실수할 경우
			iter++;
			if (iter == p.end())
				iter = p.begin();
		} while (!numbermatch && !playerinput);

		// *넘버는 맞았는데 플레이어 인풋이 없을 경우
		if (numbermatch && !playerinput) {
			//srand(time(NULL));
			//랜덤 변수를 활용하여 플레이어를 제외한 컴퓨터 승자 결정 후 승자에게 onTable카드 주기
			//int computernum = rand() % (p.size() - 1);
			//computerWin(&computer[computernum], onTable);
			vector<Player*>::iterator com;
			do {
				srand(time(NULL));
				int whowin = (rand() % 3) + 1;
				com = p.begin();
				int j = 1;
				for (; com != p.end() && j <= whowin; j++) {
					com++;
				}
				if (!(*com)->getImLoose())
					break;
			} while (1);
			vector<Player*>::iterator it;
			for (it = p.begin(); it != p.end(); it++) {
				(*com)->inputMyDeck((*it)->get_Front_Card());
			}
			clearFrontCard(p);
			cout << (*com)->getMyName() << " is win the game" << endl;
			Sleep(2000);
		}

		// *넘버가 틀렷는데 플레이어 인풋이 있을 경우
		if (!numbermatch && playerinput) {
			//플래이어에 opps함수 사용해서 컴퓨터에게 한 장씩 주기
			
			list<Card> sendCom = p[0]->oOups(survieCom);
			vector<Player*>::iterator it = p.begin();
			it++;
			for (; it != p.end(); it++) {
				if (sendCom.empty())
					break;
				if ((*it)->getImLoose())
					continue;
				(*it)->inputMyDeck(sendCom.front());
				sendCom.pop_front();
			}
			cout << "player lose\n";
			Sleep(1000);
		}

		// * 넘버도 맞고 플레이어도 인풋도 있을 경우
		if (numbermatch && playerinput) {
			//플레이어에 onTable 리스트 주기
			vector<Player*>::iterator iter;
			for (iter = p.begin(); iter != p.end(); iter++) {
				(*p.begin())->inputMyDeck((*iter)->get_Front_Card());
			}
			clearFrontCard(p);
			cout << "player win\n";
			Sleep(2000);
		}

		// * 컴퓨터가 실수할 경우
		if (!numbermatch && !playerinput) {
			vector<Player*>::iterator com;
			do {
				srand(time(NULL));
				int wholoose = (rand() % 3) + 1;
				com = p.begin();
				int j = 1;
				for (; com != p.end() && j <= wholoose; j++) {
					com++;
				}
				if (!(*com)->getImLoose())
					break;
			} while (1);
			list<Card> send = (*com)->oOups(survieCom);
			vector<Player*>::iterator it;
			for (it = p.begin(); it != p.end(); it++) {
				if (send.empty())
					break;
				if ((*it)->getImLoose())
					continue;
				if (com == iter)
					continue;
				(*it)->inputMyDeck(send.front());
				send.pop_front();
			}
			cout << (*com)->getMyName() << "'s mistake!"<<endl;
		}
		whoIsLose(p,survieCom,iter); // 누가 졌는지 알려주기
		cout << "you have " << (*p.begin())->howManyCard() << " Cards\n";
		if ((*p.begin())->myDeckEmpty() && (*p.begin())->frontCardempty()) {
			cout << "You lose this game\n";
			break;
		}
		if (survieCom == 0) {
			cout << "You win the game\n";
			break;
		}
			
	}
	return 0;
}
void giveTurnToPlayer(Player* player) {
	//플레이어에게 turn을 주고 front카드를 onTable에 넣기
	if (player->myDeckEmpty())
		return;
	player->myTurn();
}
bool numberMatch(vector<Player*> p, int*& arr) {
	//onTable에 있는 카드들의 fruit와 number를 매치하여 같은 fruit의 number합이 5면 true리턴
	//onTable 있는 카드가 4개 이상일 경우 뒤 부터 시작해서 4개까지 읽기고 매치 시켜서 합이 5이면 true 리턴 (rbegin)
	//없으면 false
	//onTable에 있는 카드들의 fruit와 number를 매치하여 같은 fruit의 number합이 5면 true리턴
	//없으면 false
	int i;
	int checkarr[4] = {0};
	vector<Player*>::iterator it2;
	for (it2 = p.begin();it2 != p.end(); it2++)
	{
		if ((*it2)->frontCardempty())
			continue;
		switch ((*it2)->show_Front_Card().fruit)
		{
		case GRAPE:
			checkarr[0] += (*it2)->show_Front_Card().number;
			break;
		case STRAWBERRY:
			checkarr[1] += (*it2)->show_Front_Card().number;
			break;
		case BANANA:
			checkarr[2] += (*it2)->show_Front_Card().number;
			break;
		case APPLE:
			checkarr[3] += (*it2)->show_Front_Card().number;
			break;
		default:
			break;
		}
	}
	arr = checkarr;
	for (i = 0; i < 4; i++) {
		if (checkarr[i] == 5)
			return true;
	}
	return false;
}
bool playerInput(bool match) {
	//player의 cin을 받음
	//match가 true일 경우 COMPUTERWAiT 초 만큼 입력대기시간 받음
	//true를 리턴
	//match가 false일 경우 2초만큼 대기
	//만일 2초 안에 player가 입력을 했다면 true리턴
	//2초가 넘아갈 동안 입력 x 시 false 리턴

	clock_t endwait;
	clock_t endwaitT = clock() + (COMPUTERWAIT+1) * CLOCKS_PER_SEC;
	clock_t endwaitF = clock() + (COMPUTERWAIT + 1)*CLOCKS_PER_SEC;
	if (match == true)
	{
		while (clock() < endwaitT)
		{
			if (GetKeyState(VK_UP) < 0)
			{
				return true;
			}
		}
		return false;
	}
	else
	{
		while (clock() < endwaitF)
		{
			if (GetKeyState(VK_UP) < 0)
				return true;
		}
		return false;
	}
}
void computerWin(Player* computer, list<Card>& onTable) {
	// computer인자의 덱에 onTable 리스트를 이어 붙이는 함수
}

void printCard(vector<Player*> p) {
	vector<Player*>::iterator iter;
	for (iter=p.begin(); iter!= p.end(); iter++) {
		if ((*iter)->getImLoose()) {
			cout << (*iter)->getMyName() << "loose    ";
			continue;
		}

		if ((*iter)->frontCardempty()) {
			cout << "No Card     ";
			continue;
		}
		Card k = (*iter)->show_Front_Card();
		cout << k.fruit << "," << k.number << "    ";
	}
	cout << endl;

}

void clearFrontCard(vector<Player*>& p) {
	vector<Player*>::iterator it;
	for (it = p.begin(); it != p.end(); it++) {
		(*it)->rmFrontCard();
	}
}

void whoIsLose(vector<Player*>& p, int& playernum, vector<Player*>::iterator& iter) {
	vector<Player*>::iterator it = p.begin();
	//player가 졌을 경우 바로 종료
	if ((*it)->myDeckEmpty()) {
		return;
	}
	it++;
	for (; it != p.end();it++) {
		if ((*it)->getImLoose())
			continue;
		if ((*it)->myDeckEmpty() && (*it)->frontCardempty()) {
			playernum--;
			cout << (*it)->getMyName() << " is lose" << endl;
			(*it)->setImloose();
		}
	}
}
bool computerMistake() {
	srand(time(NULL));
	int a = rand() % 20;
	if (a == 0)
		return true;
	else
		return false;
}