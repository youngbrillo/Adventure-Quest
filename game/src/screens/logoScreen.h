#pragma once
#include "../engine/Application.h"
#include "../engine/components.h"

namespace game
{
	class LogoScreen : public engine::Screen
	{
		 int framesCounter = 0;
		 int finishScreen = 0;

		 int logoPositionX = 0;
		 int logoPositionY = 0;

		 int lettersCount = 0;

		 int topSideRecWidth = 0;
		 int leftSideRecHeight = 0;

		 int bottomSideRecWidth = 0;
		 int rightSideRecHeight = 0;

		 int state = 0;              // Logo animation states
		 float alpha = 1.0f;         // Useful for fading
		 engine::Timer timer;
	public:
		virtual void Init(engine::Settings& settings) override;
		virtual void Unload(engine::Settings& settings) override;
		virtual void Update(engine::Settings& settings, float dt) override;
		virtual void Draw(engine::Settings& settings) override;
	};
}
