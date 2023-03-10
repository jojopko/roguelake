#include "dialog.h"
#include "figth.h"
#include "trade.h"
#include "level.h"


bool is_npc(Level* level, int x, int y) 
{
	char* field = level->field;
	int index = y * level->w + x;
	if (field[index] == '&')
		return true;
	if (field[index] == 'O')
		return true;
	if (field[index] == '8')
		return true;
	if (field[index] == 'Q')
		return true;
	return false;
}

bool is_book(Level* level, int x, int y)
{
	char* field = level->field;
	int index = y * level->w + x;
	if (field[index] == 'K')
		return true;
	return false;
}

void dialog(Player* player, NPC* npc, const Level* level)
{
	int answer_choice;
	// if (is_npc(level, player->x, player->y))
	if (npc->x == player->x && npc->y == player->y)
	{
		if (npc->type == Provodnik)
		{
			printf("Zdravstvyi, hochesh' otpravit'sya na sledyyshi yroven'?\n 1 - Da \n 2 - Net (leave)");
			do {
				scanf_s("%d", &answer_choice);
			} while (answer_choice > 2 || answer_choice < 1);
			switch (answer_choice)
			{
			case 1: printf("Da"); break; // add next level
			case 2:
				printf("Net");
				player->x = player->prev_x;
				player->y = player->prev_y;
				break; // add leave
			}
		}
		else if (npc->type == Torgovec)
		{
			printf("Zdravstvyi, hochesh' prodat' ili kypit' predmeti?\n 1 - Kypit'\n 2 - Prodat'\n 3 - Leave");
			do {
				scanf_s("%d", &answer_choice);
			} while (answer_choice > 3 || answer_choice < 1);
			switch (answer_choice)
			{
			case 1: item_buy(player->inventory, npc->Inventory_NPC); break;
			case 2: item_sell(npc->Inventory_NPC, player->inventory); break;
			case 3: 
				player->x = player->prev_x;
				player->y = player->prev_y;
				break; //leave
			}
		}
		else if (npc->type == Quest1)
		{
			printf("Zdravstvyi pytnik, pomogi mne s odim delom, i ya tebya voznagrajy. Neobhodimo ystranit' bandy razboinikov. Ybey 10 vragov i polychish nagrady.\n 1 - Ya soglsen.\n 2 - Ya ne bydy brat'sya za eto. (Leave)");
			do {
				scanf_s("%d", &answer_choice);
			} while (answer_choice > 2 || answer_choice < 1);
			switch (answer_choice)
			{
			case 1: player->killQuest = 1;
				printf("Naidite i ybeite 10 vragov!\n");
				system("pause");
				player->x = player->prev_x;
				player->y = player->prev_y; 
				break; //Zapysk mission
			case 2:
				player->x = player->prev_x;
				player->y = player->prev_y; 
				break; //leave
			}
		}
		else if (npc->type == Quest2)
		{
			printf("Zdravstvyi pytnik, pomogi mne nayti knigy, ona gde-to nepodaleky, viglyadit kak (K). Prinesi mne ee.\n 1 - Ya soglsen.\n 2 - Polychit' nagrady\n 3 - Ya ne bydy brat'sya za eto. (Leave)");
			do {
				scanf_s("%d", &answer_choice);
			} while (answer_choice > 3 || answer_choice < 1);
			switch (answer_choice)
			{
			case 1: 
				quest2();
				printf("Naidite knigy i vernites' k neznakomcy.\n");
				system("pause");
				player->x = player->prev_x;
				player->y = player->prev_y;
				break; //Zapysk mission
			case 2:
				if (player->findQuest == 1)
				{
					printf("Spasibo za pomosh'!\n");
					player->inventory->cash += 200;
					system("pause");
				}
				else
				{
					printf("Ti mne esh'e ne prines moy knigy!!!");
					system("pause");
				}
					player->x = player->prev_x;
					player->y = player->prev_y;
				//leave
				break; //leave
			}
		}
		else if (npc->type == Casino)
		{
			printf("Privet, ne hochesh' sigrat' v kosti? \n 1 - Da, zvychit neploho \n 2 - Mne eto neinteresno (Leave)\n");
			do {
				scanf_s("%d", &answer_choice);
			} while (answer_choice > 2 || answer_choice < 1);
			switch (answer_choice)
			{
			case 1:
				if (player->inventory->cash <= 0)
				{
					printf("Y vas ne hvataet monet!\n");
					system("pause");
				}
				else
				{
					casino_play(player->inventory, player);
				}
				player->x = player->prev_x;
				player->y = player->prev_y;
				break;
			case 2:
				player->x = player->prev_x;
				player->y = player->prev_y;
				break; //leave
			}
		}
	}

}

