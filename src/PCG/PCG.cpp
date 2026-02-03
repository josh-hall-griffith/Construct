/*
===============================================================================
PCG.c - Construct Map Editor PCG Module
-------------------------------------------------------------------------------
Author:      Griffith Film School
Description: PCG Module Source File for Construct Map Editor Template
===============================================================================
*/

#include "PCG/PCG.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"     // Required for UI controls
#include <stdio.h>      // TODO: once all printf is removed, this can be removed
#include <iostream>     // For std::cout
#include <fstream>      // Standard C++ File I/O

// ============================================
// Tilemap class implementation
// ============================================
PCG::TileMap::TileMap()
{
    // Constructor implementation (if needed)
}

PCG::TileMap::~TileMap()
{
    // Destructor implementation (if needed)
}

// =============================================
// PCG_SetTile - Sets the tile at (x, y) to the specified type
// =============================================
void PCG::TileMap::SetTile(int x, int y, TileType type) {
    // Basic bounds checking
    if (x >= 0 && x < MAP_COLUMNS && y >= 0 && y < MAP_ROWS) {
        // Set the tile
        tileArray[y][x] = type;
    }
}



// =============================================
// PCG_DrawMap - Renders the data using Row-Major traversal
// =============================================
void PCG::TileMap::DrawMap() const
{
    for (int y = 0; y < MAP_ROWS; y++)
    {
        for (int x = 0; x < MAP_COLUMNS; x++)
        {
            DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, GetTileColor((TileType)tileArray[y][x]));
        }
    }
}

// =============================================
// PCG_PrintMap - Standard console output (Row by Row)
// =============================================
void PCG::TileMap::PrintMap() const
{
    std::cout << "\n-------Map Layout:--------\n";
    for (int y = 0; y < MAP_ROWS; y++)
    {
        for (int x = 0; x < MAP_COLUMNS; x++)
        {
            std::cout << GetTileChar((TileType)tileArray[y][x]);
        }
        std::cout << "\n";
    }
    std::cout << "--------------------------\n";
}

// =============================================
// PCG_DrawGUI - Renders GUI Elements
// =============================================
void PCG::TileMap::DrawGUI()
{
    // Reset Button
    if(GuiButton(RESET_BUTTON_BOUNDS, "Random Map"))
    {
        //CreateMap();
        // We use the abstract generator to simply call generate on this map
        // the implementation of generate will depend on the actual generator type passed in (e.g., RandomGenerator)
        // At the end of the day, it doesn't matter
        PCG::RandomGenerator randomGen;
        randomGen.Generate(*this); // regenerate the map using the random generator
        PrintMap();
    }

    // Perlin Noise Button
    Rectangle noiseButtonBounds = { BUTTON_X - 220, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT };
    if(GuiButton(noiseButtonBounds, "Perlin Noise Map"))
    {
        PCG::PerlinNoiseGenerator perlinGen;
        perlinGen.Generate(*this); // regenerate the map using the Perlin noise generator
        PrintMap();
    }
    
    // Save Map Button
    Rectangle saveButtonBounds = { BUTTON_X, BUTTON_Y - 70, BUTTON_WIDTH, BUTTON_HEIGHT };
    if(GuiButton(saveButtonBounds, "Save Map Image"))
    {
        SaveMapImage(MAP_IMAGE_FILENAME);
    }

    // Save Data Button
    Rectangle saveDataButtonBounds = { BUTTON_X, BUTTON_Y - 140, BUTTON_WIDTH, BUTTON_HEIGHT };
    if(GuiButton(saveDataButtonBounds, "Save Map Data"))
    {
        SaveMapData(MAP_TEXT_FILENAME);
    }

    // Load Data Button
    Rectangle loadDataButtonBounds = { BUTTON_X, BUTTON_Y - 210, BUTTON_WIDTH, BUTTON_HEIGHT };
    if(GuiButton(loadDataButtonBounds, "Load Map Data"))
    {
        LoadMapData(MAP_TEXT_FILENAME);
        PrintMap();
    }
}

// =============================================
// PCG_SaveMapImage - Saves the map as an image file
// =============================================
void PCG::TileMap::SaveMapImage(const char* _filename) const
{
    // PCG IDEA: Enhance image saving with different formats or resolutions, or add a text input for filename
    Image mapImage = GenImageColor(MAP_COLUMNS, MAP_ROWS, BLACK);
    for (int y = 0; y < MAP_ROWS; y++)
    {
        for (int x = 0; x < MAP_COLUMNS; x++)
        {
            Color tileColor = GetTileColor((TileType)tileArray[y][x]);
            ImageDrawPixel(&mapImage, x, y, tileColor);
        }
    }
    if(ExportImage(mapImage, _filename)){
        printf("Map image saved successfully to %s\n", _filename);
    } else {
        printf("Failed to save map image to %s\n", _filename);
    }
    UnloadImage(mapImage);
}

