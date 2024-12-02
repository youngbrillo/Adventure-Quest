#pragma once

#include "raylib.h"
#include <string>
#include <vector>
#include <imgui.h>

namespace engine
{
	struct Settings;
	class Screen
	{
	public:
		int screenId = -1;
		bool wantTransition = false;
	public:
		virtual void Init(engine::Settings& settings) {};
		virtual void Unload(engine::Settings& settings) {};
		virtual void Update(engine::Settings& settings, float dt) {};
		virtual void Draw(engine::Settings& settings) {};
		virtual void DrawTransition(engine::Settings& settings);
		virtual void Edit(engine::Settings& settings) {};
	};

	struct ScreenTransition
	{
		bool onTransition = false;
		float transAlpha = 0.0f;
		bool transFadeOut = false;
		int transFromScreen = -1;
		int transToScreen = -1;
		float transitionFadeInSpeed = 5.0f, transitionFadeOutSpeed = 10.0f;
	};
	struct Settings
	{
		Screen* currentScreen = nullptr;
		int nextScreenId = 0;
		Font font = { 0 };
		Music music = { 0 };
		Sound soundfx = { 0 };
		ScreenTransition screenTransition;

		int screenWidth = 800;
		int screenHeight = 450;
		std::string windowTitle = "Application";
		Color backgroundColor = RAYWHITE;
		bool changeScreen = false;
		bool appShouldClose = false;
	};


	class Application
	{
		bool _initialized = false;
	public:
		Settings& settings;
		std::vector<Screen*> screens;
	public:
		Application(Settings& external_settings);
		~Application();
		void Init();
		void Run();
	private:
		void Destroy();
		void update(float dt);
		void updateTransition(float dt);
		void draw();

	public:
		Screen* AddScreen(Screen* screen);
		Screen* SetScreen(int screen);
		void ChangeToScreen(int screen);
		void TransitionToScreen(int screen); // Request transition to next screen


	};
}