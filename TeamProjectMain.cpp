#include "Player.h"
#include<time.h>
#include<conio.h>
void giveTurnToPlayer(Player& player, list<Card>& onTable);
bool numberMatch(list<Card>& onTable);
bool playerInput(bool match);


int main() {
	//�� ����
	Deck d = Deck();
	//�÷��̾� ���� -> ����ڴ� player 0;
	Player p[4];

	//�� ����
	for (int i = 0; i < 4; i++) {
		p[i].setMyDeck(d.giveCardToPlayer());
	}

	int i = 0;
	//���� ����
	while (1) {//��ü���� ���� ���� - �÷��̾��� ���� ����
		bool judge1 = false;
		bool judge2 = false;
		list<Card> onTable;
		do {//�÷��̾�� ���� ����
			giveTurnToPlayer(p[i], onTable);
			judge1 = numberMatch(onTable);
			judge2 = playerInput(judge1);
		} while (!judge1 || !judge2);
	}
	return 0;
}
void giveTurnToPlayer(Player& player, list<Card>& onTable) {
	//�÷��̾�� turn�� �ְ� frontī�带 onTable�� �ֱ�
}
bool numberMatch(const list<Card>& onTable) {
	//onTable�� �ִ� ī����� fruit�� number�� ��ġ�Ͽ� ���� fruit�� number���� 5�� true����
	//������ false
}
bool playerInput(bool match) {
	//player�� cin�� ����
	//match�� true�� ��� COMPUTERWAiT �� ��ŭ �Է´��ð� ����
	//true�� ����
	//match�� false�� ��� 2�ʸ�ŭ ���
	//���� 2�� �ȿ� player�� �Է��� �ߴٸ� true����
	//2�ʰ� �Ѿư� ���� �Է� x �� false ����
	clock_t endwait;
	endwaitT = clock() + COMPUTERWAIT * CLOCKS_PER_SEC;
	endwaitF = clock() + (COMPUTERWAIT + 1)*CLOCKS_PER_SEC;
	if (match == true)
	{
		while (clock()<endwaitT)
		{
			if (kbhit())
			{
				
			}
		}
		return true;
	}
	else
	{
		while (clock()<endwaitF)
		{
			if (kbhit())
				return true;
		}
		return false;
	}
}