#include "Deck.h"

class Player {
public:
	Player() {  }
	~Player() { myDeck.clear(); }
	void setMyDeck(const list<Card>& recive_From_Deck) {
		//recive_From_Deck에서 받은 카드 뭉치를 myDeck에 붙이는 기능
		list<Card> save(recive_From_Deck);
		for (list<Card>::iterator i = save.begin(); i != save.end(); i++)
		{
			this->myDeck.push_back(*i);
		}
	}
	
	//player의 덱이 비었는지 확인하는 메소드
	bool myDeckEmpty() {
		return myDeck.empty();
	}

	//player의 첫번째 카드 반환
	Card show_Front_Card() {
		return this->frontCard;
	}

	void myTurn() {
		//myDeck에서 카드 1장을 가져와서 frontCard에 넣는 기능
		// 1장 가져올 때 덱이 비었는지 확인하고 비어있으면 아무것도 하지 않는다
		// 가져올 경우 myDeck에서 가져온 카드를 pop한다.
		if (this->myDeck.empty() == false)
		{
			frontCard = this->myDeck.front();
			this->myDeck.pop_front();
		}
	}

	list<Card> oOups(int player_num) {
		//플래이어가 실수할 경우를 의미하며 덱에 player_num만큼 카드를 뺴서 리턴하는 메소드
		// 만약 플레이어 보다 카드 개수가 적으면, 덱 전체를 리턴하게끔 구현
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
