#include "trade.h"


Item* spawn_item(ItemType type, int value, int id, const char* name, int cost, int damage, int x, int y)
{
    Item* item = (Item*)malloc(sizeof(Item));
    item->id = id;
    item->type = type;
    item->name = name;
    item->cost = cost;
    item->value = value;
    item->damage = damage;
    item->x = x;
    item->y = y;
    return item;
}

NPC* spawn_NPC(int x, int y, Inventory Inventory_NPC)
{
    NPC* npc = (NPC*)malloc(sizeof(NPC));
    npc->x = x;
    npc->y = y;
    npc->Inventory_NPC = &Inventory_NPC;
    return npc;
}


//����� ���������� � ��������
void print_item_info(ItemType type, int value, const char* name, int cost, int damage)
{
    printf("%s\n%d\n%d\n%d\n", name, damage, value, cost);
}
//��������
Item* items(ItemType type, int value, int id, const char* name, int cost, int damage)
{
    Item* healing_potion = (Item*)malloc(sizeof(Item));
    healing_potion->type = Health;
    healing_potion->cost = 50;
    healing_potion->damage = 0;
    healing_potion->name = "Zel'e regeneracii";
    healing_potion->value = 1;

    Item* sword = (Item*)malloc(sizeof(Item));
    sword->type = Melee;
    sword->cost = 100;
    sword->damage = 20;
    sword->name = "Mech";
    sword->value = 1;

    Item* bow = (Item*)malloc(sizeof(Item));
    bow->type = Ranged;
    bow->cost = 120;
    bow->damage = 25;
    bow->name = "Lyk";
    bow->value = 1;

    Item* breastplate = (Item*)malloc(sizeof(Item));
    breastplate->type = Armor;
    breastplate->cost = 70;
    breastplate->damage = 0;
    breastplate->name = "Nagrydnik";
    breastplate->value = 1;
    return healing_potion, sword, bow, breastplate;
}

void add_item_to_inventory(Inventory* Inventory_Person, Player* player, Item* item)
{
    bool f = 0; 
    if ((player->x == item->x) && (player->y == item->y))
        for (int i = 0; i < 9; i++)
        {
            if (Inventory_Person->items[i].type == None)
            {
                if (item->type == Money)
                {
                    Inventory_Person->cash += item->value;
                    break;
                }
                f = 1;
                Inventory_Person->items[i] = *item;
                break;
            }
        }
    if (f == 0)
        printf("Net svobodnogo mesta\n");
}

void item_sell_dop(Inventory* Inventory_Person, Inventory* Inventory_NPC)
{
    bool f = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (Inventory_NPC->items[j].type == None)
            {
                Inventory_NPC->items[j] = Inventory_Person->items[i];
                Inventory_Person->items[i].type = None;
                Inventory_NPC->cash -= Inventory_Person->items[i].cost;
                Inventory_Person->cash += Inventory_Person->items[i].cost;
                f = 1;
                break;
            }
        }
        if (f == 1)
             break;
    }
    if (f == 0)
        printf("Inventar' torgovca polon");
}

