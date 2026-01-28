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
#include <stdio.h>


// =============================================
// PCG_CreateMap - Populates array using Row-Major order (y then x)
// =============================================
void PCG_CreateMap(TileType _tileArray[MAP_ROWS][MAP_COLUMNS])
{
    // PCG IDEA: Use a more complex PCG algorithm here for better map generation
    for (int y = 0; y < MAP_ROWS; y++)
    {
        for (int x = 0; x < MAP_COLUMNS; x++)
        {
            // PCG IDEA: Use noise functions, cellular automata, or other algorithms for more interesting maps
            _tileArray[y][x] = (TileType)GetRandomValue(0, TILE_COUNT - 1);   // Randomly assign tiles based on TILE_COUNT choosing from the TileType enum
            //_tileArray[y][x] = GetPCGValue(); // example of using a custom PCG function
        }
    }
}

// =============================================
// PCG_DrawMap - Renders the data using Row-Major traversal
// =============================================
void PCG_DrawMap(TileType _tileArray[MAP_ROWS][MAP_COLUMNS])
{
    for (int y = 0; y < MAP_ROWS; y++)
    {
        for (int x = 0; x < MAP_COLUMNS; x++)
        {
            // PCG IDEA: Use different sprites or textures for different tile types instead of rectangles
            DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, PCG_GetTileColor((TileType)_tileArray[y][x]));
        }
    }
}

// =============================================
// PCG_PrintMap - Standard console output (Row by Row)
// =============================================
void PCG_PrintMap(TileType _tileArray[MAP_ROWS][MAP_COLUMNS])
{
    printf("\n-------Map Layout:--------\n");
    for (int y = 0; y < MAP_ROWS; y++)
    {
        for (int x = 0; x < MAP_COLUMNS; x++)
        {
            if (_tileArray[y][x] == TILE_TYPE_GRASS) {
				printf("%c", GRASS_CHAR);
            } else if (_tileArray[y][x] == TILE_TYPE_ROCK) {
                printf("%c", ROCK_CHAR);
            }else{
                // What ever value is here, just print the integer
                printf("%i", _tileArray[y][x]);
            }
        }
        printf("\n");
    }
    printf("--------------------------\n");
}

// =============================================
// PCG_DrawGUI - Renders GUI Elements
// =============================================
void PCG_DrawGUI(TileType tileArray[MAP_ROWS][MAP_COLUMNS])
{
    // PCG IDEA: Add more GUI controls for different PCG parameters. Tidy up layout as needed
    // Reset Button
    if(GuiButton(RESET_BUTTON_BOUNDS, "Reset Map"))
    {
        PCG_CreateMap(tileArray);
        PCG_PrintMap(tileArray);
    }

    // Save Map Button
    Rectangle saveButtonBounds = { BUTTON_X, BUTTON_Y - 70, BUTTON_WIDTH, BUTTON_HEIGHT };
    if(GuiButton(saveButtonBounds, "Save Map Image"))
    {
        PCG_SaveMapImage(tileArray, MAP_IMAGE_FILENAME);
    }

    // Save Data Button
    Rectangle saveDataButtonBounds = { BUTTON_X, BUTTON_Y - 140, BUTTON_WIDTH, BUTTON_HEIGHT };
    if(GuiButton(saveDataButtonBounds, "Save Map Data"))
    {
        PCG_SaveMapData(tileArray, MAP_TEXT_FILENAME);
    }

    // Load Data Button
    Rectangle loadDataButtonBounds = { BUTTON_X, BUTTON_Y - 210, BUTTON_WIDTH, BUTTON_HEIGHT };
    if(GuiButton(loadDataButtonBounds, "Load Map Data"))
    {
        PCG_LoadMapData(tileArray, MAP_TEXT_FILENAME);
        PCG_PrintMap(tileArray);
    }
}

// =============================================
// PCG_SaveMapImage - Saves the map as an image file
// =============================================
void PCG_SaveMapImage(TileType _tileArray[MAP_ROWS][MAP_COLUMNS], const char* filename)
{
    // PCG IDEA: Enhance image saving with different formats or resolutions, or add a text input for filename
    Image mapImage = GenImageColor(MAP_COLUMNS, MAP_ROWS, BLACK);
    for (int y = 0; y < MAP_ROWS; y++)
    {
        for (int x = 0; x < MAP_COLUMNS; x++)
        {
            Color tileColor = PCG_GetTileColor((TileType)_tileArray[y][x]);
            ImageDrawPixel(&mapImage, x, y, tileColor);
        }
    }
    if(ExportImage(mapImage, filename)){
        printf("Map image saved successfully to %s\n", filename);
    } else {
        printf("Failed to save map image to %s\n", filename);
    }
    UnloadImage(mapImage);
}

// =============================================
// PCG_SaveMapData - Saves the map data to a text file
// =============================================
void PCG_SaveMapData(TileType _tileArray[MAP_ROWS][MAP_COLUMNS], const char* _filename)
{
    // PCG IDEA: Add error handling and user feedback for file operations
    // add input for filename

    // open file for write and check for errors
    FILE* file = fopen(_filename, "w");
    if (file == NULL) {
        printf("Error opening file %s for writing.\n", _filename);
        return;
    }

    // loop through array and write to file
    for (int y = 0; y < MAP_ROWS; y++)
    {
        for (int x = 0; x < MAP_COLUMNS; x++)
        {
            // write each tile character to the file using the get tile char helper function
            fputc(GetTileChar((TileType)_tileArray[y][x]), file);
        }
        // add the newline character at the end of each row
        fputc('\n', file); // New line at the end of each row
    }

    // close the file
    fclose(file);
    printf("Map data saved successfully to %s\n", _filename);
}

// =============================================
// PCG_LoadMapData - Loads the map data from a text file
// =============================================
void PCG_LoadMapData(TileType _tileArray[MAP_ROWS][MAP_COLUMNS], const char* _filename)
{
    // PCG IDEA: Add error handling and user feedback for file operations
    // add input for filename loading
    // open file for read and check for errors
    FILE* file = fopen(_filename, "r");
    if (file == NULL) {
        printf("Error opening file %s for reading.\n", _filename);
        return;
    }   
    // loop through array and read from file
    for (int y = 0; y < MAP_ROWS; y++)
    {
        for (int x = 0; x < MAP_COLUMNS; x++)
        {
            // get each character from the file
            int ch = fgetc(file);

            // Skip newlines and carriage returns (Handles Linux/Mac AND Windows files)
            while (ch == '\n' || ch == '\r') {
                ch = fgetc(file);
            }

            if (ch == GRASS_CHAR) {
                _tileArray[y][x] = TILE_TYPE_GRASS;
            } else if (ch == ROCK_CHAR) {
                _tileArray[y][x] = TILE_TYPE_ROCK;
            }else if (ch == EOF) {
                printf("Error: Reached end of file unexpectedly in %s\n", _filename);
                fclose(file);
                return;
            } else {
                printf("Warning: Skipping unexpected character '%c' (ASCII %d)\n", ch, ch);
                x--; // Don't move to next tile, try reading again
            }
        }
    }
    // Close the file
    fclose(file);
}

// =============================================
// PCG_GetTileColor - Returns the color for a given tile type
// =============================================
Color PCG_GetTileColor(TileType tileType){
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
char GetTileChar(TileType tileType){
    // PCG IDEA: Add more tile types here for more variety
    switch (tileType) {
        case TILE_TYPE_GRASS:
            return GRASS_CHAR;
        case TILE_TYPE_ROCK:
            return ROCK_CHAR;
        default:
            return '?'; // Unknown tile type
    }
}