#include "Deck.h"

class Player {
public:
	Player() {}
	~Player() { myDeck.clear(); }
	void setMyDeck(list<Card> recive_From_Deck) {
		//recive_From_Deck에서 받은 카드 뭉치를 myDeck에 붙이는 기능
		this->myDeck = recive_From_Deck;
	}

	void setImloose() {//패배할 경우 참으로 설정
		loseOrWin = true;
	}
	bool getImLoose() {//패배했는지 안했는지 확인
		return loseOrWin;
	}
        int get_front_size()
        {
         return this->frontCard.size();
        }
	void inputMyDeck(list<Card> recive_Card) {//덱어 카드 리스트를 붙이는 것 : 이겼을 떄 사용
		list<Card>::iterator i, j;
		i = recive_Card.begin();
		j = recive_Card.end();
		myDeck.insert(myDeck.end(), i, j);
	}
	void inputMyDeck(Card recive_Card) {//덱에 카드를 붙이는 것 : 실수했을 때 사용
		myDeck.push_back(recive_Card);
	}
	void setMyName(string name) {//플레이어의 이름 설정
		this->myName = name;
	}
	string getMyName() {//플레이어의 이름 반환
		return myName;
	}

	//player의 덱이 비었는지 확인하는 메소드
	bool myDeckEmpty() {
		return myDeck.empty();
	}
	bool frontCardempty() {
		return frontCard.empty();
	}

	//player의 frontCard 카드 리턴 : 보여주기 용도
	Card show_Front_Card() {
		return *frontCard.begin();
	}

	list<Card> get_Front_Card() {//프런트 카드 자체를 반환 : 이떄 프런트 카드는 비게 된다.
		list<Card> copy;
		copy.splice(copy.end(),frontCard,frontCard.begin(), frontCard.end());
		return copy;
	}
	int howManyCard() {//카드 숫자 확인 : Deck + frontCard
		return this->frontCard.size()+myDeck.size();
	}

	void myTurn() {
		// myDeck에서 카드 1장을 가져와서 frontCard에 넣는 기능
		// 1장 가져올 때 덱이 비었는지 확인하고 비어있으면 아무것도 하지 않는다
		// 가져올 경우 myDeck에서 가져온 카드를 pop한다.

		srand((unsigned int)time(NULL));

		if (this->myDeckEmpty()) {
			return;		// 덱이 비어있으면 아무것도 하지 않고 함수종료
		}

		Card myCard;
		//덱에 랜덤으로 카드 뽑기
		int randNum = rand() % this->myDeck.size();
		list<Card>::iterator i = this->myDeck.begin();

		for (int j = 0; j < randNum && (i != this->myDeck.end()); i++, j++);

		myCard = *i;
		this->myDeck.erase(i);

		frontCard.push_front(myCard);	// 덱에 나의 맨 앞 카드 붙임

	}

	void showMyCard() {//본인이 가진 카드를 보여줌 : 코드 확인용, 실전X
		cout << "My Front Cards" << endl;
		list<Card> ::iterator i1 = frontCard.begin();
		list<Card> ::iterator i2 = myDeck.begin();
		for (; i1 != frontCard.end(); i1++) {
			cout << i1->fruit << "," << i1->number << "   ";
		}
		cout << endl;
		cout << "My Deck Cards" << endl;
		for (; i2 != myDeck.end(); i2++) {
			cout << i2->fruit << "," << i2->number << "   ";
		}
		cout << endl;
	}

	list<Card> oOups(int player_num) {
		//플래이어가 실수할 경우를 의미하며 덱에 player_num만큼 카드를 뺴서 리턴하는 메소드
		//
		// 만약 플레이어 보다 덱 카드 개수가 적으면, 프런트 카드에서 가져옴
		list<Card> mistake;
		if (myDeck.empty())
			return mistake;
		list<Card>::iterator iter1;
		
		list<Card>::reverse_iterator riter1;
		iter1 = myDeck.begin();

		int i = 0;
		for (i = 0; i < player_num && iter1 != myDeck.end(); i++) {
			mistake.push_back(*iter1);
			this->myDeck.erase(iter1++);
		}
		for (riter1 = frontCard.rbegin(); i < player_num&&riter1 != frontCard.rend(); i++) {
			mistake.push_back(*riter1);
			this->frontCard.pop_back();
		}
		return mistake;
	}

	void rmFrontCard() {
		frontCard.clear();
	}
	void clear() {
		myDeck.clear();
		frontCard.clear();
		loseOrWin = false;
		myName.clear();
	}
private:
	list<Card> myDeck;
	list<Card> frontCard;
	bool loseOrWin = false;
	string myName;
};
