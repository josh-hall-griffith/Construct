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
#include <stdio.h>
#include "resource_dir.h"

// Defines
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 1024
#define TILE_SIZE 64

// Standard Map Dimensions
#define MAP_COLUMNS (SCREEN_WIDTH / TILE_SIZE)
#define MAP_ROWS (SCREEN_HEIGHT / TILE_SIZE)

// Tile Types
#define TILE_TYPE_GRASS 0
#define TILE_TYPE_ROCK 1

// Console Representation
#define GRASS_CHAR '.'
#define ROCK_CHAR '#'

// Forward declarations using standard [ROWS][COLS] sizing
void CreateMap(int _tileArray[MAP_ROWS][MAP_COLUMNS]);
void DrawMap(int _tileArray[MAP_ROWS][MAP_COLUMNS]);
void PrintMap(int _tileArray[MAP_ROWS][MAP_COLUMNS]);

int main()
{
    // Tell the window to use vsync and work on high DPI displays
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Construct Map Editor");

    SearchAndSetResourceDir("resources");
    Texture wabbit = LoadTexture("wabbit_alpha.png");

    // Initialize the map (Rows come first in memory for C arrays)
    int tileArray[MAP_ROWS][MAP_COLUMNS] = { 0 };
    
    CreateMap(tileArray);
    PrintMap(tileArray);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        // Render the map data
        DrawMap(tileArray);

        // Render UI Elements
        DrawText("The Construct Map Editor", 20, 20, 20, WHITE);
        DrawTexture(wabbit, 400, 200, WHITE);

        EndDrawing();
    }

    UnloadTexture(wabbit);
    CloseWindow();
    return 0;
}

// =============================================
// CreateMap - Populates array using Row-Major order (y then x)
// =============================================
void CreateMap(int _tileArray[MAP_ROWS][MAP_COLUMNS])
{
    for (int y = 0; y < MAP_ROWS; y++)
    {
        for (int x = 0; x < MAP_COLUMNS; x++)
        {
            _tileArray[y][x] = GetRandomValue(TILE_TYPE_GRASS, TILE_TYPE_ROCK);
        }
    }
}

// =============================================
// DrawMap - Renders the data using Row-Major traversal
// =============================================
void DrawMap(int _tileArray[MAP_ROWS][MAP_COLUMNS])
{
    for (int y = 0; y < MAP_ROWS; y++)
    {
        for (int x = 0; x < MAP_COLUMNS; x++)
        {
            Color tileColor;
            
            if (_tileArray[y][x] == TILE_TYPE_GRASS)
            {
                tileColor = LIGHTGRAY;
            }
            else
            {
                tileColor = DARKGRAY;
            }
            
            // Note: Screen Coordinates are still (x, y)
            DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE - 1, TILE_SIZE - 1, tileColor);
        }
    }
}

// =============================================
// PrintMap - Standard console output (Row by Row)
// =============================================
void PrintMap(int _tileArray[MAP_ROWS][MAP_COLUMNS])
{
    printf("\n-------Map Layout:--------\n");
    for (int y = 0; y < MAP_ROWS; y++)
    {
        for (int x = 0; x < MAP_COLUMNS; x++)
        {
            if (_tileArray[y][x] == TILE_TYPE_GRASS) {
				printf("%c", GRASS_CHAR);
            } else {
                printf("%c", ROCK_CHAR);
            }
        }
        printf("\n");
    }
    printf("--------------------------\n");
}