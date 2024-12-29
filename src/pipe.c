#include <stdio.h>
#include <stdbool.h>
#include "raylib.h"
#include "main.h"

bool CheckPipeVisible(int index)
{
  return (bool)(pipes[index].x + textures.pipeGreen.width * PIPE_SCALE > 0 && pipes[index].x < SCREEN_WIDTH);
}

int FindFarthestPipe()
{
  int farthestPipeInd = 0;
  int farthestPipeX = pipes[0].x;

  for (int i = 1; i < MAX_PIPES; i++)
  {
    if (pipes[i].x > farthestPipeX)
    {
      farthestPipeInd = i;
      farthestPipeX = pipes[i].x;
    }
  }
  return farthestPipeInd;
}

void DrawPipe()
{
  if (game.state == START)
  {
    if (IsKeyPressed(KEY_SPACE))
    {
      for (int i = 0; i < MAX_PIPES; i++)
      {
        if (i == 0)
        {
          pipes[i].x = DEFAULT_PIPE_X;
          pipes[i].y = GetRandomValue(SCREEN_HEIGHT / 3, SCREEN_HEIGHT - SCREEN_HEIGHT / 3);
          continue;
        }

        pipes[i].x = pipes[i - 1].x + textures.pipeGreen.width * PIPE_SCALE + pipeState.horizontalGap;
        pipes[i].y = GetRandomValue(SCREEN_HEIGHT / 3, SCREEN_HEIGHT - SCREEN_HEIGHT / 3);
      }
    }
    return;
  }

  if (game.frame - game.startFrame < 3)
    return;

  const Vector2 farthestPipe = pipes[FindFarthestPipe()];

  for (int i = 0; i < MAX_PIPES; i++)
  {
    if (!CheckPipeVisible(i) && pipes[i].x < 0)
    {
      pipes[i].x = farthestPipe.x + textures.pipeGreen.width * PIPE_SCALE + pipeState.horizontalGap;
      pipes[i].y = GetRandomValue(SCREEN_HEIGHT / 3, SCREEN_HEIGHT - SCREEN_HEIGHT / 3);
    }
  }

  const float width = textures.pipeGreen.width * PIPE_SCALE;
  const float height = textures.pipeGreen.height * PIPE_SCALE;
  const Rectangle pipeRectangle = (Rectangle){0, 0, textures.pipeGreen.width, textures.pipeGreen.height};

  for (int i = 0; i < MAX_PIPES; i++)
  {
    if (!CheckPipeVisible(i) && pipes[i].x < 0)
      continue;

    /* code */
    const float x1 = (float)pipes[i].x + width;
    const float x2 = (float)pipes[i].x;
    const float y1 = (float)pipes[i].y - pipeState.verticalGap / 2;
    const float y2 = (float)pipes[i].y + pipeState.verticalGap / 2;

    if (game.state == PLAYING)
    {
      // if (
      //     CheckCollisionRecs(
      //         (Rectangle){bird.position.x, bird.position.y, bird.textures[0].width, bird.textures[0].height},
      //         (Rectangle){x2, 0, width, height - y1})

      //     || CheckCollisionRecs(
      //            (Rectangle){bird.position.x, bird.position.y, bird.textures[0].width, bird.textures[0].height},
      //            (Rectangle){x2, y2, width, SCREEN_HEIGHT - y2}))

      // {
      //   game.state = OVER;
      // }
      // else
      // {

      //   pipes[i].x -= pipeState.speed;
      // }
      pipes[i].x -= pipeState.speed;
    }

    DrawTexturePro(
        textures.pipeGreen,
        pipeRectangle,
        (Rectangle){x1, y1, width, height},
        (Vector2){0, 0},
        180.0f,
        WHITE);
    DrawTexturePro(
        textures.pipeGreen,
        pipeRectangle,
        (Rectangle){x2, y2, width, height},
        (Vector2){0, 0},
        0,
        WHITE);
  }
}
