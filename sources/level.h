#ifndef _LEVEL_
#define _LEVEL_

#include "figth.h"
#include "trade.h"
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

void draw_enemy(Camera * camera, const Enemy * enemy);

void draw_stats(Camera * camera, const Player * player);

void move_camera(Camera * camera, const Player *player);

void draw_log1(Camera * camera, const char * buffer100);

void draw_log2(Camera * camera, const char * buffer100);

#if __linux__
int getch();
#endif

bool is_wall(Level * level, int x, int y);





#endif
