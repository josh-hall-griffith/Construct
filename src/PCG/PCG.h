/*
===============================================================================
PCG.h - Construct Map Editor PCG Module
-------------------------------------------------------------------------------
Author:      Griffith Film School
Description: PCG Module Header File for Construct Map Editor Template
===============================================================================
*/

//#ifndef PCG_H
//#define PCG_H
#pragma once    // Use pragma once for header guard instead of traditional ifndef/define/endif
#include "raylib.h" // Required for Color types
#include <stdint.h>  // For uint32_t type

// Screen Dimensions
const int SCREEN_WIDTH = 1024;          // Example of using const to adhere to C++ standards
const uint32_t SCREEN_HEIGHT = 1024;    // example of using uint32_t which is more appropriate for sizes


// Standard Map Dimensions
const uint32_t TILE_SIZE = 64;
const uint32_t MAP_COLUMNS = SCREEN_WIDTH / TILE_SIZE;    // Using for compile-time constant. Adherence to C++ standards
const uint32_t MAP_ROWS = SCREEN_HEIGHT / TILE_SIZE;              

// Tile Types
typedef enum {
    TILE_TYPE_GRASS = 0,
    TILE_TYPE_ROCK = 1,
    TILE_COUNT  // automatically counts the number of tile types as its the last element thus representing the count
    
} TileType;

// Console Representation
constexpr char GRASS_CHAR = '.'; // Using constexpr char for character literals to adhere to C++ standards
constexpr char ROCK_CHAR = '#';

// Color Definitions in RGBA format
const Color GRASS_COLOR = {69, 182, 156, 255};     
const Color ROCK_COLOR = {114, 147, 160, 255};            
const Color UNKNOWN_COLOR = WHITE;                   

// Button Bounds
const uint32_t BUTTON_WIDTH = 200;
const uint32_t BUTTON_HEIGHT = 50;
const uint32_t BUTTON_X = SCREEN_WIDTH - BUTTON_WIDTH - 20;
const uint32_t BUTTON_Y = SCREEN_HEIGHT - BUTTON_HEIGHT - 20;

// PCG gui button
const Rectangle RESET_BUTTON_BOUNDS = { BUTTON_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT };

// File Names
constexpr char MAP_TEXT_FILENAME[] = "pcg_map_data.txt";
constexpr char MAP_IMAGE_FILENAME[] = "pcg_map.png";

// PCG Namespace
// Encapsulates all PCG related functions and definitions
namespace PCG {
    
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
};


//#endif // PCG_H