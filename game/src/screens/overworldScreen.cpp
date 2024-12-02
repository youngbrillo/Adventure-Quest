#include "overworldScreen.h"
#include <raymath.h>

void game::Overworld::Init(engine::Settings& settings)
{
	displayText.font = settings.font;
	displayText.position.x = settings.screenWidth / 2;
	displayText.position.y = settings.screenHeight / 2;
	displayText.text = "Nothing to see here...";
	displayText.tint = BLACK;

	displayText.origin = displayText.Size();

	displayText.origin = Vector2Scale(displayText.origin, 0.5f);
	settings.backgroundColor = LIGHTGRAY;
}

void game::Overworld::Unload(engine::Settings& settings)
{
}

void game::Overworld::Update(engine::Settings& settings, float dt)
{
}

void game::Overworld::Draw(engine::Settings& settings)
{
	displayText.Draw();
}
