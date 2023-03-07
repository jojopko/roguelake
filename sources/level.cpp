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

void draw(Camera * camera){
    for (int cam_y = 0; cam_y < camera->h; cam_y++){
        for (int cam_x = 0; cam_x < camera->w; cam_x++){
            int c = camera->surface[cam_y * camera->w + cam_x];
            putchar(c);
        }
        if (cam_y != camera->h - 1)
            putchar('\n');
    }
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
    int item_x = 9;
    int item_y = 9;
    int item_cam_x = (item_x - camera->offset_x);
    int player_cam_y = (item_y - camera->offset_y);
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

bool is_wall(Level * level, int x, int y) {
    char * field = level->field;
    for (int y = 0; y < level->h; y++) {
        for (int x = 0; x < level->w; x++) {
            int index = y * level->w + x;
            if (field[index] == '#')
                return true;
        }
    }
    return false;
}

