#include "raylib.h"

int main() {
    InitWindow(800, 600, "Dungeon");
    SetTargetFPS(60);
    
    float speed = 200;
    Rectangle wall = { 300, 200, 200, 40 };
    Rectangle player = { 400, 300, 32, 32 };
    
    while (!WindowShouldClose()) {
        Rectangle old_player = player;
        if (IsKeyDown(KEY_RIGHT)) player.x += speed * GetFrameTime();
        if (IsKeyDown(KEY_LEFT))  player.x -= speed * GetFrameTime();
        if (IsKeyDown(KEY_DOWN))  player.y += speed * GetFrameTime();
        if (IsKeyDown(KEY_UP))    player.y -= speed * GetFrameTime();
        
        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangleRec(player, GREEN);
        DrawRectangleRec(wall, GRAY);
        EndDrawing();

        if (CheckCollisionRecs(player, wall)) {
            player = old_player;
        }
    }
    CloseWindow();
    return 0;
}