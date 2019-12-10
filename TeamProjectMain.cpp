#include "Player.h"
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <iomanip>

void giveTurnToPlayer(Player* player);
bool numberMatch(vector<Player*> p);
bool playerInput(bool match);
void printCard(vector<Player*> p);
void clearFrontCard(vector<Player*>& p);
void whoIsLose(vector<Player*>& p, int& playernum, vector<Player*>::iterator& iter);
bool computerMistake();

int difficult;

int main() {
	//덱 셔플
	cout << "Welcome Hali-Gali Game\n";
	cout << "You can choose how difficult this game!\n";
	
	while(1){
	//덱 생성
	Deck d = Deck();

	//플레이어 생성 -> 사용자는 player 0;
	Player player;
	Player computer[COMPUTERNUM];

	//플레이어를 담는 벡터 생성 Player*값으로 설정 
	//-> 플레이어의 턴을 제공하고 이에 따라 데이터 수정이 일어나기 때문
	// p[0]이 사용자 [1] ~ [3]은 컴퓨터
	vector<Player*> p;
	//살아있는 컴퓨터 숫자
	int survieCom = 3;

	//각 플레이어의 이름 생성 -
	player.setMyName("Player");
	p.push_back(&player);
	for (int i = 0; i < COMPUTERNUM; i++) {
		computer[i].setMyName("computer " + to_string(i + 1));
		p.push_back(&computer[i]);
	}

	//벡터 iter -> 턴마다 플레이어를 가리킴
	vector<Player*>::iterator iter;
	//컴퓨터와 플레이어에 덱의 카드 제공
	for (iter = p.begin(); iter != p.end(); iter++) {
		(*iter)->setMyDeck(d.giveCardToPlayer());
		//(*iter)->showMyCard();
	}

	int i = 0;
	//iter를 사용자를 가리키게 만듬
	iter = p.begin();
	

	// 난이도 설정 1[쉬움]~3[어려움] 
	cout << "Choose difficult![1(esay)~3(hard)] : ";
	while (1) {
		cin >> difficult;
		if (difficult <= 3 && difficult > 0) {
			cout << "You choose" << difficult << endl;
			Sleep(2000);
			cin.clear();
			cin.ignore(100, '\n');
			break;
		}
		cout << "You input out of range! Choose again\n";
		cin.clear();
		cin.ignore(100, '\n');
	}

	while (1) {//전체적인 게임 진행 - 플래이어의 승패 결정
		cout << "Start!" << endl;
		Sleep(1000);
		bool numbermatch = false;
		bool playerinput = false;

		do {//플레이어에게 턴을 제공
			if ((*iter)->myDeckEmpty() || (*iter)->getImLoose()) { // 해당 플레이어의 덱이 없거나 패배했을 경우
				iter++;// 다음 사람 지목
				if (iter == p.end())//끝을 가리키면 처음을 가리키게 설정
					iter = p.begin();
				continue;
			}
			//해당 플레이어의 턴 제공
			giveTurnToPlayer(*iter);
			// 모든 플레이어의 frontCard출력
			printCard(p);

			//카드가 맞는게 있는지 확인
			numbermatch = numberMatch(p);
			//플레이어 인풋 확인
			playerinput = playerInput(numbermatch);

			cout << endl;
			
			//컴퓨터의 실수값 생성
			//0~9까지 랜덤으로 뽑고 0일 경우 참 아니면 거짓
			//넘버 매치도 안되고, 플레이어 인풋도 없는 경우 실행
			if (computerMistake() && !numbermatch && !playerinput) {
				//다음 플레이어 지목
				iter++;
				if (iter == p.end())
					iter = p.begin();
				break;
			}

			//다음 플레이어 지목
			iter++;
			if (iter == p.end())
				iter = p.begin();
		} while (!numbermatch && !playerinput);

		// *넘버는 맞았는데 플레이어 인풋이 없을 경우
		if (numbermatch && !playerinput) {
			//랜덤 변수를 활용하여 플레이어를 제외한 컴퓨터 승자 결정 후 승자에게 플레이어 모두의 front카드 주기
			
			//승자 결정 iter:com
			vector<Player*>::iterator com;
			do {//컴퓨터 선택, 선택된 컴퓨터가 진 상태일 경우 살아있는 컴퓨터를 찾을 떄 까지 반복
				srand(time(NULL));
				int whowin = (rand() % 3) + 1;
				com = p.begin();
				int j = 1;
				for (; com != p.end() && j <= whowin; j++) {
					com++;
				}
				if (!(*com)->getImLoose()) // 살아있으면 탈출
					break;
			} while (1);

			//모든 플레이어 지목하는 iter:it
			vector<Player*>::iterator it;
			int cardnum = 0;
			for (it = p.begin(); it != p.end(); it++) {//frontCard의 list들을 이긴 컴퓨터 덱에 넣기
				if((*com)!=*it){ cardnum += (*it)->get_front_size(); }
				(*com)->inputMyDeck((*it)->get_Front_Card());
			}
			clearFrontCard(p); //모든 플레이어의 frontCard 리스트 초기화
			cout << (*com)->getMyName() << " is win the game" << endl;
			Sleep(1000);
			cout << (*com)->getMyName() << " get " << cardnum << " cards" << endl;
			Sleep(1000);
		}

		// *넘버가 틀렷는데 플레이어 인풋이 있을 경우
		if (!numbermatch && playerinput) {
			//플래이어에 opps함수 사용해서 컴퓨터에게 한 장씩 주기

			//제공될 카드 뭉치, 살아있는 컴퓨터 수 이하만큼 반환하도록 설정
			list<Card> sendCom = p[0]->oOups(survieCom);

			//사용자를 제외한 컴퓨터를 가리키는 iter:it
			vector<Player*>::iterator it = p.begin();
			it++;
			for (; it != p.end(); it++) {
				//제공될 카드 뭉치가 비었으면 끝
				if (sendCom.empty())
					break;
				if ((*it)->getImLoose()) //패배한 컴퓨터를 가리킬 경우 넘어가기
					continue;
				(*it)->inputMyDeck(sendCom.front()); //컴퓨터에게 카드 제공
				sendCom.pop_front();
			}
			cout << "Your mistake\n";
			Sleep(1000);
			cout << "You lose " << survieCom << " cards\n";
			Sleep(1000);
		}

		// * 넘버도 맞고 플레이어도 인풋도 있을 경우
		if (numbermatch && playerinput) {
			//플레이어에 모든 frontCard제공
			//컴퓨터가 맞았을 경우와 똑같음
			vector<Player*>::iterator iter;
			int cardnum = 0;
			for (iter = p.begin(); iter != p.end(); iter++) {
				if (*iter != p[0])
					cardnum += (*iter)->get_front_size();
				(*p.begin())->inputMyDeck((*iter)->get_Front_Card());
			}
			clearFrontCard(p);
			cout << "player win\n";
			Sleep(1000);
			cout << "You get " << cardnum << " cards" << endl;
			Sleep(1000);
		}

		// * 컴퓨터가 실수할 경우
		if (!numbermatch && !playerinput) {
			//랜덤으로 실수한 컴퓨터 지정 : 패배한 컴퓨터 가리킬 경우 반복
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
				if (com == it)
					continue;
				(*it)->inputMyDeck(send.front());
				send.pop_front();
			}
			cout << (*com)->getMyName() << "'s mistake!" << endl;
			Sleep(1000);
			cout << (*com)->getMyName() << " lose " << survieCom << " cards" << endl;
			Sleep(1000);
			cout << "You get 1 card\n";
			Sleep(1000);
		}
		whoIsLose(p, survieCom, iter); // 누가 졌는지 알려주기
		cout << "you have " << (*p.begin())->howManyCard() << " Cards\n"; //플레이어의 남은 카드 수 반환 : frontCard + deckCard
		Sleep(1000);
		if ((*p.begin())->myDeckEmpty() && (*p.begin())->frontCardempty()) {//플레이어의 남은 카드가 없을 경우 패배
			cout << "You lose this game\n";
			break;
		}
		if (survieCom == 0) {//남은 컴퓨터가 없는 경우 플레이어 승리
			cout << "You win the game\n";
			break;
		}

	}
	char porout;
	cout << "Play Again? (input y or n)\n"; //다시 할지 판단
	cin >> porout;
	if (porout == 'y') {
		cout << "Play again" << endl;
		Sleep(1000);
	}
	else {
		cout << "out this game\n";
		break;
	}
	cin.ignore();
	}
	return 0;
}
void giveTurnToPlayer(Player* player) {
	//플레이어의  myTurn메소드 실행 -> 플레이어 덱이 비었을 경우 리턴
	if (player->myDeckEmpty())
		return;
	player->myTurn();
}
bool numberMatch(vector<Player*> p) {
	//onTable에 있는 카드들의 fruit와 number를 매치하여 같은 fruit의 number합이 5면 true리턴
	//onTable 있는 카드가 4개 이상일 경우 뒤 부터 시작해서 4개까지 읽기고 매치 시켜서 합이 5이면 true 리턴 (rbegin)
	//없으면 false
	//onTable에 있는 카드들의 fruit와 number를 매치하여 같은 fruit의 number합이 5면 true리턴
	//없으면 false
	int i;
	int checkarr[4] = { 0 };
	vector<Player*>::iterator it2;
	for (it2 = p.begin(); it2 != p.end(); it2++)
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
	//위 화살표 방향키 입력을 받음
	// 쉬움 2.75초 보통 1.75초 어려움 0.75초 대기

	clock_t endwait;
	clock_t endwaitT = clock() + (3.75 - difficult) * CLOCKS_PER_SEC;
	clock_t endwaitF = clock() + (COMPUTERWAIT + 1)*CLOCKS_PER_SEC;
	if (match == true)
	{
		while (clock() < endwaitT)
		{
			if (GetKeyState(VK_UP) < 0)
			{
				return true;
			}
			if (GetKeyState(VK_DOWN) < 0) {
				while (1) {
					if (GetKeyState(VK_LEFT) < 0)
						break;
				}
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
			if (GetKeyState(VK_DOWN) < 0) { // 방향키 아래를 누르면 대기
				while (1) {
					if (GetKeyState(VK_LEFT) < 0)//왼쪽을 누를 경우 브레이크
						break;
				}
			}
		}
		return false;
	}
}

void printCard(vector<Player*> p) {//프런트 카드 출력
	vector<Player*>::iterator iter;
	string** print = new string*[4]; //카드 출력 메모리 설정
	int i = 0;
	for (int i = 0; i < 4; i++) {
		print[i] = new string[6];
		for (int j = 0; j < 6; j++)
			print[i][j] = "      ";
	}

	for (iter = p.begin(); iter != p.end() && i < 4; iter++, i++) {
		if ((*iter)->getImLoose()) {//질 경우 이름 뒤에 loose 붙이기

			cout << left << setw(18) << (*iter)->getMyName() + " loose";
			continue;
		}
		//이름 출력
		cout << left << setw(18) << (*iter)->getMyName();
		if ((*iter)->frontCardempty()) {//frontCard가 비었을 경우 패스
			continue;
		}
		//frontcard를 가져오고 print[i]에 저장
		Card k = (*iter)->show_Front_Card();
		print[i] = fruitPrint(k);
	}
	cout << endl;
	for (int j = 0; j < 6; j++) {
		for (i = 0; i < 4; i++) {
			cout << left << setw(18) << print[i][j];
		}
		cout << endl;
	}
	delete[] print;
}

void clearFrontCard(vector<Player*>& p) {//모든 플레이어 front카드 리스트 초기화
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
	for (; it != p.end(); it++) {
		//이미 진 경우 패스
		if ((*it)->getImLoose())
			continue;
		//모두 비었을 경우 
		if ((*it)->myDeckEmpty() && (*it)->frontCardempty()) {
			playernum--;//컴퓨터 숫자 1만큼 줄이기
			cout << (*it)->getMyName() << " is lose" << endl;
			(*it)->setImloose();
		}
	}
	Sleep(1000);
}
bool computerMistake() { //컴퓨터 실수 확률 설정
	srand(time(NULL));
	int a = rand() % 10;
	if (a == 0)
		return true;
	else
		return false;
}