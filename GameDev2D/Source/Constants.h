#pragma once

//Block width is 128 px, buffer is 8 px

const int COLUMNAMT = 7; //Number of columns
const int LEVELAMT = 5; //Number of rows, referred to as levels
const int STARTCOLUMN = 3; //The column every block starts in
const int UIBUFFER = 25; //The distance between the UI sprites and the screen edges

//Movement multipliers
const float MOVELEFT = -1.0f;
const float MOVERIGHT = 1.0f;

//Controls the intervals each block moves at
const float SPEEDS[LEVELAMT] = { 0.21f, 0.16f, 0.11f, 0.06f, 0.02f };

//Testing speeds
//const float SPEEDS[LEVELAMT] = { 0.21f, 0.21f, 0.21f, 0.21f, 0.21f };

//Indicates the potential placements of blocks. Increments of 136 (block width + buffer)
const float LEVELS[LEVELAMT] = { 24.0f, 160.0f, 296.0f, 432.0f, 568.0f };
const float COLUMNS[COLUMNAMT] = { 167.0f, 303.0f, 439.0f, 575.0f, 711.0f, 847.0f, 983.0f };

//UI sprite filenames (Winner not included)
const std::string UIFILENAMES[LEVELAMT] = { "Level1", "Level2", "Level3", "Level4", "Level5" };