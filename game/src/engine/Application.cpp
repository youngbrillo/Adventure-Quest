#include "Application.h"
#include "utils/rlImGui.h"
engine::Application::Application(Settings& external_settings)
	: settings(external_settings)
{
}

engine::Application::~Application()
{
}

void engine::Application::Init()
{
	InitWindow(settings.screenWidth, settings.screenHeight, settings.windowTitle.c_str());
	InitAudioDevice();

    // Load global data (assets that must be available in all screens, i.e. font)
    //settings.font = LoadFont("resources/mecha.png");
    //settings.music = LoadMusicStream("resources/ambient.ogg");
    //settings.soundfx = LoadSound("resources/coin.wav");

    if (IsMusicValid(settings.music)) {
        SetMusicVolume(settings.music, 1.0f);
        PlayMusicStream(settings.music);
    }

    if (!IsFontValid(settings.font))
    {
        settings.font = GetFontDefault();
    }
    rlImGuiSetup(true);
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_DockingEnable;

    // Setup and init first screen
    SetScreen(settings.nextScreenId);// screens[defaultScreen];

    _initialized = true;
}

void engine::Application::Run()
{
    if (!_initialized)
        Init();
    while (!settings.appShouldClose)
    {
        if (WindowShouldClose())
            settings.appShouldClose = true;

        float dt = GetFrameTime();
        if (settings.changeScreen)
        {
            TransitionToScreen(settings.nextScreenId);
        }
        update(dt);
        draw();
    }

    Destroy();
}

void engine::Application::Destroy()
{
    rlImGuiShutdown();
    UnloadFont(settings.font);
    UnloadMusicStream(settings.music);
    UnloadSound(settings.soundfx);
    CloseAudioDevice();     // Close audio context
    CloseWindow();          // Close window and OpenGL context
}

void engine::Application::update(float dt)
{
    if (IsMusicStreamPlaying(settings.music))
        UpdateMusicStream(settings.music);

    if (settings.currentScreen)
    {
        settings.currentScreen->Update(settings, dt);
        if (settings.currentScreen->wantTransition)
            TransitionToScreen(settings.nextScreenId);
    }
    updateTransition(dt);
    draw();
}

void engine::Application::updateTransition(float dt)
{
    if (!settings.screenTransition.onTransition)
    {
        return;
    }
    if (!settings.screenTransition.transFadeOut)
    {
        settings.screenTransition.transAlpha += settings.screenTransition.transitionFadeInSpeed * dt;

        // NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
        // For that reason we compare against 1.01f, to avoid last frame loading stop
        if (settings.screenTransition.transAlpha > 1.01f)
        {
            settings.screenTransition.transAlpha = 1.0f;

            SetScreen(settings.screenTransition.transToScreen);

            // Activate fade out effect to next loaded screen
            settings.screenTransition.transFadeOut = true;
        }
    }
    else  // Transition fade out logic
    {
        settings.screenTransition.transAlpha -= settings.screenTransition.transitionFadeOutSpeed * dt;

        if (settings.screenTransition.transAlpha < -0.01f)
        {
            settings.screenTransition.transAlpha = 0.0f;
            settings.screenTransition.transFadeOut = false;
            settings.screenTransition.onTransition = false;
            settings.screenTransition.transFromScreen = -1;
            settings.screenTransition.transToScreen = -1;
        }
    }

}

void engine::Application::draw()
{
    BeginDrawing();
    ClearBackground(settings.backgroundColor);

    if (settings.currentScreen) {

        if (settings.screenTransition.onTransition)
            settings.currentScreen->DrawTransition(settings);
        else
            settings.currentScreen->Draw(settings);
    }

    rlImGuiBegin();
    if (settings.currentScreen)
    {
        settings.currentScreen->Edit(settings);
    }

    rlImGuiEnd();


    EndDrawing();
}

engine::Screen* engine::Application::AddScreen(Screen* screen)
{
    screens.emplace_back(screen);
    screen->screenId = screens.size() - 1;
    return screen;
}

engine::Screen* engine::Application::SetScreen(int screen)
{
    if (screen >= 0 && screen < screens.size()) {
        
        if (settings.currentScreen)
            settings.currentScreen->Unload(settings);

        settings.currentScreen = screens[screen];
        settings.currentScreen->Init(settings);


        return settings.currentScreen;
    }
    return nullptr;
}

void engine::Application::ChangeToScreen(int screen)
{
}

void engine::Application::TransitionToScreen(int screen)
{
    settings.screenTransition.onTransition = true;
    settings.screenTransition.transFadeOut = false;
    settings.screenTransition.transFromScreen = settings.currentScreen ? settings.currentScreen->screenId : -1;
    settings.screenTransition.transToScreen = screen;
    settings.screenTransition.transAlpha = 0.0f;
    settings.changeScreen = false;
}

void engine::Screen::DrawTransition(engine::Settings& settings)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, settings.screenTransition.transAlpha));
}
