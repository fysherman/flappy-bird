#pragma once

#include <stdbool.h>
#include "raylib.h"

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500
#define MAX_PIPES 5
#define BIRD_TEXTURES 3

typedef struct Textures
{
  Texture2D background;
  Texture2D base;
  Texture2D pipeGreen;
  Texture2D birdMidFlap;
  Texture2D birdDownFlap;
  Texture2D birdUpFlap;
  Texture2D gameOver;
  Texture2D gameStart;
} Textures;

typedef struct Bird
{
  Vector2 position;
  float speed;
  float rotation;
  float gravity;
  float velocity;
  float rotationSpeed;
  float flapSpeed;
  Texture2D textures[BIRD_TEXTURES];
} Bird;

typedef struct Pipe
{
  int pipeVerticalGap;
  int pipeHorizontalGap;
} Pipe;

typedef enum GameState
{
  START,
  PLAYING,
  OVER,
} GameState;

typedef struct Game {
  GameState state;
  int score;
  int highScore;
  float frame;
} Game;

extern Bird bird;
extern Game game;
extern Textures textures;
extern Texture2D pipes[5];

void InitGame();
void DrawFrame();
void EndGame();
