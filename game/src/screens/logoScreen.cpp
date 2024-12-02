#include "logoScreen.h"

void game::LogoScreen::Init(engine::Settings& settings)
{
    finishScreen = 0;
    framesCounter = 0;
    lettersCount = 0;

    logoPositionX = GetScreenWidth() / 2 - 128;
    logoPositionY = GetScreenHeight() / 2 - 128;

    topSideRecWidth = 16;
    leftSideRecHeight = 16;
    bottomSideRecWidth = 16;
    rightSideRecHeight = 16;

    state = 0;
    alpha = 1.0f;

    timer.limit = 1.0f / 60.0f;
    timer.reset();
}

void game::LogoScreen::Unload(engine::Settings& settings)
{
}

void game::LogoScreen::Update(engine::Settings& settings, float dt)
{
    if (IsKeyReleased(KEY_ENTER)){
        state++;
        if (state > 3) {
            state = 3;
            settings.nextScreenId = screenId + 1; //go to next scene
            settings.changeScreen = true;
        }
    }

    if (state == 0)                 // State 0: Top-left square corner blink logic
    {
        if (timer.countDown(dt))
            framesCounter++;
        else
            return;

        if (framesCounter == 80)
        {
            state = 1;
            framesCounter = 0;      // Reset counter... will be used later...
        }
    }
    else if (state == 1)            // State 1: Bars animation logic: top and left
    {
        topSideRecWidth += 8;
        leftSideRecHeight += 8;

        if (topSideRecWidth == 256) state = 2;
    }
    else if (state == 2)            // State 2: Bars animation logic: bottom and right
    {
        bottomSideRecWidth += 8;
        rightSideRecHeight += 8;

        if (bottomSideRecWidth == 256) state = 3;
    }
    else if (state == 3)            // State 3: "raylib" text-write animation logic
    {
        if (timer.countDown(dt))
            framesCounter++;
        else
            return;

        if (lettersCount < 10)
        {
            if (framesCounter / 12)   // Every 12 frames, one more letter!
            {
                lettersCount++;
                framesCounter = 0;
            }
        }
        else    // When all letters have appeared, just fade out everything
        {
            if (framesCounter > 200)
            {
                alpha -= 0.02f;

                if (alpha <= 0.0f)
                {
                    alpha = 0.0f;
                    finishScreen = 1;   // Jump to next screen
                }
            }
        }
    }
}

void game::LogoScreen::Draw(engine::Settings& settings)
{
    if (state == 0)         // Draw blinking top-left square corner
    {
        if ((framesCounter / 10) % 2) DrawRectangle(logoPositionX, logoPositionY, 16, 16, BLACK);
    }
    else if (state == 1)    // Draw bars animation: top and left
    {
        DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, BLACK);
        DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, BLACK);
    }
    else if (state == 2)    // Draw bars animation: bottom and right
    {
        DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, BLACK);
        DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, BLACK);

        DrawRectangle(logoPositionX + 240, logoPositionY, 16, rightSideRecHeight, BLACK);
        DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, BLACK);
    }
    else if (state == 3)    // Draw "raylib" text-write animation + "powered by"
    {
        DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, Fade(BLACK, alpha));
        DrawRectangle(logoPositionX, logoPositionY + 16, 16, leftSideRecHeight - 32, Fade(BLACK, alpha));

        DrawRectangle(logoPositionX + 240, logoPositionY + 16, 16, rightSideRecHeight - 32, Fade(BLACK, alpha));
        DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, Fade(BLACK, alpha));

        DrawRectangle(GetScreenWidth() / 2 - 112, GetScreenHeight() / 2 - 112, 224, 224, Fade(RAYWHITE, alpha));

        DrawTextEx(settings.font, TextSubtext("raylib", 0, lettersCount), Vector2{ (float)GetScreenWidth() / 2 - 44,(float) GetScreenHeight() / 2 + 48 }, 50, 1.0f, Fade(BLACK, alpha));

        if (framesCounter > 20) //DrawText("powered by", logoPositionX, logoPositionY - 27, 20, Fade(DARKGRAY, alpha));
            DrawTextEx(settings.font,"powered by", Vector2{ (float)logoPositionX, (float)logoPositionY - 27 }, 20,1.0f, Fade(DARKGRAY, alpha));
    }
}
