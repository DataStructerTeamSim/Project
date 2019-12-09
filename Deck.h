#include "main.h"

//main.h에 선언된 과일 카드를 사용하여 랜덤하게 섞은 후 list에 저장하는 class

class Deck {
public:
	Deck() {
		deck_Card = new Card[56];
		realSetCard(); // 전역변수 카드 배열 값 설정
		setDeck_Card(); //카드 값 설정 기본 배열
		shuffle_Deck_Card(); // 카드 섞기 기본 배열

		//Deck_Card 값을 list로 만드는 코드
		for (int i = 0; i < 56;i++) {
			deck_List.push_back(deck_Card[i]);
		}
	}
	~Deck() { deck_List.clear(); delete[] deck_Card; }

	void insertCard(Card c) {	// 카드를 덱에 넣기 (추가된 부분)
		deck_List.push_back(c);
	}

	void setDeck_Card() {
		//과일 카드들을 deck_Card에 붙여서 넣기
		for (int i = 0; i < 56; i++) {
			if (i >= 0 && i < 14)
				deck_Card[i] = grape[i];
			else if (i >= 14 && i < 28)
				deck_Card[i] = strawberry[i - 14];
			else if (i >= 28 && i < 42)
				deck_Card[i] = banana[i - 28];
			else
				deck_Card[i] = apple[i - 42];
		}
	}
	void shuffle_Deck_Card() {
		//Deck_Card들의 배열을 랜덤하게 섞기
		srand((unsigned int)time(NULL));
		Card temp;
		int rn;
		for (int i = 0; i < 55; i++) {
			rn = rand() % (56 - i) + i;
			temp = deck_Card[i];
			deck_Card[i] = deck_Card[rn];
			deck_Card[rn] = temp;
		}
	}
	list<Card> giveCardToPlayer() {
		//플레이어에게 제공할 카드 14장 list를 리턴하는 메소드
		//줄 때마다 덱에서 14장 제거해야 된다.
		list<Card> givePlayerDeck;
		iter1 = this->deck_List.begin();
		iter2 = this->deck_List.begin();
		for (int i = 0; i < 14; i++)
			iter2++;
		givePlayerDeck.splice(givePlayerDeck.begin(),deck_List, iter1, iter2);
		return givePlayerDeck;
	}

	//deck에 섞여 있는 카드 보기
	void printAllCard() {
		for (iter1 = deck_List.begin(); iter1 != deck_List.end(); iter1++) {
			cout << (*iter1).fruit << " " << (*iter1).number << "   ";
		}
	}
	void clear(){
		delete[] deck_Card;
		deck_List.clear();

	}

private:
	Card* deck_Card;
	list<Card>deck_List;
	list<Card>::iterator iter1;
	list<Card>::iterator iter2;
};