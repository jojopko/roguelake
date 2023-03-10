#include <stdlib.h>
#include "figth.h"
#include "level.h"
#include "dialog.h"

int gameloop();

int main() {
    return gameloop();
}

int gameloop() {
    const int enemies_count = 64;
    const int items_count = 128;
    const int npc_count = 16;
    Player * player;
    Level * level;
    Camera * camera;
    Enemy enemies[enemies_count];
    Item items[items_count];
    NPC npcs[npc_count];

    Inventory a;
    a.cash = 0;
    camera = init_camera();
    player = Player_Init(1, 1, 100, 10);
    player->cam = camera;
    player->inventory = &a;

    level = init_level();
    if (!load_level("../assets/level1.txt", level))
        return 2;
    
    spawn_enemies(enemies, enemies_count, level);
    spawn_items(items, items_count, level);
    spawn_npcs(npcs, npc_count, level);
    
    while(true) {
        move_camera(camera, player);
        draw_level(camera, level);
        draw_items(camera, items, items_count);
        draw_enemies(camera, enemies, enemies_count);
        draw_player(camera, player);
        draw_stats(camera, player);
        draw_npcs(camera, npcs, npc_count);
        draw(camera);
        //events
        for (int i = 0; i < npc_count; i++)
            dialog(player, &npcs[i], level);
        add_items(player, items, items_count);
        movePlayer(player, level);
        move_enemies(enemies, enemies_count, level, player);
        clear(camera);
    }
}