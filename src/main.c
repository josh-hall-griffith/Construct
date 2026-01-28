/*
===============================================================================
Construct Map Editor
-------------------------------------------------------------------------------
Author:      Griffith Film School
Description: A simple tile-based map editor template using raylib for 
             introductory programming students. Demonstrates 2D arrays, 
             nested loops, and basic graphics rendering.
===============================================================================
*/

#include "raylib.h"
#include "resource_dir.h"

#include "PCG/PCG.h"


int main()
{
    // Tell the window to use vsync and work on high DPI displays
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Construct Map Editor");

    SearchAndSetResourceDir("resources");
    Texture wabbit = LoadTexture("wabbit_alpha.png");

    // Initialize the map (Rows come first in memory for C arrays)
    TileType tileArray[MAP_ROWS][MAP_COLUMNS] = { 0 };

    PCG_CreateMap(tileArray);
    PCG_PrintMap(tileArray);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        // Render the map data
        PCG_DrawMap(tileArray);

        // Render UI Elements
        DrawText("The Construct Map Editor", 20, 20, 20, WHITE);

		// Draw the wabbit texture for fun
		// PCG IDEA: Make the wabbit controllable using keyboard input or have it react to the map like A* navigation
        DrawTexture(wabbit, 400, 200, WHITE);

		// GUI controls
		PCG_DrawGUI(tileArray);

        EndDrawing();
    }

    UnloadTexture(wabbit);
    CloseWindow();
    return 0;
}

