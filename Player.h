#include "Deck.h"

class Player {
public:
	Player() {}
	~Player() { myDeck.clear(); }
	void setMyDeck(const list<Card>& recive_From_Deck) {
		//recive_From_Deck���� ���� ī�� ��ġ�� myDeck�� ���̴� ���
	}

	//player�� ���� ������� Ȯ���ϴ� �޼ҵ�
	bool myDeckEmpty() {
		return myDeck.empty();
	}

	//player�� ù��° ī�� ��ȯ
	Card show_Front_Card() {
		return this->frontCard;
	}

	void myTurn() {
		//myDeck���� ī�� 1���� �����ͼ� frontCard�� �ִ� ���
		// 1�� ������ �� ���� ������� Ȯ���ϰ� ��������� �ƹ��͵� ���� �ʴ´�
		// ������ ��� myDeck���� ������ ī�带 pop�Ѵ�.
	}

	list<Card> oOups(int player_num) {
		//�÷��̾ �Ǽ��� ��츦 �ǹ��ϸ� ���� player_num��ŭ ī�带 ���� �����ϴ� �޼ҵ�
		// ���� �÷��̾� ���� ī�� ������ ������, �� ��ü�� �����ϰԲ� ����
	}
	
private:
	list<Card> myDeck;
	list<Card>::iterator iter1 = myDeck.begin();
	list<Card>::iterator iter2;
	Card frontCard;
	bool loseOrWin = true;
};
