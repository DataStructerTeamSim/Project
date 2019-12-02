#include "main.h"
#include<cstdlib>
//main.h에 선언된 과일 카드를 사용하여 랜덤하게 섞은 후 list에 저장하는 class

class Deck {
public:
	
	Deck() {
		realSetCard(); // 전역변수 카드 배열 값 설정
		setDeck_Card(); //다리아 구현
		shuffle_Deck_Card(); // 다리아 구현
							 //Deck_Card 값을 list로 만드는 코드
		for (Card a : deck_Card) {
			deck_List.push_back(a);
		}
	}
	~Deck() { deck_List.clear(); }

	void setDeck_Card() {
		//과일 카드들을 deck_Card에 붙여서 넣기
		copy(grape, grape + 14, deck_Card);//삽입용 배열만들기
		copy(banana, banana + 14, deck_Card + 14);
		copy(strawberry, strawberry + 14, deck_Card + 28);
		copy(apple, apple + 14, deck_Card + 42);
	}
	void shuffle_Deck_Card() {
		//Deck_Card들의 배열을 랜덤하게 섞기
		int temp;
		Card save;
		for (size_t i = 0; i < 56; i++)
		{
			temp = rand() % 56;
			save = deck_Card[i];
			deck_Card[i] = deck_Card[temp];
			deck_Card[temp] = save;
		}
	}
	list<Card> giveCardToPlayer() {
		//플레이어에게 제공할 카드 14장 list를 리턴하는 메소드
		//줄 때마다 덱에서 14장 제거해야 된다.
		list<Card>playerDeck;
		for (size_t i = 0; i < 14; i++)
		{
			playerDeck.push_back(deck_List.front());
			deck_List.pop_front();
		}
		return playerDeck;
	}

	//deck에 섞여 있는 카드 보기
	void printAllCard() {
		for (iter1 = deck_List.begin(); iter1 != deck_List.end(); iter1++) {
			cout << (*iter1).fruit << " " << (*iter1).number << endl;
		}
	}
	
private:
	Card deck_Card[56];
	list<Card>::iterator iter1;
	list<Card>::iterator iter2;
	list<Card>deck_List;
};
