#include "PCG.h"
#include <stdio.h>
#include <iostream>
#include <fstream>

// ============================================= 
// void PCG_CreateMap(TileType _tileArray[MAP_ROWS][MAP_COLUMNS])
// ============================================= 
void PCG::CreateMap(TileType _tileArray[MAP_ROWS][MAP_COLUMNS]) {
    for (int y = 0; y < MAP_ROWS; y++) {
        for (int x = 0; x < MAP_COLUMNS; x++) {
            _tileArray[y][x] = (TileType)GetRandomValue(0, TILE_COUNT - 1);
        }
    }
}

// ============================================= 
// Color PCG_GetTileColor(TileType tileType)
// Return a colour based on the type input
// ============================================= 
Color PCG::GetTileColor(PCG::TileType tileType) {
    switch (tileType) {
    case PCG::TileType::TILE_TYPE_GRASS: return GRASS_COLOR;
    case PCG::TileType::TILE_TYPE_ROCK: return ROCK_COLOR;
    default: return UNKNOWN_COLOR;
    }
}

// ============================================= 
// void PCG_DrawMap(TileType _tileArray[MAP_ROWS][MAP_COLUMNS])
// ============================================= 
void PCG::DrawMap(PCG::TileType _tileArray[MAP_ROWS][MAP_COLUMNS]) {
    for (int y = 0; y < MAP_ROWS; y++) {
        for (int x = 0; x < MAP_COLUMNS; x++) {
            DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, PCG::GetTileColor(_tileArray[y][x]));
        }
    }
}

// ============================================= 
// void PCG_PrintMap(TileType _tileArray[MAP_ROWS][MAP_COLUMNS])
// ============================================= 
void PCG::PrintMap(TileType _tileArray[MAP_ROWS][MAP_COLUMNS]) {
    std::cout <<"\n-------Map Layout:--------" << std::endl;
    // (Existing Print Logic here...)
    std::cout <<"--------------------------" << std::endl;
}

// ============================================= 
// char GetTileChar(TileType tileType)
// Return a char value based on the type of tile passed in
// ============================================= 
char PCG::GetTileChar(TileType tileType){
    switch (tileType) {
        case TILE_TYPE_GRASS: return GRASS_CHAR;
        case TILE_TYPE_ROCK: return ROCK_CHAR;
        default: return '?';
    }
}

// ============================================= 
// void PCG_SaveMapData(TileType _tileArray[MAP_ROWS][MAP_COLUMNS], const char* _filename)
// Store our tilemap data to a text file using the input _filename
// ============================================= 
void PCG::SaveMapData(TileType _tileArray[MAP_ROWS][MAP_COLUMNS], const char* _filename) {
    std::fstream file;
    file.open(_filename, std::ios::out); // Open C++ file stream for writing
    //if (file == nullptr) {    // old C-style file open check
    if (!file.is_open()) { // Check if file opened successfully
        return;
    }

    // Write each single tileArray charater into our file stream
    for (int y = 0; y < PCG::MAP_ROWS; y++) {
        for (int x = 0; x < PCG::MAP_COLUMNS; x++) {
            //fputc(PCG::GetTileChar(_tileArray[y][x]), file);  // old c-style file write
            file.put(PCG::GetTileChar(_tileArray[y][x])); // Write char to C++ file stream
        }
        //fputc('\n', file); // New line at end of row
        file.put('\n'); // New line at end of row for C++ file stream
    }
    //fclose(file); // old C-style file close
    file.close(); // Close C++ file stream
    std::cout << "Map saved to " << _filename << std::endl;
}