void casino_play(Inventory* Inventory_Person, Player* player)
{
	int p_dice1, p_dice2, c_dice1, c_dice2, bet;
	srand(time(NULL));
	printf("Sdelayte stavky. \n");
	do {
		scanf_s("%d", &bet);
		if (Inventory_Person->cash < bet) printf("Vasha stavka bol'she imeysh'ihsya y vas deneg\n");
	} while (Inventory_Person->cash < bet);
	if (Inventory_Person->cash >= bet)
	{
		printf("Nazhmite lybuy knopky chtobi brosit' kosti\n");
		system("pause");
		p_dice1 = rand() % 12;
		p_dice2 = rand() % 12;
		c_dice1 = rand() % 12;
		c_dice2 = rand() % 12;
		if ((p_dice1 + p_dice2) > (c_dice1 + c_dice2))
		{
			printf("Vi pobedili! Derzhite vash priz.\n");
			Inventory_Person->cash += bet;
			system("pause");
		}
		else
		{
			printf("Vi proigrali!\n");
			Inventory_Person->cash -= bet;
			system("pause");
		}
	}
	printf("Prihodi esh'e!\n");
	system("pause");
}

void quest2()
{
	spawn_item(Quest, 1, 1001, "Kniga", 0, 0, 16, 6);
}

void spawn_npcs(NPC * npcs, int count, const Level * level) {
    char * field = level->field;
    int npcs_id = 0;
    for (int i = 0; i < count; i++) {
        npcs[i].x = -1231;
        npcs[i].y = -1231;
    }
    for (int y = 0; y < level->h; y++) {
        for (int x = 0; x < level->w; x++) {
            int index = y * level->w + x;
            char c = field[index];
            if (c == '&') {
                int rand_money = rand() % 1000 + 1;
                // enemies[enemy_id] = *Enemy_Init(x, y, 50, 10, rand_money);
                npcs[npcs_id].type = Torgovec;
                Inventory * inv = (Inventory *) malloc(sizeof(Inventory));
				inv->cash = rand_money;
				inv->items[0] = *spawn_item(Health, 100, 123123, "Health\0", 50, 0, -1, -1);
				inv->items[1] = *spawn_item(Health, 100, 12311233, "Health\0", 50, 0, -1, -1);
				inv->items[2] = *spawn_item(Health, 100, 1236123, "Health\0", 50, 0, -1, -1);
				inv->items[3] = *spawn_item(Melee, 10, 123133765, "Knife\0", 150, 10, -1, -1);
				inv->items[4] = *spawn_item(None, 0, 0, "a\0", 0, 0, -1, -1);
				inv->items[5] = *spawn_item(None, 0, 0, "a\0", 0, 0, -1, -1);
				inv->items[6] = *spawn_item(None, 0, 0, "a\0", 0, 0, -1, -1);
				inv->items[7] = *spawn_item(None, 0, 0, "a\0", 0, 0, -1, -1);
				inv->items[8] = *spawn_item(None, 0, 0, "a\0", 0, 0, -1, -1);
				npcs[npcs_id].Inventory_NPC = inv;
                npcs[npcs_id].x = x;
                npcs[npcs_id].y = y;
                npcs_id++;
            }
            if (npcs_id >= count) {
                return;
            }
        }
    }
}
