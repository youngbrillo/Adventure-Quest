#pragma once
#include "../engine/Application.h"

namespace game
{
	class BattleScreen : public engine::Screen
	{
	public:
		BattleScreen();
		virtual void Init(engine::Settings& settings) override;
		virtual void Unload(engine::Settings& settings) override;
		virtual void Update(engine::Settings& settings, float dt) override;
		virtual void Draw(engine::Settings& settings) override;
	};
}
