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

void dialog(Player* player, NPC* npc, Inventory* Inventory_Person, Inventory* Invenroty_NPC, Level* level)
{
	int answer_choice;
	// if (is_npc(level, player->x, player->y))
	if (npc->x == player->x && npc->y == player->y)
	{
		if (npc->type == Provodnik)
		{
			printf("Zdravstvyi, hochesh' otpravit'sya na sledyyshi yroven'?\n 1 - Da \n 2 - Net (leave)");
			scanf_s("%d", &answer_choice);
			switch (answer_choice)
			{
			case 1: printf("Da"); break; // add next level
			case 2: printf("Net"); break; // add leave
			default: break; // add leave
			}
		}
		else if (npc->type == Torgovec)
		{
			printf("Zdravstvyi, hochesh' prodat' ili kypit' predmeti?\n 1 - Kypit'\n 2 - Prodat'\n 3 - Leave");
			scanf_s("%d", &answer_choice);
			switch (answer_choice)
			{
			case 1: item_buy(Inventory_Person, Invenroty_NPC); break;
			case 2: item_sell(Inventory_Person, Invenroty_NPC); break;
			case 3: 
				player->x = player->prev_x;
				player->y = player->prev_y;
				break; //leave
			default: break; //leave
			}
		}
		else if (npc->type == Quest1)
		{
			printf("Zdravstvyi pytnik, pomogi mne s odim delom, i ya tebya voznagrajy. Neobhodimo ystranit' bandy razboinikov. Ybey 10 vragov i polychish nagrady.\n 1 - Ya soglsen.\n 2 - Ya ne bydy brat'sya za eto. (Leave)");
			scanf_s("%d", &answer_choice);
			switch (answer_choice)
			{
			case 1: player->killQuest = 1; break; //Zapysk mission
			case 2: break; //leave
			default: break; //leave
			}
		}
		else if (npc->type == Quest2)
		{
			printf("Zdravstvyi pytnik, pomogi mne nayti knigy, ona gde-to nepodaleky, viglyadit kak (K). Prinesi mne ee.\n 1 - Ya soglsen.\n 2 - Polychit' nagrady\n 3 - Ya ne bydy brat'sya za eto. (Leave)");
			scanf_s("%d", &answer_choice);
			switch (answer_choice)
			{
			case 1: quest2();  break; //Zapysk mission
			case 2:
				if (player->findQuest == 1)
				{
					printf("Spasibo za pomosh'!\n");
					Inventory_Person->cash += 200;
				}
				else printf("Ti mne esh'e ne prines moy knigy!!!"); //leave
				break; //leave
			default: break; //leave
			}
		}
	}

}

void quest2()
{
	spawn_item(Quest, 1, 1001, "Kniga", 0, 0, 16, 6);
}