#include "raylib.h"

int main() {
    InitWindow(800, 600, "Dungeon");
    SetTargetFPS(60);
    float x = 400, y = 300;
    float speed = 200;

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_RIGHT)) x += speed * GetFrameTime();
        if (IsKeyDown(KEY_LEFT))  x -= speed * GetFrameTime();
        if (IsKeyDown(KEY_DOWN))  y += speed * GetFrameTime();
        if (IsKeyDown(KEY_UP))    y -= speed * GetFrameTime();

        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangle((int)x, (int)y, 32, 32, GREEN);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}