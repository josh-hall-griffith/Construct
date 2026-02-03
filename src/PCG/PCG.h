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

    // Example of using classes in C++ for encapsulation and organisation
    class TileMap {
        public:
            TileMap();
            ~TileMap();

            // Methods
            void CreateMap(); 
            void PrintMap() const; // Mark as const: it only reads data
            void DrawMap() const; // Mark as const: it only reads data
            void DrawGUI();

            // File Operations
            void SaveMapData(const char* _filename);
            void LoadMapData(const char* _filename);
            void SaveMapImage(const char* _filename);

            // Helper Functions
            Color GetTileColor(TileType tileType) const;    // Mark as const: it only reads data
            char GetTileChar(TileType tileType) const;      // Mark as const: it only reads data
            
        private:
            TileType tileArray[MAP_ROWS][MAP_COLUMNS] = {};  // 2D array to hold the tile data. we use {} to zero initialize the array
    };
};


//#endif // PCG_H