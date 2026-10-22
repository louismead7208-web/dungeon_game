#pragma once

#define MAP_HEIGHT 30
#define MAP_WIDTH 40

struct tile {
    int visited = 0;
    int state = 1;
};

extern struct tile map[MAP_HEIGHT][MAP_WIDTH];

//walkable
const int ALIVE = 1;
//wall
const int DEAD = 0;

void gen_map();