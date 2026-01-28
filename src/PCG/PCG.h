/*
===============================================================================
PCG.h - Construct Map Editor PCG Module
-------------------------------------------------------------------------------
Author:      Griffith Film School
Description: PCG Module Header File for Construct Map Editor Template
===============================================================================
*/

#ifndef PCG_H
#define PCG_H
#include "raylib.h" // Required for Color types

// Screen Dimensions
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 1024


// Standard Map Dimensions
#define TILE_SIZE 64
#define MAP_COLUMNS (SCREEN_WIDTH / TILE_SIZE)
#define MAP_ROWS (SCREEN_HEIGHT / TILE_SIZE)

// Tile Types
typedef enum {
    TILE_TYPE_GRASS = 0,
    TILE_TYPE_ROCK = 1,
    TILE_COUNT  // automatically counts the number of tile types as its the last element thus representing the count
    // TILE_TYPE_WATER = 2, // Example of adding a new tile type
} TileType;

// Console Representation
#define GRASS_CHAR '.'
#define ROCK_CHAR '#'
//// PCG IDEA: #define WATER_CHAR '~' // Example of adding a new tile type

// Color Definitions in RGBA format
#define GRASS_COLOR (Color){69, 182, 156, 255} // Light Teal
#define ROCK_COLOR (Color){114, 147, 160, 255} // Light Gray
#define UNKNOWN_COLOR WHITE
// // PCG IDEA:  #define WATER_COLOR LIGHTBLUE // Example of adding a new tile type


// Button Bounds
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50
#define BUTTON_X (SCREEN_WIDTH - BUTTON_WIDTH - 20)
#define BUTTON_Y (SCREEN_HEIGHT - BUTTON_HEIGHT - 20)

// PCG gui button
#define RESET_BUTTON_BOUNDS (Rectangle){ BUTTON_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT }

// File Names
#define MAP_TEXT_FILENAME "pcg_map_data.txt"
#define MAP_IMAGE_FILENAME "pcg_map.png"

// Declare Functions using standard [ROWS][COLS] sizing
void PCG_CreateMap(TileType _tileArray[MAP_ROWS][MAP_COLUMNS]);
void PCG_DrawMap(TileType _tileArray[MAP_ROWS][MAP_COLUMNS]);
void PCG_DrawGUI(TileType tileArray[MAP_ROWS][MAP_COLUMNS]);

Color PCG_GetTileColor(TileType tileType);
char GetTileChar(TileType tileType);

void PCG_PrintMap(TileType _tileArray[MAP_ROWS][MAP_COLUMNS]);
void PCG_SaveMapData(TileType _tileArray[MAP_ROWS][MAP_COLUMNS], const char* filename);
void PCG_LoadMapData(TileType _tileArray[MAP_ROWS][MAP_COLUMNS], const char* filename);
void PCG_SaveMapImage(TileType _tileArray[MAP_ROWS][MAP_COLUMNS], const char* filename);

#endif // PCG_H