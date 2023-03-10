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
struct Camera;

struct Player {
	int x;
	int y;
	int hp;
	int default_attack;
	Item* item_weapon;
	int prev_x;
	int prev_y;
	bool killQuest = 0;
	int killQuestCounter = 0;
	bool findQuest = 0;
	Camera* cam;
	Inventory * inventory;
};

struct Enemy {
	int x;
	int y;
	int hp;
	int default_attack;
	int money;
};

Player* Player_Init(int x, int y, int hp, int attack);

Enemy* Enemy_Init(int x, int y, int hp, int attack, int money);

void setPlayer(Player* player, int dx, int dy, int dhp);

void movePlayer(Player* player, Level* level);

void FigthPlayer(Player* player, Enemy* enemy, const Level* level);

void Start_Fight(Player* player, Enemy* enemy, const Level* level);

bool is_enemy(const Level * level, int x, int y);

void Enemy_AI(Enemy* enemy, const Level* level);

void spawn_items(Item * items, int count, const Level * level);

void spawn_enemies(Enemy * enemies, int count, const Level * level);

void move_enemies(Enemy * enemies, int count, const Level * level, Player * player);

#endif
