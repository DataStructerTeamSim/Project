#include <iostream>
#include <list>

#define GRAPE 0 
#define STRAWBERRY 1
#define BANANA 2
#define APPLE 3
#define COMPUTERWAIT 1
// 과일 정의
using namespace std;

//카드 struct 정의, fruit => 과일의 정보 | number => 과일의 개수
typedef struct __Card {
	int fruit;
	int number;
}Card;

//과일마다 카드값 저장하는 배열
Card grape[14]; Card strawberry[14]; Card banana[14]; Card apple[14];

//카드 설정, 해당 카드에 1:5개, 2:3개, 3:3개, 4:2개, 5:1개씩 number에 할당하는 메소드
void setCard(Card *card, int fruitType) {
	for (int i = 0; i < 14; i++) {
		card[i].fruit = fruitType;
		if (i < 5)
			card[i].number = 1;
		else if (i >= 5 && i < 8)
			card[i].number = 2;
		else if (i >= 8 && i < 11)
			card[i].number = 3;
		else if (i >= 11 && i < 13)
			card[i].number = 4;
		else
			card[i].number = 5;
	}
}

//모든 과일카드에 숫자 및 과일 할당 메소드
void realSetCard() {
	setCard(grape, GRAPE);
	setCard(strawberry, STRAWBERRY);
	setCard(banana, BANANA);
	setCard(apple, APPLE);
}

