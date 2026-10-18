#pragma once

#define MAP_HEIGHT 30
#define MAP_WIDTH 40

extern int map[MAP_HEIGHT][MAP_WIDTH];

const int ALIVE = 1;
const int DEAD = 0;

void gen_map();