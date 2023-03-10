#include <stdio.h>
#include<stdlib.h>
#include "figth.h"
#include "trade.h"
#include "level.h"
//Боевка. Если игрок и враг в одной клетке, то мы начинаем бой. Если игрок бежит из битвы, то мы возвращаемся в прошлую клетку. 
//Если побеждаем остаемся в той же клетке. @MXTIGV187
//Боевка.Протестировать всю систему : создать несколько предметов разных типов, эксперементировать с инвентарями в условиях боя.

// Добавить функцию инициализации Player (чекай spawn_item)
Player* Player_Init(int x, int y, int hp, int attack) {
	Player* player = (Player*)malloc(sizeof(Player));
	player->x = x;
	player->y = y;
	player->hp = hp;
	player->default_attack = attack;
	return player;
}


Enemy* Enemy_Init(int x, int y, int hp, int attack, int money) {
	Enemy* enemy = (Enemy*)malloc(sizeof(Enemy));
	enemy->x = x;
	enemy->y = y;
	enemy->hp = hp;
	enemy->default_attack = attack;
	enemy->money = money;
	return enemy;

}

void Enemy_AI(Enemy* enemy, const Level* level) {
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
	if (GetKeyState(VK_ESCAPE) < 0) {
		system("cls");
		exit(0);
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

void Start_Fight(Player* player, Enemy* enemy, const Level* level) {
	if (player->x == enemy->x && player->y == enemy->y){
		FigthPlayer(player, enemy, level);
	}
}


void FigthPlayer(Player* player, Enemy* enemy, const Level* level) {
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
			for (int i = 0; i < 9; i++){
				if (player->inventory->items[i].type == Melee){
					enemy->hp -= player->inventory->items[i].value;
				}
			}
			player->hp -= enemy->default_attack;
			enemy->hp -= player->default_attack;
			break;
		case 2:			// leave fight
			player->x = player->prev_x;
			player->y = player->prev_y;
			player->hp -= enemy->default_attack;
			leave_fight = true;
			break;
		case 3:			// health
			for (int i = 0; i < 9; i++) {
				if (player->inventory->items[i].type == Health) {
					player->hp += player->inventory->items[i].value; //�������� ����� ������� ���� �������
					player->hp -= enemy->default_attack;
					player->inventory->items[i].type = None;
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
	if(enemy->hp <= 0){
		player->inventory->cash += 50;
	}
	if (player->killQuest == 1 && enemy->hp <= 0)
	{
		player->killQuestCounter += 1;
		if (player->killQuestCounter >= 10)
		{
			player->inventory->cash += 200;
			player->killQuest = 0;
		}
	}
}

// FIXME: почему то кода выходишь из боя, потом нельзя сного начать биться
bool is_enemy(const Level* level, int x, int y) {
    char* field = level->field;
    int index = y * level->w + x;
    if (field[index] == 'A')
        return true;
    return false;
}

void move_enemies(Enemy * enemies, int count, const Level * level, Player * player) {
	for (int i = 0; i < count; i++) {
		Enemy_AI(&enemies[i], level);
		Start_Fight(player, &enemies[i], level);
	}
}

void spawn_enemies(Enemy * enemies, int count, const Level * level) {
    char * field = level->field;
    int enemy_id = 0;
    for (int i = 0; i < count; i++) {
        enemies[i].hp = 0;
    }
    for (int y = 0; y < level->h; y++) {
        for (int x = 0; x < level->w; x++) {
            int index = y * level->w + x;
            char c = field[index];
            if (c == 'A') {
                int rand_money = rand() % 100 + 1;
                // enemies[enemy_id] = *Enemy_Init(x, y, 50, 10, rand_money);
                enemies[enemy_id].x = x;
                enemies[enemy_id].y = y;
                enemies[enemy_id].hp = 50;
                enemies[enemy_id].default_attack = 10;
                enemies[enemy_id].money = rand_money;
                enemy_id++;
            }
            if (enemy_id >= count) {
                return;
            }
        }
    }
}
