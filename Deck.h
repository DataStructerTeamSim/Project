#include "main.h"
#include<cstdlib>
//main.h�� ����� ���� ī�带 ����Ͽ� �����ϰ� ���� �� list�� �����ϴ� class

class Deck {
public:
	
	Deck() {
		realSetCard(); // �������� ī�� �迭 �� ����
		setDeck_Card(); //�ٸ��� ����
		shuffle_Deck_Card(); // �ٸ��� ����
							 //Deck_Card ���� list�� ����� �ڵ�
		for (Card a : deck_Card) {
			deck_List.push_back(a);
		}
	}
	~Deck() { deck_List.clear(); }

	void setDeck_Card() {
		//���� ī����� deck_Card�� �ٿ��� �ֱ�
		copy(grape, grape + 14, deck_Card);//���Կ� �迭�����
		copy(banana, banana + 14, deck_Card + 14);
		copy(strawberry, strawberry + 14, deck_Card + 28);
		copy(apple, apple + 14, deck_Card + 42);
	}
	void shuffle_Deck_Card() {
		//Deck_Card���� �迭�� �����ϰ� ����
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
		//�÷��̾�� ������ ī�� 14�� list�� �����ϴ� �޼ҵ�
		//�� ������ ������ 14�� �����ؾ� �ȴ�.
		list<Card>playerDeck;
		for (size_t i = 0; i < 14; i++)
		{
			playerDeck.push_back(deck_List.front());
			deck_List.pop_front();
		}
		return playerDeck;
	}

	//deck�� ���� �ִ� ī�� ����
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
