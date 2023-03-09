#ifndef _DIALOG_H_
#define _DIALOG_H_

#include <stdio.h>
#ifdef _WIN32

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
	Provodnik
};

void dialog(Player* player, NPC* npc, Inventory* Inventory_Person, Inventory* Invenroty_NPC, Enemy* enemy, Level* level, Item* item);
bool is_npc(Level* level, int x, int y);
bool is_book(Level* level, int x, int y);
void quest2(Item* item);
#endif