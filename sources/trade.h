// Инвентарь
// Торговля
// 
#ifndef _ITEM_H_
#define _ITEM_H_

#include <stdlib.h>
#include <stdio.h>

enum ItemType {
    None,
    Health,
    Knife
    // ...
};

struct Item {
    int id;
    ItemType type;
    char name; // название
    int value; // зависит от type. если health - то насколько восстановится
    int cost; // цена предмета
    int damage; // урон
};

struct Inventory {
    int cash;
    Item items[9];
};

Item* spawn_item(ItemType type, int value, int id, char name, int cost);
void print_item_info(ItemType type, int value, char name, int cost);
void item_sell(Inventory Inventory_Person, Inventory Inventory_NPC);
void item_buy(Inventory Inventory_Person, Inventory Inventory_NPC);
#endif

