#include "raylib.h"

int main() {
    InitWindow(800, 600, "Dungeon");
    SetTargetFPS(60);
    float x = 400, y = 300;

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_RIGHT)) x += 4;
        if (IsKeyDown(KEY_LEFT))  x -= 4;
        if (IsKeyDown(KEY_DOWN))  y += 4;
        if (IsKeyDown(KEY_UP))    y -= 4;

        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangle((int)x, (int)y, 32, 32, GREEN);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}