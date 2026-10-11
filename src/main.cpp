#include "raylib.h"
#include <vector>
#include <string>
#include <math.h>
#include <ctime>

// prototypes
std::vector<std::string> generate_level(int ROWS, int COLS);


int main() {
    
    float speed = 200;

    const float TILE = 40;

    std::vector<std::string> level = generate_level(15, 20);

    std::vector<Rectangle> walls = { };

    for (int row = 0; row < level.size(); row++) {
        for (int col = 0; col < level[row].size(); col++) {
            if (level[row][col] == '#') {
                walls.push_back({TILE * col, TILE * row, TILE, TILE});
            }
        }
    }
    
    Rectangle player = { 44, 44, 32, 32 };

    const int ROWS = level.size();
    const int COLS = level[0].size();

    InitWindow(COLS * TILE, ROWS * TILE, "Dungeon");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        Rectangle old_player = player;
        if (IsKeyDown(KEY_RIGHT)) player.x += speed * GetFrameTime();
        if (IsKeyDown(KEY_LEFT))  player.x -= speed * GetFrameTime();
        for (const Rectangle& w : walls) {
            if (CheckCollisionRecs(player, w)) {
                player.x = old_player.x;
            }
        }

        if (IsKeyDown(KEY_DOWN))  player.y += speed * GetFrameTime();
        if (IsKeyDown(KEY_UP))    player.y -= speed * GetFrameTime();
        for (const Rectangle& w : walls) {
            if (CheckCollisionRecs(player, w)) {
                player.y = old_player.y;
            }
        }
        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangleRec(player, GREEN);
        for (const Rectangle& w : walls) {
            DrawRectangleRec(w, GRAY);
        }
        EndDrawing();

    }
    CloseWindow();
    return 0;
}

std::vector<std::string> generate_level(int ROWS, int COLS) {
    std::vector<std::string> level(ROWS, std::string(COLS, '#'));
    //SetRandomSeed(1);
    SetRandomSeed((unsigned int)time(NULL));
    int walker_x = GetRandomValue(1, COLS - 2);
    int walker_y = GetRandomValue(1, ROWS - 2);
    for (int i = 0; i < 500; i++) {
        level[walker_y][walker_x] = '.';

        int direction = GetRandomValue(0, 3); //0:down, 1:up, 2:right, 3:left
        if (direction == 0) {
            if (walker_y + 1 == ROWS - 2) {
                continue;
            }
            walker_y++;
        } 
        else if (direction == 1) {
            if (walker_y - 1 == 1) {
                continue;
            }
            walker_y--;
        } 
        else if (direction == 2) {
            if (walker_x + 1 == COLS - 2) {
                continue;
            }
            walker_x++;
        }
        else if (direction == 3) {
            if (walker_x - 1 == 1) {
                continue;
            }
            walker_x--;
        }
    }
    return level;
}

/*
std::vector<std::string> level = {
        "####################",
        "#..................#",
        "#.####.......####..#",
        "#.#..............#.#",
        "#.#..............#.#",
        "#.####.......####..#",
        "#..................#",
        "#......##########..#",
        "#..................#",
        "#.###..............#",
        "#.#................#",
        "#.#....#####.......#",
        "#......#...........#",
        "#..................#",
        "####################"
    };
for (int row = 0; row < ROWS; row++) {
    for (int col = 0; col < COLS; col++) {
        level[row][col] = '#';
    }
}
*/