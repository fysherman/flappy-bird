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
#include "main.h"
#include "bird.h"
#include "pipe.h"

Textures textures;

Texture2D birdTextures[3];

Game game = {START, 0, 0, 0};

Pipe pipe = {100, 200};

Bird bird = {
    {(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2},
    0,
    0,
    0.2f,
    4.0f,
    7.0f,
    0.2f,
    {{0, 0}, {0, 0}, {0, 0}}};

pipes[MAX_PIPES];

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
  textures.background = LoadTexture("objects/background_day.png");
  textures.base = LoadTexture("objects/base.png");
  textures.birdMidFlap = LoadTexture("objects/yellowbird_midflap.png");
  textures.birdDownFlap = LoadTexture("objects/yellowbird_downflap.png");
  textures.birdUpFlap = LoadTexture("objects/yellowbird_upflap.png");
  textures.pipeGreen = LoadTexture("objects/pipe_green.png");

  bird.textures[0] = textures.birdDownFlap;
  bird.textures[1] = textures.birdMidFlap;
  bird.textures[2] = textures.birdUpFlap;
}

void DrawFrame()
{
  // drawing
  BeginDrawing();

  // Setup the back buffer for drawing (clear color and depth buffers)
  ClearBackground(BLACK);

  game.frame += GetFrameTime();

  float backgroundSize = 0;
  float backgroundScale = (float)SCREEN_HEIGHT / textures.background.height;

  while (backgroundSize < SCREEN_WIDTH)
  {
    // Draw the background texture
    DrawTextureEx(textures.background, (Vector2){backgroundSize, 0}, 0, backgroundScale, WHITE);
    backgroundSize += (float)textures.background.width * backgroundScale;
  }

  DrawPipe();

  float baseSize = 0;

  while (baseSize < SCREEN_WIDTH)
  {
    // Draw the base texture
    DrawTextureEx(textures.base, (Vector2){baseSize, SCREEN_HEIGHT - textures.base.height / 2}, 0, 1.0f, WHITE);
    baseSize += (float)textures.base.width;
  }

  DrawBird();
  // end the frame and get ready for the next one  (display frame, poll input, etc...)
  EndDrawing();
}

void EndGame()
{
  // unload our texture so it can be cleaned up
  UnloadTexture(textures.background);
  UnloadTexture(textures.base);
  UnloadTexture(textures.birdMidFlap);
  UnloadTexture(textures.birdDownFlap);
  UnloadTexture(textures.birdUpFlap);

  // destroy the window and cleanup the OpenGL context
  CloseWindow();
}
