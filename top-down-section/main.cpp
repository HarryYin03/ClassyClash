#include "raylib.h"
#include "raymath.h"
#include "character.h"
#include "Prop.h"
#include "Enemy.h"


int main()
{
    const int windowWidth = 384;
    const int windowHeight = 384;
    InitWindow(windowWidth, windowHeight, "George's Top Down");
    Texture2D map = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 mapPos = {0.0, 0.0};
    const float mapScale{4.0f};

    Character knight{windowWidth, windowHeight};


    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop { Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}
    };

    Enemy goblin{
        Vector2{},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")
    };

    goblin.setTarget(&knight);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);
        
        for (auto prop: props)
        {
            prop.Render(knight.getWorldPos());
        }

        knight.tick(GetFrameTime());
        if  (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > map.width * mapScale||
            knight.getWorldPos().y + windowHeight > map.height * mapScale )
        {
            knight.undoMovement();
        }
        // check prop collicsion
        for (auto prop : props)
        {
            if(CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
            {
                knight.undoMovement();
            }
        }

        goblin.tick(GetFrameTime());


        EndDrawing();
    }
    CloseWindow();
}

