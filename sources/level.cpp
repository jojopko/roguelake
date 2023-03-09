#include <stdlib.h>
#include <stdio.h>
#include "level.h"



Camera * init_camera() {
    Camera * camera = (Camera *) malloc(sizeof(Camera));
    camera->offset_x = 0;
    camera->offset_y = 0;
    camera->w = 100;
    camera->h = 30;
    camera->surface = (char *) malloc(sizeof(char) * camera->w * camera->h);
    return camera;
}

Level * init_level() {
    Level * level = (Level *) malloc(sizeof(Level));
    level->w = 0;
    level->h = 0;
    level->field = nullptr;
    return level;
}

bool load_level(const char * filename, Level * level) {
    FILE * fp = fopen(filename, "r");
    if (!fp) {
        return false;
    }

    if (level->field) {
        free(level->field);
    }

    int w, h;
    fscanf(fp, "%d %d\n", &w, &h);

    level->field = (char *) malloc(sizeof(char) * w * h);
    level->w = w;
    level->h = h;

    const int buffer_size = 256;
    char buffer[buffer_size] = {};

    for (int i = 0; i < h && !feof(fp); i++) {
        fgets(buffer, buffer_size, fp);
        for (int j = 0; j < w; j++) {
            char c = buffer[j];
            char * current = &level->field[i * w + j];
            switch(c) {
                case '.':
                    *current = ' ';
                    break;
                case '#':
                    *current = '#';
                    break;
                default:
                    *current = '#';
            }
        }
    }
    fclose(fp);
    return true;
}

void draw_level(Camera * camera, const Level * level) {
    for (int cam_y = 0; cam_y < camera->h; cam_y++){
        for (int cam_x = 0; cam_x < camera->w; cam_x++){
            int gr_x = cam_x + camera->offset_x;
            int gr_y = cam_y + camera->offset_y;
            if ((gr_x < 0 || gr_x > level->w) || (gr_y < 0 || gr_y > level->h)){
                camera->surface[cam_y * camera->w + cam_x] = '#'; // если вы ходит за края карты то "#"
            }
            else{
                camera->surface[cam_y * camera->w + cam_x] = level->field[gr_y * level->w + gr_x];
            }
        }
    }
}

void draw_stats(Camera * camera, const Player * player) {
    bool fill_empty = false;
    char stat[100] = {};
    int attack = player->default_attack + (player->item_weapon != NULL ? player->item_weapon->damage : 0);
    sprintf(stat, "HP:%d AP:%d X:%d Y:%d", player->hp, attack, player->x, player->y);
    for (int i = 0; i < camera->w; i++){
        if(fill_empty)
            camera->surface[i] = ' ';
        if(stat[i] == 0)
            fill_empty = true;
        else
            camera->surface[i] = stat[i];
    }
}

void draw_log1(Camera * camera, const char * buffer100) {
    bool fill_empty = false;
    for (int i = 0; i < camera->w; i++){
        int index = (camera->h-2) * camera->w + i;
        char c = buffer100[i];
        if(c == '\0')
            fill_empty = true;
        if (fill_empty){
            camera->surface[index] = ' ';
        }
        else{
            camera->surface[index] = c;
        }
    }
}

void draw_log2(Camera * camera, const char * buffer100) {
    bool fill_empty = false;
    for (int i = 0; i < camera->w; i++){
        int index = (camera->h-1) * camera->w + i;
        char c = buffer100[i];
        if(c == '\0')
            fill_empty = true;
        if (fill_empty){
            camera->surface[index] = ' ';
        }
        else{
            camera->surface[index] = c;
        }
    }
}

void draw(Camera * camera){
    for (int cam_y = 0; cam_y < camera->h; cam_y++){
        for (int cam_x = 0; cam_x < camera->w; cam_x++){
            int c = camera->surface[cam_y * camera->w + cam_x];
            putchar(c);
        }
        if (cam_y != camera->h - 1){
            putchar('\n');
        }
    }
}

void move_camera(Camera *camera, const Player *player) {
    camera->offset_x = player->x - camera->w / 2;
    camera->offset_y = player->y - camera->h / 2;
}


#if __linux__
#include <termios.h>
#include <unistd.h>

int getch() {
    struct termios oldtc;
    struct termios newtc;
    int ch;
    tcgetattr(STDIN_FILENO, &oldtc);
    newtc = oldtc;
    newtc.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newtc);
    ch=getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldtc);
    return ch;
}

short GetKeyState(int virtkey) {
    int c = getch();
    if (c == virtkey) 
        return -1;
    return 0;
}
#endif

void clear(Camera * camera) {
    for (int y = 0; y < camera->h; y++) {
        for(int x = 0; x < camera->w; x++){
            camera->surface[y*camera->w + x] = '#';
        }
    }
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void draw_player(Camera *camera, const Player * player){
    int player_cam_x = (player->x - camera->offset_x);
    int player_cam_y = (player->y - camera->offset_y);
    if((player_cam_x >= 0 && player_cam_x < camera->w) && 
       (player_cam_y >= 0 && player_cam_y < camera->h)) {
        camera->surface[player_cam_y * camera->w + player_cam_x] = '@';
    }
}

void draw_item(Camera * camera, const Item * item){
    int item_cam_x = (item->x - camera->offset_x);
    int player_cam_y = (item->y - camera->offset_y);
    if((item_cam_x >= 0 && item_cam_x < camera->w) && 
       (player_cam_y >= 0 && player_cam_y < camera->h)) {
        if (item->type == Health)
            camera->surface[player_cam_y * camera->w + item_cam_x] = 'O';
        else if (item->type == Melee)
            camera->surface[player_cam_y * camera->w + item_cam_x] = '!';
        else 
            camera->surface[player_cam_y * camera->w + item_cam_x] = '-';

    }
}

void draw_enemy(Camera * camera, const Enemy * enemy) {
    int enemy_cam_x = (enemy->x - camera->offset_x);
    int enemy_cam_y = (enemy->y - camera->offset_y);
    if((enemy_cam_x >= 0 && enemy_cam_x < camera->w) && 
       (enemy_cam_y >= 0 && enemy_cam_y < camera->h) &&
       enemy->hp > 0) {
        camera->surface[enemy_cam_y * camera->w + enemy_cam_x] = 'A';
    }
}

void draw_npc(Camera * camera, const NPC * npc){
    int npc_cam_x = (npc->x - camera->offset_x);
    int npc_cam_y = (npc->y - camera->offset_y);
    if((npc_cam_x >= 0 && npc_cam_x < camera->w) && 
       (npc_cam_y >= 0 && npc_cam_y < camera->h)) {
        if (npc->type == Torgovec)
            camera->surface[npc_cam_y * camera->w + npc_cam_x] = '&';
        if (npc->type == Quest1)
            camera->surface[npc_cam_y * camera->w + npc_cam_x] = 'O';
        if (npc->type == Quest2)
            camera->surface[npc_cam_y * camera->w + npc_cam_x] = '8';
        if (npc->type == Provodnik)
            camera->surface[npc_cam_y * camera->w + npc_cam_x] = 'Q';
    }
}

bool is_wall(Level * level, int x, int y) {
    char * field = level->field;
    int index = y * level->w + x;
    if (field[index] == '#')
        return true;
    if (field[index] == '@')
        return true;
    return false;
}




