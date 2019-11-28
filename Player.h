#include "Deck.h"

class Player {
public:
	Player() {}
	~Player() { myDeck.clear(); }
	void setMyDeck(list<Card> recive_From_Deck) {
		//recive_From_Deck에서 받은 카드 뭉치를 myDeck에 붙이는 기능
		this->myDeck = recive_From_Deck;
	}

	void setImloose() {
		loseOrWin = true;
	}
	bool getImLoose() {
		return loseOrWin;
	}

	void inputMyDeck(list<Card> recive_Card) {
		list<Card>::iterator i, j;
		i = recive_Card.begin();
		j = recive_Card.end();
		myDeck.insert(myDeck.end(), i, j);
	}
	void inputMyDeck(Card recive_Card) {
		myDeck.push_back(recive_Card);
	}
	void setMyName(string name) {
		this->myName = name;
	}
	string getMyName() {
		return myName;
	}

	//player의 덱이 비었는지 확인하는 메소드
	bool myDeckEmpty() {
		return myDeck.empty();
	}
	bool frontCardempty() {
		return frontCard.empty();
	}

	//player의 낸 카드 리턴

	Card show_Front_Card() {
		return *frontCard.begin();
	}

	list<Card> get_Front_Card() {
		list<Card> copy;
		copy.splice(copy.end(),frontCard,frontCard.begin(), frontCard.end());
		return copy;
	}
	int howManyCard() {
		int frontCardNum = 0;
		int myDeckNum = 0;
		list<Card> ::iterator i1 = frontCard.begin();
		list<Card> ::iterator i2 = myDeck.begin();
		for (; i1 != frontCard.end(); i1++) {
			frontCardNum++;
		}
		for (; i2 != myDeck.end(); i2++) {
			myDeckNum++;
		}
		return frontCardNum + myDeckNum;
	}

	void myTurn() {
		// myDeck에서 카드 1장을 가져와서 frontCard에 넣는 기능
		// 1장 가져올 때 덱이 비었는지 확인하고 비어있으면 아무것도 하지 않는다
		// 가져올 경우 myDeck에서 가져온 카드를 pop한다.

		srand(time(NULL));

		if (this->myDeckEmpty()) {
			return;		// 덱이 비어있으면 아무것도 하지 않고 함수종료
		}

		Card myCard;
		int randNum = rand() % this->myDeck.size();
		list<Card>::iterator i = this->myDeck.begin();

		for (int j = 0; j < randNum && (i != this->myDeck.end()); i++, j++);

		myCard = *i;
		this->myDeck.erase(i);

		frontCard.push_front(myCard);	// 덱에 나의 맨 앞 카드 붙임

	}

	void showMyCard() {
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
		// 만약 플레이어 보다 카드 개수가 적으면, 덱 전체를 리턴하게끔 구현
		list<Card> mistake;
		if (myDeck.empty())
			return mistake;
		list<Card>::iterator iter1;
		list<Card>::iterator iter2;
		iter1 = myDeck.begin();
		iter2 = mistake.begin();
		for (int i = 0; i < player_num && iter1 != myDeck.end(); i++) {
			mistake.push_back(*iter1);
			this->myDeck.erase(iter1++);
		}
		return mistake;
	}

	void rmFrontCard() {
		frontCard.clear();
	}

private:
	list<Card> myDeck;
	list<Card> frontCard;
	bool loseOrWin = false;
	string myName;
};