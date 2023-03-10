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
    emptying_the_array(&a);
    a.cash = 0;
    camera = init_camera();
    player = Player_Init(1, 1, 100, 10);
    player->cam = camera;
    player->inventory = &a;
    player->level = 1;

    level = init_level();
    char filename[256];
    sprintf(filename, "../assets/level%d.txt\0", player->level);
    if (!load_level(filename, level))
        return 2;
    
    spawn_enemies(enemies, enemies_count, level);
    spawn_items(items, items_count, level);
    spawn_npcs(npcs, npc_count, level);
    // save(player);
    // load(player);
    
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
        if (player->do_new_level){
            player->level++;
            sprintf(filename, "../assets/level%d.txt\0", player->level);
            if (load_level(filename, level)){
                spawn_enemies(enemies, enemies_count, level);
                spawn_items(items, items_count, level);
                spawn_npcs(npcs, npc_count, level);
                player->do_new_level = false;
            }
            else {
                return 2;
            }
            player->x = 24;
            player->y = 24;
        }
        add_items(player, items, items_count);
        movePlayer(player, level);
        move_enemies(enemies, enemies_count, level, player);
        clear(camera);
    }
}