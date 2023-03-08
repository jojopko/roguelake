// Инвентарь
// Торговля
// 
#ifndef _ITEM_H_
#define _ITEM_H_

#include <stdlib.h>
#include <stdio.h>
#include "figth.h"
#include "dialog.h"

#ifdef _WIN32

#define scanf_s scanf_s

#else

#define scanf_s scanf

#endif

struct NPC {
    int x;
    int y;
    TypeNPC type;
    Inventory* Inventory_NPC;
};

enum ItemType {
    None,
    Health,
    Melee,
    Money,
    Armor,
    Ranged
    // ...
};

struct Item {
    int id;
    ItemType type;
    const char* name; // название
    int value; // зависит от type. если health - то насколько восстановится
    int cost; // цена предмета
    int damage; // урон
    int x;
    int y;
};

struct Inventory {
    int cash;
    Item items[9];
};


Item* spawn_item(ItemType type, int value, int id, const char* name, int cost, int damage, int x, int y);
void add_item_to_inventory(Inventory* Inventory_Person, Player* player, Item* item);
void item_sell(Inventory* Inventory_Person, Inventory* Inventory_NPC);
void item_buy(Inventory* Inventory_Person, Inventory* Inventory_NPC);
void emptying_the_array(Inventory* Gear);
NPC* spawn_NPC(int x, int y, Inventory Inventory_NPC);

void print_item_info(ItemType type, int value, const char* name, int cost, int damage);
Item* items(ItemType type, int value, int id, const char* name, int cost, int damage);
void item_sell_dop(Inventory* Inventory_Person, Inventory* Inventory_NPC);
void item_buy_dop(Inventory* Inventory_Person, Inventory* Inventory_NPC);
#endif

