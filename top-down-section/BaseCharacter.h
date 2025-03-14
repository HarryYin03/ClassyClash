#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include "raylib.h"

class BaseCharacter
{
    public:
        BaseCharacter();
        Vector2 getWorldPos()
        {
            return worldPos;
        };
        void undoMovement();
        Rectangle getCollisionRec();
        virtual void tick(float deltaTime);
    protected:
        Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
        Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
        Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
        Vector2 screenPos{};
        Vector2 worldPos{};
        Vector2 worldPosLastFrame{};
        // 1: facing right, -1 : facing left
        float rightLeft{1.f};
        // animation variables

        float runningTime{};
        int frame{};
        const int maxFrames{6};
        const float updateTime{1.f / 12.f};
        const float speed{4.f};
        float width{};
        float height{};
        float scale{4.0f};
};

#endif // BASE_CHARACTER_H