// ============================================= 
// void PCG_LoadMapData(TileType _tileArray[MAP_ROWS][MAP_COLUMNS], const char* _filename)
// Load our tilemap data from a text file, using input _filename
// ============================================= 
void PCG::LoadMapData(TileType _tileArray[MAP_ROWS][MAP_COLUMNS], const char* _filename) {
    //FILE* file = fopen(_filename, "r"); // "r" = Read // old c style
    std::fstream file;  // C++ file stream object for reading
    file.open(_filename, std::ios::in); // Open C++ file stream for reading
    //if (file == NULL) {   // old C-style file open check
    if (!file.is_open()) { // Check if file opened successfully for C++ stream
        return;
    }

    // Get each character from our file stream, and load it into our tileMap array
    for (int y = 0; y < PCG::MAP_ROWS; y++) {
        for (int x = 0; x < PCG::MAP_COLUMNS; x++) {
            //int ch = fgetc(file); // old C-style file read
            int ch = file.get(); // Get char from C++ file stream
            // Skip invisible newline characters
            while (ch == '\n' || ch == '\r') {
                //ch = fgetc(file); // old C-style file read for skipping newlines
                ch = file.get(); // Get char from C++ file stream for skipping newlines
            }

            if (ch == PCG::GRASS_CHAR) {
                _tileArray[y][x] = PCG::TileType::TILE_TYPE_GRASS;
            }
            else if (ch == PCG::ROCK_CHAR) {
                _tileArray[y][x] = PCG::TileType::TILE_TYPE_ROCK;
            }
        }
    }
    //fclose(file); // old C-style file close
    file.close(); // Close C++ file stream
    // printf("Map loaded from %s\n", _filename);   // old C-style print statement
    std::cout << "Map loaded from " << _filename << std::endl; // C++ style print statement
}

// ============================================= 
// void PCG_SaveMapImage(TileType _tileArray[MAP_ROWS][MAP_COLUMNS], const char* filename)
// Store our tileMap data as a .png image, using the input filename.
// ============================================= 
void PCG::SaveMapImage(TileType _tileArray[MAP_ROWS][MAP_COLUMNS], const char* filename) {
    Image mapImage = GenImageColor(MAP_COLUMNS, MAP_ROWS, BLACK);
    
    for (int y = 0; y < MAP_ROWS; y++) {
        for (int x = 0; x < MAP_COLUMNS; x++) {
            Color c = GetTileColor(_tileArray[y][x]);
            ImageDrawPixel(&mapImage, x, y, c);
        }
    }
    if(ExportImage(mapImage, filename)) { 
        std::cout << "Image saved: " << filename << std::endl;
    }
    UnloadImage(mapImage);
}

// Required to call Raylib gui buttons. Add this near the top of PCG.c
#define RAYGUI_IMPLEMENTATION
#include "raygui.h" 

// ============================================= 
// void PCG_DrawGUI(TileType tileArray[MAP_ROWS][MAP_COLUMNS])
// ============================================= 
void PCG::PCG_DrawGUI(TileType tileArray[MAP_ROWS][MAP_COLUMNS]) {
    // Reset Button
    if(GuiButton(RESET_BUTTON_BOUNDS, "Reset Map")) {
        CreateMap(tileArray);
    }

    // Save Data Button
    Rectangle saveRect = { BUTTON_X, BUTTON_Y - 70, BUTTON_WIDTH, BUTTON_HEIGHT };
    if(GuiButton(saveRect, "Save Map Data")) {
        SaveMapData(tileArray, MAP_TEXT_FILENAME);
    }
    
    // Load Data Button
    Rectangle loadRect = { BUTTON_X, BUTTON_Y - 140, BUTTON_WIDTH, BUTTON_HEIGHT };
    if(GuiButton(loadRect, "Load Map Data")) {
        LoadMapData(tileArray, MAP_TEXT_FILENAME);
    }

    // Save Image Button
    Rectangle imgRect = { BUTTON_X, BUTTON_Y - 210, BUTTON_WIDTH, BUTTON_HEIGHT };
    if(GuiButton(imgRect, "Save Map PNG")) {
        SaveMapImage(tileArray, MAP_IMAGE_FILENAME);
    }
}