// =============================================
// PCG_SaveMapData - Saves the map data to a text file
// =============================================
void PCG::TileMap::SaveMapData(const char* _filename) const
{

    // open file for write and check for errors
    // C++ way to write file
    std::ofstream file(_filename);
    if (!file.is_open()) {                 
        std::cout << "Error opening file " << _filename << " for writing.\n";
        return;
    }

    // loop through array and write to file
    for (int y = 0; y < MAP_ROWS; y++)
    {
        for (int x = 0; x < MAP_COLUMNS; x++)
        {
            // write each tile character to the file using the get tile char helper function
            file << GetTileChar((TileType)tileArray[y][x]);
            
        }
        // add the newline character at the end of each row
        file << '\n'; // New line at the end of each row
    }

    // close the file
    file.close();
    std::cout << "Map data saved successfully to " << _filename << "\n";
}

// =============================================
// PCG_LoadMapData - Loads the map data from a text file
// =============================================
void PCG::TileMap::LoadMapData(const char* _filename)
{
    // add input for filename loading
    // open file for read and check for errors
    
    // C++ way to read file
    std::ifstream file(_filename);
    if (!file.is_open()) {
        printf("Error opening file %s for reading.\n", _filename);
        return;
    }   
    // loop through array and read from file
    for (int y = 0; y < MAP_ROWS; y++)
    {
        for (int x = 0; x < MAP_COLUMNS; x++)
        {
            // get each character from the file
            int ch = file.get();

            // Skip newlines and carriage returns (Handles Linux/Mac AND Windows files)
            while (ch == '\n' || ch == '\r') {
                ch = file.get();
            }

            //if (ch == GRASS_CHAR) {
            if(ch == GRASS_CHAR) {
                tileArray[y][x] = TILE_TYPE_GRASS;
            } else if (ch == ROCK_CHAR) {
                tileArray[y][x] = TILE_TYPE_ROCK;
            }else if (ch == EOF) {
                printf("Error: Reached end of file unexpectedly in %s\n", _filename);
                //fclose(file);
                file.close();
                return;
            } else {
                std::cout << "Warning: Unknown character '" << static_cast<char>(ch) << "' in map data file. Using UNKNOWN tile type.\n";
                x--; // Don't move to next tile, try reading again
            }
        }
    }
    // Close the file
    file.close();
}

// =============================================
// PCG_GetTileColor - Returns the color for a given tile type
// =============================================
Color PCG::TileMap::GetTileColor(TileType tileType) const{
    // PCG IDEA: Add more tile types here for more variety
    switch (tileType) {
        // PCG IDEA: Add more tile types here for more variety
        case TILE_TYPE_GRASS:
            // PCG IDEA: instead of using RGB colour use HSV. then you can more easily vary the hue/saturation/value for more variety. Creating subtle shades in the grass tiles
            return GRASS_COLOR;
        case TILE_TYPE_ROCK:
            return ROCK_COLOR;
        default:
            return UNKNOWN_COLOR; // Unknown tile type
    }
}

// =============================================
// PCG_GetTileChar - Returns the character representation for a given tile type
// =============================================
char PCG::TileMap::GetTileChar(TileType tileType) const{
    // PCG IDEA: Add more tile types here for more variety
    switch (tileType) {
        case TILE_TYPE_GRASS:
            return GRASS_CHAR;   // Dereference to get char from const char*
        case TILE_TYPE_ROCK:
            return ROCK_CHAR;    // Dereference to get char from const char*
        default:
            return '?'; // Unknown tile type
    }
}

// -----------------------------------------------------------------

// =============================================
// PCG_RandomGenerator - Example implementation of a simple random generator
// =============================================
void PCG::RandomGenerator::Generate(PCG::TileMap& _map) {
    for (int y = 0; y < MAP_ROWS; y++)
    {
        for (int x = 0; x < MAP_COLUMNS; x++)
        {
            _map.SetTile(x, y, (TileType)GetRandomValue(0, TILE_COUNT - 1));   // Randomly assign tiles based on TILE_COUNT choosing from the TileType enum
        }
    }
}

// =============================================
// PCG_PerlinNoiseGenerator - Example implementation of a Perlin noise based generator
// =============================================
void PCG::PerlinNoiseGenerator::Generate(PCG::TileMap& _map) {
    
    // Use large ranom offsets to guarantee a uniqe map section every time.
    int randomOffsetX = GetRandomValue(0, 1000);
    int randomOffsetY = GetRandomValue(0, 1000); 

    // increasing the scale to make noise features (blobs) smaller
    float noiseScale = 2.5f;

    // Raylib Perlin noise
    Image noiseImage = GenImagePerlinNoise(MAP_COLUMNS, MAP_ROWS, randomOffsetX, randomOffsetY, noiseScale);
    
    for(int y = 0; y < MAP_ROWS; y++)
    {
        for (int x = 0; x < MAP_COLUMNS; x++)
        {
            Color pixelColor = GetImageColor(noiseImage, x, y);
            // Simple thresholding based on brightness
            float brightness = (pixelColor.r + pixelColor.g + pixelColor.b) / (3.0f * 255.0f);
            if (brightness < 0.5f) {
                _map.SetTile(x, y, TILE_TYPE_ROCK);
            } else {
                _map.SetTile(x, y, TILE_TYPE_GRASS);
            }
        }
    }
    UnloadImage(noiseImage);
}