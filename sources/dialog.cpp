#include "dialog.h"
#include "figth.h"
#include "trade.h"

void dialog(TypeNPC type, Player* player, NPC* npc, Inventory* Inventory_Person, Inventory* Invenroty_NPC)
{
	int answer_choice;
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
		case 3: break; //leave
		default: break; //leave
		}
	}
	else if (npc->type == Quest1)
	{
		printf("Zdravstvyi pytnik, pomogi mne s odim delom, i ya tebya voznagrajy. Neobhodimo ystranit' odnogo podleca.\n 1 - Ya soglsen.\n 2 - Ya ne bydy brat'sya za eto. (Leave)");
		scanf_s("%d", &answer_choice);
		switch (answer_choice)
		{
		case 1: break; //Zapysk mission
		case 2: break; //leave
		default: break; //leave
		}
	}
	else if (npc->type == Quest2)
	{
		printf("Zdravstvyi pytnik, pomogi mne nayti predmet, on gde-to na nepodaleky.\n 1 - Ya soglsen.\n 2 - Ya ne bydy brat'sya za eto. (Leave)");
		scanf_s("%d", &answer_choice);
		switch (answer_choice)
		{
		case 1: break; //Zapysk mission
		case 2: break; //leave
		default: break; //leave
		}
	}

}