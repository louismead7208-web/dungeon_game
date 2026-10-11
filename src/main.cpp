#include "raylib.h"
#include <vector>
#include <string>
#include <math.h>

int main() {
    
    float speed = 200;

    const float TILE = 40;

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