#include "raylib.h"
#include "raymath.h"
#include "character.h"
{
    Vector2 direction{};
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0;
    if (Vector2Length(direction) != 0.0)
    {
        // set worldPos = worldPos + direction

        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f; // if direction.x < 0, then knight is facing left
        texture = run;
    }
    else
    {
        texture = idle;
    }
    // update the animation
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames)
        {
            frame = 0;
        }
    }
    // draw the character
    Rectangle source{frame * (float)texture.width / 6.f, 0.f, rightLeft * (float)texture.width / 6.f, (float)texture.height};
    Rectangle dest{screenPos.x, screenPos.y, 4.0f * (float)texture.width / 6.0f, 4.0f * (float)texture.height};

    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}

int main(void)
{
    const int windowWidth = 384;
    const int windowHeight = 384;
    InitWindow(windowWidth, windowHeight, "George's Top Down");
    Texture2D map = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 mapPos = {0.0, 0.0};

    Character knight;
    knight.setScreenPos(windowWidth, windowHeight);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);
        knight.tick(GetFrameTime());

        EndDrawing();
    }
    CloseWindow();
}
