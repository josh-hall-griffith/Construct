#include "raylib.h"
#include "resource_dir.h"
#include "PCG.h" // Import our new module


int main() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(PCG::SCREEN_WIDTH, PCG::SCREEN_HEIGHT, "Construct Map Editor");
    
    PCG::TileMap tileMap; 
    tileMap.CreateMap();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        tileMap.DrawMap(); // Function from PCG.c
        DrawText("Construct Map Editor", 20, 20, 20, WHITE);
        tileMap.DrawGUI();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}