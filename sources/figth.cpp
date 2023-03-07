#include <stdio.h>
#include "figth.h"
#include "trade.h"
#include "level.h"

// Добавить функцию инициализации Player (чекай spawn_item)
Player* Player_Init(int x, int y, int hp, int attack ) {
	Player* player = (Player*)malloc(sizeof(Player));
	player->x = x;
	player->y = y;
	player->hp = hp;
	player->default_attack = attack;
	return player;
}


Enemy* Enemy_Init(int x, int y, int hp, int attack) {
	Enemy* enemy = (Enemy*)malloc(sizeof(Enemy));
	enemy->x = x;
	enemy->y = y;
	enemy->hp = hp;
	enemy->default_attack = attack;
	return enemy;

}



void setPlayer(Player* player, int dx, int dy, int dhp) {
	player->x = dx;
	player->y = dy;
	player->hp = dhp;

}

void movePlayer(Player* player, Level* level) {

	if (GetKeyState('W') < 0) {
		(*player).y--;
		if (is_wall(level, player->x, player->y))
			(*player).y++;

	}
	if (GetKeyState('S') < 0){ 
		(*player).y++;
		if (is_wall(level, player->x, player->y))
			(*player).y--;
	
	}
	if (GetKeyState('A') < 0) {
		(*player).x--;
		if (is_wall(level, player->x, player->y))
			(*player).x++;

	}
	if (GetKeyState('D') < 0) {
		(*player).x++;
		if (is_wall(level, player->x, player->y))
			(*player).x--;

	}

}

void FigthPlayer(Player* player, Enemy* enemy, Inventory* inventory) {
	int n;
	bool leave_fight = false;
	bool f = 0;
	while ((enemy->hp > 0 && player->hp > 0) || leave_fight) {
		do {

			printf("Viberty deistvie - ");    // need check proverka
			scanf("%d", &n);	
		} while (n > 3);
		switch (n) {
		case 1:			// attack
			enemy->hp -= player->default_attack + player->item_weapon->damage;
			player->hp -= enemy->default_attack;
			break;
		case 2:			// leave fight
			player->hp -= enemy->default_attack;
			leave_fight = true;
			break;
		case 3:			// health
			
			for (int i = 0; i < 9; i++) {
				if (inventory->items[i].type == Health) {
					player->hp += 35; //�������� ����� ������� ���� �������
					player->hp -= enemy->default_attack;
					f = 1;
					break;
				}
			}
			if (f == 0){
				printf("Net aptechki");
				player->hp -= enemy->default_attack;
			}
			
		}
	}
	

}