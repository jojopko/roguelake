#include <stdio.h>
#include<stdlib.h>
#include "figth.h"
#include "trade.h"
#include "level.h"
//Боевка. Если игрок и враг в одной клетке, то мы начинаем бой. Если игрок бежит из битвы, то мы возвращаемся в прошлую клетку. 
//Если побеждаем остаемся в той же клетке. @MXTIGV187
//Боевка.Протестировать всю систему : создать несколько предметов разных типов, эксперементировать с инвентарями в условиях боя.

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

void Enemy_AI(Enemy* enemy, Level* level) {
	int hp_post;
	int random;
	hp_post=enemy->hp;
	if (enemy->hp > 0) {
		random = rand() % 16;
		if (random == 1) {
			enemy->x++;
			if (is_wall(level, enemy->x, enemy->y))
				(*enemy).x--;
		}
		if (random == 2) {
			enemy->x--;
			if (is_wall(level, enemy->x, enemy->y))
				(*enemy).x++;
		}
		if (random == 3) {
			enemy->y++;
			if (is_wall(level, enemy->x, enemy->y))
				(*enemy).y--;
		}
		if (random == 4) {
			enemy->y--;
			if (is_wall(level, enemy->x, enemy->y))
				(*enemy).y++;
		}
	}

}



void setPlayer(Player* player, int dx, int dy, int dhp) {
	player->x = dx;
	player->y = dy;
	player->hp = dhp;

}

#ifdef _WIN32
// Если это винда, то будет этот код

void movePlayer(Player* player, Level* level) {
	player->prev_x = player->x;
	player->prev_y = player->y;
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

#else
// На линуксе -- этот

void movePlayer(Player* player, Level* level) {
	int c = getch();
	
	if (c == 'w') {
		player->prev_x = player->x;
		player->prev_y = player->y;
		(*player).y--;
		if (is_wall(level, player->x, player->y))
			(*player).y++;
	}
	if (c == 's'){ 
		player->prev_x = player->x;
		player->prev_y = player->y;
		(*player).y++;
		if (is_wall(level, player->x, player->y))
			(*player).y--;
	}
	if (c == 'a') {
		player->prev_x = player->x;
		player->prev_y = player->y;
		(*player).x--;
		if (is_wall(level, player->x, player->y))
			(*player).x++;
	}
	if (c == 'd') {
		player->prev_x = player->x;
		player->prev_y = player->y;
		(*player).x++;
		if (is_wall(level, player->x, player->y))
			(*player).x--;
	}
}

#endif

void Start_Fight(Player* player, Enemy* enemy, Inventory* inventory, Level* level) {
	// if (is_enemy(level, player->x, player->y)) {
	// 	FigthPlayer(player, enemy, inventory,level);
	// }

	if (player->x == enemy->x && player->y == enemy->y){
		FigthPlayer(player, enemy, inventory, level);
	}
}


void FigthPlayer(Player* player, Enemy* enemy, Inventory* inventory, Level* level) {
	int n;
	bool leave_fight = false;
	bool f = 0;
	while ((enemy->hp > 0 && player->hp > 0) && !leave_fight) {
		do {

			printf("Viberty deistvie - ");    // need check proverka
			scanf("%d", &n);	
		} while (n > 3);
		switch (n) {
		case 1:			// attack
			if (player->item_weapon != NULL && player->item_weapon->type!=None) {
				player->hp -= enemy->default_attack;
				enemy->hp -= player->default_attack + player->item_weapon->value;
			}
			else {
				player->hp -= enemy->default_attack;
				enemy->hp -= player->default_attack;
				
			}
			break;
		case 2:			// leave fight
			player->x = player->prev_x;
			player->y = player->prev_y;
			player->hp -= enemy->default_attack;
			leave_fight = true;
			break;
		case 3:			// health
			
			for (int i = 0; i < 9; i++) {
				if (inventory->items[i].type == Health) {
					player->hp += inventory->items[i].value; //�������� ����� ������� ���� �������
					player->hp -= enemy->default_attack;
					f = 1;
					break;
				}
			}
			if (f == 1){
				// printf("Net aptechki");
				player->hp -= enemy->default_attack;
			}
			
		}
	}
	if (player->killQuest == 1 && enemy->hp <= 0)
	{
		player->killQuestCounter += 1;
		if (player->killQuestCounter >= 10)
		{
			inventory->cash += 200;
			player->killQuest = 0;
		}
	}
}

// FIXME: почему то кода выходишь из боя, потом нельзя сного начать биться
bool is_enemy(Level* level, int x, int y) {
    char* field = level->field;
    int index = y * level->w + x;
    if (field[index] == 'A')
        return true;
    return false;
}
