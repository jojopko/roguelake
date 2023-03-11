#ifndef _DIALOG_H_
#define _DIALOG_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32

#include <windows.h>
#define scanf_s scanf_s

#else

#define scanf_s scanf

#endif
struct Level;
struct Player;
struct NPC;
struct Inventory;
struct Enemy;
struct Item;

enum TypeNPC {
	Torgovec,
	Quest1,
	Quest2,
	Provodnik,
	Casino
};

void dialog(Player* player, NPC* npc, Level* level);

bool is_npc(Level* level, int x, int y);

bool is_book(Level* level, int x, int y);

void quest2();

void casino_play(Inventory* Inventory_Person, Player* player);

void spawn_npcs(NPC * npcs, int count, const Level * level);

#endif