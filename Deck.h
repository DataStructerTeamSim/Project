#include "main.h"

//main.h�� ����� ���� ī�带 ����Ͽ� �����ϰ� ���� �� list�� �����ϴ� class

class Deck {
public :
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
	}
	void shuffle_Deck_Card() {
		//Deck_Card���� �迭�� �����ϰ� ����
	}
	list<Card> giveCardToPlayer() {
		//�÷��̾�� ������ ī�� 14�� list�� �����ϴ� �޼ҵ�
		//�� ������ ������ 14�� �����ؾ� �ȴ�.
	}

	//deck�� ���� �ִ� ī�� ����
	void printAllCard() {
		for (iter1 = deck_List.begin(); iter1 != deck_List.end(); iter1++) {
			cout << (*iter1).fruit << " " << (*iter1).number << endl;
		}
	}
private : 
	Card deck_Card[56];
	list<Card>deck_List;
	list<Card>::iterator iter1;
	list<Card>::iterator iter2;
};