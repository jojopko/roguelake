#ifndef _FIGTH_H_
#define _FIGTH_H_

#include <math.h>

#ifdef _WIN32

#include <Windows.h>

#else

short GetKeyState(int virtkey);

#endif

// стр Игрока
// стр Врага

// Боевка
// Перемещение
struct Item;

struct Player {
	int x;
	int y;
	int hp;
	int default_attack;
	Item* item_weapon;
};

struct Enemy {
	int x;
	int y;
	int hp;
	int default_attack;
};
void Player_Init(Player* player);

void Enemy_Init(Enemy* enemy);

void setPlayer(Player* player, int dx, int dy, int dhp);

void movePlayer(Player* player);

void FigthPlayer(Player* php, Enemy* ehp); //php-хп игрока ehp хп врага

#endif
