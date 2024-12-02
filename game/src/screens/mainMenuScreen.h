#pragma once
#include "../engine/Application.h"
#include "../engine/components.h"
namespace game
{
	class MainMenuScreen : public engine::Screen
	{
	
		Texture2D buttonTexture;
		std::vector<engine::Button> buttons;
		bool editEnabled = true;
	public:
		int newGameScreen = -1, continueGameScreen = -1, settingsScreen = -1;

	public:
		virtual void Init(engine::Settings& settings) override;
		virtual void Unload(engine::Settings& settings) override;
		virtual void Update(engine::Settings& settings, float dt) override;
		virtual void Draw(engine::Settings& settings) override;
		virtual void Edit(engine::Settings& settings) override;
	};
}
