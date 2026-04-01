#include "raylib.h"
#include "resource_dir.h"
#include "PCG.h" // Import our new module


int main() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Construct Map Editor");
    
    PCG::TileType tileArray[MAP_ROWS][MAP_COLUMNS] = { PCG::TileType::TILE_TYPE_ROCK };
    PCG::CreateMap(tileArray);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        PCG::PCG_DrawMap(tileArray); // Function from PCG.c
        DrawText("Construct Map Editor", 20, 20, 20, WHITE);
        PCG::PCG_DrawGUI(tileArray);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}