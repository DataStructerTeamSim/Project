#include <iostream>
#include <list>

#define GRAPE 0 
#define STRAWBERRY 1
#define BANANA 2
#define APPLE 3
#define COMPUTERWAIT 1
// ���� ����
using namespace std;

//ī�� struct ����, fruit => ������ ���� | number => ������ ����
typedef struct __Card {
	int fruit;
	int number;
}Card;

//���ϸ��� ī�尪 �����ϴ� �迭
Card grape[14]; Card strawberry[14]; Card banana[14]; Card apple[14];

//ī�� ����, �ش� ī�忡 1:5��, 2:3��, 3:3��, 4:2��, 5:1���� number�� �Ҵ��ϴ� �޼ҵ�
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

//��� ����ī�忡 ���� �� ���� �Ҵ� �޼ҵ�
void realSetCard() {
	setCard(grape, GRAPE);
	setCard(strawberry, STRAWBERRY);
	setCard(banana, BANANA);
	setCard(apple, APPLE);
}

