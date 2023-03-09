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
struct Level;
struct Inventory;

struct Player {
	int x;
	int y;
	int hp;
	int default_attack;
	Item* item_weapon;
	int prev_x;
	int prev_y;
};

struct Enemy {
	int x;
	int y;
	int hp;
	int default_attack;
};

Player* Player_Init(int x, int y, int hp, int attack);

Enemy* Enemy_Init(int x, int y, int hp, int attack);

void setPlayer(Player* player, int dx, int dy, int dhp);

void movePlayer(Player* player, Level* level);

void FigthPlayer(Player* player, Enemy* enemy, Inventory* inventory, Level* level);

void Start_Fight(Player* player, Enemy* enemy, Inventory* inventory, Level* level);

bool is_enemy(Level * level, int x, int y);

#endif
