#include <stdlib.h>
#include "figth.h"
#include "level.h"
#include "dialog.h"



int main() {
    //Тестовый код для движения. Закинуть в main и раскоментить
    srand(123);
    Player * player = Player_Init(12,12,100,10);
    Enemy * enemy = Enemy_Init(12,11,100,10);
    Inventory a, b;
    a.items[0] = *spawn_item(Health, 100, 1, "Name\0", 100, 0, -1, -1);
    // b.items[0] = *spawn_item(Health, 100, 1, "Name\0", 100, 0, -1, -1);
    b.cash = 1000;
    NPC * npc = spawn_NPC(15, 12, &b);

    Camera * cam = init_camera();
    Level * level = init_level();
    if (!load_level("../assets/level1.txt\0", level))
        return 2;

    Enemy * enemies[10] = {
        Enemy_Init(12,11,100,10),
        Enemy_Init(13,11,100,10),
        Enemy_Init(14,11,100,10),
        Enemy_Init(15,11,100,10),
        Enemy_Init(15,11,100,10),
        Enemy_Init(15,11,100,10),
        Enemy_Init(15,11,100,10),
        Enemy_Init(15,11,100,10),
        Enemy_Init(15,11,100,10),
        Enemy_Init(15,11,100,10)
    };

    while (true){
        move_camera(cam, player);
        draw_level(cam, level);
        // draw_item(cam, )
        for (int i = 0; i < 10; i++) {
            Enemy_AI(enemies[i], level);
            draw_enemy(cam, enemies[i]);
            Start_Fight(player, enemies[i], &a, level);
        }
        draw_npc(cam, npc);
        draw_player(cam, player);
        draw_stats(cam, player);
        dialog(player, npc, &a, &b, level);
        draw(cam);
        if (player->hp <= 0){
            clear(cam);
            printf("Game over!");
            return 0;
        }
        movePlayer(player, level);
        clear(cam);
    }

    return 0;
}


    // // Тестовый код для движения. Закинуть в main и раскоментить
    // Player * player = Player_Init(12,12,100,10);
    // Enemy * enemy = Enemy_Init(12,9,10,100);
    // Inventory a;
    // a.items[0] = *spawn_item(Health, 100, 1, "Name\0", 100, 0, -1, -1);

    // Camera * cam = init_camera();
    // Level * level = init_level();
    // if (!load_level("../assets/level1.txt\0", level))
    //     return 2;

    // while (true){
    //     draw_level(cam, level);
    //     // draw_item(cam, )
    //     draw_enemy(cam, enemy);
    //     draw_player(cam, player);
    //     if (player->x == enemy->x && player->y == enemy->y){
    //         clear(cam);
    //         FigthPlayer(player, enemy, &a);
    //     }
    //     draw(cam);
    //     movePlayer(player, level);
    //     clear(cam);
    // }




// #include <stdio.h>
// #include <stdlib.h>
// #include <fcntl.h>
// #include <unistd.h>
// #include <linux/input.h>
// int fd;
//     struct input_event ev;

//     // Open the input device
//     fd = open("/dev/input/event2", O_RDONLY);
//     if (fd < 0) {
//         perror("open");
//         exit(1);
//     }

//     while (1) {
//         printf("hello\n");
//         // Read the next event
//         if (read(fd, &ev, sizeof(struct input_event)) < 0) {
//             perror("read");
//             exit(1);
//         }

//         // Check if the event is a key press
//         if (ev.type == EV_KEY && ev.value == 1 && ev.code == KEY_A) {
//             printf("Key A pressed\n");
//         }
//     }

