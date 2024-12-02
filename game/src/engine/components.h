#pragma once

#include <raylib.h>
#include <string>
#include <functional>

namespace engine
{
	struct Timer
	{
		float duration = 0.0f, limit = 1.0f;
		bool loop = true;

		Timer(float timeLimit = 1.0f, bool loopEnabled = true)
			: duration(0.0f), limit(timeLimit), loop(loopEnabled)
		{}

		bool countDown(float dt)
		{
			if (isFinished())
			{
				if (!loop)
					return true;
				reset();
			}

			duration += dt;
			if (duration >= limit)
			{
				duration = limit;
				return true;
			}

			return false;
		}

		void reset()
		{
			duration = 0.0f;
		}
		bool isFinished() const
		{
			return duration >= limit;
		}
	};


	struct Panel
	{
		Texture2D texture = { 1,1,1 };
		NPatchInfo npatch = NPatchInfo{
			Rectangle{0, 0, 1,1},
			0, 0, 0, 0
		};
		Rectangle destination = { 0, 0, 64, 64 };
		Vector2 origin = { 0.0f, 0.0f };
		float angle = 0.0f;
		Color tint = WHITE;


		void Draw(Color* color = nullptr) const;
	};

	struct Text
	{
		std::string text;
		Font font = GetFontDefault();
		Vector2 position = { 0.0f, 0.0f }, origin = { 0.0, 0.0f };
		float fontSize = 50.0f;
		float fontSpacing = 1.0f;
		float angle = 0.0f;
		Color tint = BLACK;

		void Draw(Vector2 offset = {0.0f, 0.0f}, float angleOffset = 0, Color* color = nullptr) const;
		Vector2 Size() const;
		Rectangle bounds() const;
	};
	struct Button
	{
		Panel panel;
		Text text;
		Color altPanelColor = BLACK, altTextColor = YELLOW;
		bool Draw();
		void resize();

		std::function<void(void*)> onClick;
	};
}