void item_buy_dop(Inventory* Inventory_Person, Inventory* Inventory_NPC) 
{
    bool f = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (Inventory_Person->items[j].type == None)
            {
                Inventory_Person->items[j] = Inventory_NPC->items[i];
                Inventory_NPC->items[i].type = None;
                Inventory_Person->cash -= Inventory_NPC->items[i].cost;
                Inventory_NPC->cash += Inventory_NPC->items[i].cost;
                f = 1;
                break;
            }
            else printf("Inventar' igroka polon");
        }
        if (f == 1)
            break;
    }
    if (f == 0)
        printf("Inventar' torgovca polon");
}
//������� ���������
void item_sell(Inventory* Inventory_Person, Inventory* Inventory_NPC)
{
    int select_item;
    printf("Vvedite nomer predmeta, kotoriy hotite prodat'\n");
    do {
        scanf_s("%d", &select_item);
        if (select_item > 9 || select_item < 1) printf("Ykazan neverniy nomer predmeta\n");
    } while (select_item > 9 || select_item < 1);
    switch (select_item)
    {
    case 1:
        if (Inventory_Person->items[0].type != None)
            item_sell_dop(Inventory_Person, Inventory_NPC);
        else printf("Yacheyka pysta\n");
        break;
    case 2:
        if (Inventory_Person->items[1].type != None)
            item_sell_dop(Inventory_Person, Inventory_NPC);
        else printf("Yacheyka pysta\n");
        break;
    case 3:
        if (Inventory_Person->items[2].type != None)
            item_sell_dop(Inventory_Person, Inventory_NPC);
        else printf("Yacheyka pysta\n");
        break;
    case 4:
        if (Inventory_Person->items[3].type != None)
            item_sell_dop(Inventory_Person, Inventory_NPC);
        else printf("Yacheyka pysta\n");
        break;
    case 5:
        if (Inventory_Person->items[4].type != None)
            item_sell_dop(Inventory_Person, Inventory_NPC);
        else printf("Yacheyka pysta\n");
        break;
    case 6:
        if (Inventory_Person->items[5].type != None)
            item_sell_dop(Inventory_Person, Inventory_NPC);
        else printf("Yacheyka pysta\n");
        break;
    case 7:
        if (Inventory_Person->items[6].type != None)
            item_sell_dop(Inventory_Person, Inventory_NPC);
        else printf("Yacheyka pysta\n");
        break;
    case 8:
        if (Inventory_Person->items[7].type != None)
            item_sell_dop(Inventory_Person, Inventory_NPC);
        else printf("Yacheyka pysta\n");
        break;
    case 9:
        if (Inventory_Person->items[8].type != None)
            item_sell_dop(Inventory_Person, Inventory_NPC);
        else printf("Yacheyka pysta\n");
        break;
        
    default:
        printf("Ykazan neverniy nomer predmerta");
        break;
    }
}
//������� ���������
void item_buy(Inventory* Inventory_Person, Inventory* Inventory_NPC)
{
    int select_item;
    printf("Vvedite nomer predmeta, kotoriy hotite kypit'\n");
    do {
        scanf_s("%d", &select_item);
        if (select_item > 9 || select_item < 1) printf("Ykazan neverniy nomer predmeta\n");
    } while (select_item > 9 || select_item < 1);
    switch (select_item)

    {
    case 1:
        if (Inventory_NPC->items[0].type != None)
            item_buy_dop(Inventory_Person, Inventory_NPC);
        else printf("Yacheyka pysta\n");
        break;
    case 2: 
        if (Inventory_NPC->items[1].type != None)
            item_buy_dop(Inventory_Person, Inventory_NPC);
        else printf("Yacheyka pysta\n");
        break;
    case 3:
        if (Inventory_NPC->items[2].type != None)
            item_buy_dop(Inventory_Person, Inventory_NPC);
        else printf("Yacheyka pysta\n");
        break;
    case 4:
        if (Inventory_NPC->items[3].type != None)
            item_buy_dop(Inventory_Person, Inventory_NPC);
        else printf("Yacheyka pysta\n");
        break;
    case 5:
        if (Inventory_NPC->items[4].type != None)
            item_buy_dop(Inventory_Person, Inventory_NPC);
        else printf("Yacheyka pysta\n");
        break;
    case 6:
        if (Inventory_NPC->items[5].type != None)
            item_buy_dop(Inventory_Person, Inventory_NPC);
        else printf("Yacheyka pysta\n");
        break;
    case 7:
        if (Inventory_NPC->items[6].type != None)
            item_buy_dop(Inventory_Person, Inventory_NPC);
        else printf("Yacheyka pysta\n");
        break;
    case 8:
        if (Inventory_NPC->items[7].type != None)
            item_buy_dop(Inventory_Person, Inventory_NPC);
        else printf("Yacheyka pysta\n");
        break;
    case 9:
        if (Inventory_NPC->items[8].type != None)
            item_buy_dop(Inventory_Person, Inventory_NPC);
        else printf("Yacheyka pysta\n");
        break;

    default: printf("Ykazan neverniy nomer predmerta");
        break;
    }
}
//����������� ���������
void emptying_the_array(Inventory* Gear)
{
    for (int i = 1; i < 9; i++) {
        Gear->items[i].type = None;
    }
}

