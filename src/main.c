/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

For a C++ project simply rename the file to .cpp and re-run the build script

-- Copyright (c) 2020-2024 Jeffery Myers
--
--This software is provided "as-is", without any express or implied warranty. In no event
--will the authors be held liable for any damages arising from the use of this software.

--Permission is granted to anyone to use this software for any purpose, including commercial
--applications, and to alter it and redistribute it freely, subject to the following restrictions:

--  1. The origin of this software must not be misrepresented; you must not claim that you
--  wrote the original software. If you use this software in a product, an acknowledgment
--  in the product documentation would be appreciated but is not required.
--
--  2. Altered source versions must be plainly marked as such, and must not be misrepresented
--  as being the original software.
--
--  3. This notice may not be removed or altered from any source distribution.

*/

#include <stdio.h>
#include "raylib.h"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir

const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 500;

void InitGame();
void DrawFrame();
void EndGame();

typedef struct Background
{
  Texture2D texture;
  float scale;
} Background;

Background background;

int main()
{
  InitGame();

  // game loop
  while (!WindowShouldClose()) // run the loop untill the user presses ESCAPE or presses the Close button on the window
  {
    DrawFrame();
  }

  EndGame();

  return 0;
}

void InitGame()
{
  // Tell the window to use vsync and work on high DPI displays
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  // Create the window and OpenGL context
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bird");

  // Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
  SearchAndSetResourceDir("resources");

  // Load a texture from the resources directory
  background.texture = LoadTexture("objects/background_day.png");
  background.scale = (float)SCREEN_HEIGHT / background.texture.height;
}

void DrawFrame()
{
  // drawing
  BeginDrawing();

  // Setup the back buffer for drawing (clear color and depth buffers)
  ClearBackground(BLACK);

  // Draw the background texture
  DrawTextureEx(background.texture, (Vector2){0, 0}, 0, background.scale, WHITE);

  // end the frame and get ready for the next one  (display frame, poll input, etc...)
  EndDrawing();
}

void EndGame()
{
  // unload our texture so it can be cleaned up
  UnloadTexture(background.texture);

  // destroy the window and cleanup the OpenGL context
  CloseWindow();
}
