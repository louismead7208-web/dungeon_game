#include "raylib.h"
#include <vector>

int main() {
    InitWindow(800, 600, "Dungeon");
    SetTargetFPS(60);
    
    float speed = 200;
    std::vector<Rectangle> walls = {
        // boarder
        {0,   0,   800, 20},
        {0,   580, 800, 20},
        {0,   0,   20,  600},
        {780, 0,   20,  600},

        // inside
        {200, 100, 20,  250},
        {200, 100, 200, 20},
        {500, 200, 20,  250},
        {500, 430, 200, 20},
        {300, 450, 120, 20}
    };

    Rectangle player = { 400, 300, 32, 32 };
    
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