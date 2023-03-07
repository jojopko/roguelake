#ifndef _LEVEL_
#define _LEVEL_

#include "figth.h"

// Карту
// Камеру
// перемещение камеры

struct Camera {
    int offset_x;
    int offset_y;
    int w;
    int h;
    char * surface;
};

struct Level {
    int w;
    int h;
    char * field;
};

Camera * init_camera();

Level * init_level();

bool load_level(const char * filename, Level * level);

void draw_level(Camera * camera, const Level * level);

void draw(Camera * camera);

void clear(Camera * camera);

void draw_player(Camera *camera, const Player * player);

void draw_item(Camera * camera, const Item * item);

int getch();

#endif
