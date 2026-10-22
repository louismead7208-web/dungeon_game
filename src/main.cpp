#include "raylib.h"
#include "p_gen.h"

#include <vector>
#include <string>
#include <math.h>
#include <ctime>

// prototypes


int main() {
    
    float speed = 200;

    const float TILE = 40;

    std::vector<Rectangle> walls = { };

    gen_map();

    for (int h = 0; h < MAP_HEIGHT; h++) {
        for (int w = 0; w < MAP_WIDTH; w++) {
            if (map[h][w].state == DEAD) {
                walls.push_back({TILE * w, TILE * h, TILE, TILE});
            }
            if (h == 0 || h == MAP_HEIGHT - 1 || w == 0 || w == MAP_WIDTH - 1) {
                walls.push_back({ TILE * w, TILE * h, TILE, TILE });
            }
        }
    }

    Rectangle player = { 44, 44, 32, 32 };

    InitWindow(MAP_WIDTH * TILE, MAP_HEIGHT * TILE, "Dungeon");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        Rectangle old_player = player;
        if (IsKeyDown(KEY_RIGHT)) player.x += speed * GetFrameTime();
        if (IsKeyDown(KEY_LEFT))  player.x -= speed * GetFrameTime();
        for (const Rectangle& w : walls) {
            if (CheckCollisionRecs(player, w)) player.x = old_player.x;
        }

        if (IsKeyDown(KEY_DOWN))  player.y += speed * GetFrameTime();
        if (IsKeyDown(KEY_UP))    player.y -= speed * GetFrameTime();
        for (const Rectangle& w : walls) {
            if (CheckCollisionRecs(player, w)) player.y = old_player.y;
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
