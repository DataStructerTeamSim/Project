#include "Deck.h"

class Player {
public:
	Player() {  }
	~Player() { myDeck.clear(); }
	void setMyDeck(const list<Card>& recive_From_Deck) {
		//recive_From_Deck���� ���� ī�� ��ġ�� myDeck�� ���̴� ���
		list<Card> save(recive_From_Deck);
		for (list<Card>::iterator i = save.begin(); i != save.end(); i++)
		{
			this->myDeck.push_back(*i);
		}
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
		if (this->myDeck.empty() == false)
		{
			frontCard = this->myDeck.front();
			this->myDeck.pop_front();
		}
	}

	list<Card> oOups(int player_num) {
		//�÷��̾ �Ǽ��� ��츦 �ǹ��ϸ� ���� player_num��ŭ ī�带 ���� �����ϴ� �޼ҵ�
		// ���� �÷��̾� ���� ī�� ������ ������, �� ��ü�� �����ϰԲ� ����
		for (size_t i = 0; i < player_num; i++)
		{
			this->myDeck.pop_front();
		}
	}
	Player operator=(const Player &p)
	{
		if (this != &p)
		{
			this->myDeck = p.myDeck;
			this->frontCard = p.frontCard;
			this->iter1 = p.iter1;
			this->iter2 = p.iter2;
			this->frontCard = p.frontCard;
			this->loseOrWin = p.loseOrWin;
		}
		return *this;
	}
private:
	list<Card> myDeck;
	list<Card>::iterator iter1 = myDeck.begin();
	list<Card>::iterator iter2;
	Card frontCard;
	bool loseOrWin = true;
};
