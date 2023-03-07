#include <stdio.h>
#include "figth.h"
#include "trade.h"
void setPlayer(Player* setspawn, Player* sethp, Player* setarmor, int dx, int dy, int dhp) {
	(*setspawn).x = dx;
	(*setspawn).y = dy;
	(*sethp).hp = dhp;

}

void movePlayer(Player* player) {
	if (GetKeyState('W') < 0) (*player).y--;
	if (GetKeyState('S') < 0) (*player).y++;
	if (GetKeyState('A') < 0) (*player).x--;
	if (GetKeyState('D') < 0) (*player).x++;
}
void FigthPlayer(Player* player, Enemy* enemy) {
	int n;
	bool leave_fight = false;
	while ((enemy->hp > 0 && player->hp > 0) || leave_fight) {
		printf("Viberty deistvie - ");    // ������� �������� 
		scanf("%d", &n);
		switch (n) {
		case 1:			// �����
			enemy->hp -= player->default_attack + player->item_weapon->damage;
			player->hp -= enemy->default_attack;
			break;
		case 2:			// �������
			player->hp -= enemy->default_attack;
			leave_fight = true;
			break;
		case 3:			// ���������
			player->hp += 100000; //�������� ����� ������� ���� �������
			player->hp -= enemy->default_attack;
			break;
		}
	}
	

}