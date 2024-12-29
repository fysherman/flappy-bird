#include <stdio.h>
#include "raylib.h"
#include "main.h"

Texture2D GetTexture()
{
  if (game.state == OVER)
    return bird.textures[0];

  const int textureIndex = (int)(game.frame / bird.flapSpeed) % BIRD_TEXTURES;

  return bird.textures[textureIndex];
}

void DrawBird()
{
  // Speed handle
  if (IsKeyPressed(KEY_SPACE))
  {
    if (game.state == START)
    {
      game.startFrame = game.frame;
    }
    game.state = PLAYING;
    bird.speed = bird.velocity;
  }
  else if (game.state == PLAYING)
  {
    bird.speed -= bird.gravity;
  }

  if (IsKeyPressed(KEY_ENTER))
  {
    game.state = START;
    bird.position = (Vector2){(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2};
    bird.speed = 0;
    bird.rotation = 0;
  }

  Texture2D birdTexture = GetTexture();

  // Collision base
  if (CheckCollisionRecs(
    (Rectangle){bird.position.x, bird.position.y, birdTexture.width, birdTexture.height},
    (Rectangle){0, SCREEN_HEIGHT - textures.base.height / 2, SCREEN_WIDTH, textures.base.height / 2}
  )) {
    game.state = OVER;
  }

  if (game.state == PLAYING)
  {
    bird.position.y -= bird.speed;
    if (bird.speed > -4.0f)
    {
      bird.rotation = -30.0f;
    }
    else if (bird.rotation < 90.0f)
    {
      bird.rotation += bird.rotationSpeed;
    }
  }

  // Draw the bird texture
  DrawTexturePro(
      birdTexture,
      (Rectangle){0, 0, birdTexture.width, birdTexture.height},
      (Rectangle){bird.position.x, bird.position.y, birdTexture.width, birdTexture.height},
      (Vector2){birdTexture.width / 2, birdTexture.height / 2},
      bird.rotation,
      WHITE);
}