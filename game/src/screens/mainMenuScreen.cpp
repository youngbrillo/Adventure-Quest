#include "mainMenuScreen.h"

struct bfab
{
	std::string text;
	std::function<void(void*)> clickhandle;
};

void game::MainMenuScreen::Init(engine::Settings& settings)
{
	std::vector<bfab> bList = { 
		{"Start", [&settings, this](void*) {
			printf("Start Game!\n");  

			settings.changeScreen = true;
			settings.nextScreenId = this->newGameScreen;
		
		}},
		{"Continue", [&settings, this](void*) {
			printf("continue Game!\n");
			settings.changeScreen = true;
			settings.nextScreenId = this->continueGameScreen;
		 }},
		{"Settings", [&settings, this](void*) {
			printf("View settings screen!\n");
			settings.changeScreen = true;
			settings.nextScreenId = this->settingsScreen;
		  }},
		{"Quit To Desktop", [&settings](void*) {
			printf("quit to desktop\n");  
			settings.appShouldClose = true;
		}}
	};
	float vert = 30, padding = 10.0f;
	buttonTexture = LoadTexture("./resources/UI/panel-transparent-center-025.png");
	if (!IsTextureValid(buttonTexture))
		buttonTexture = { 1,1,1 };

	int id = 0;
	for(auto& text : bList)
	{
		buttons.push_back(engine::Button{});

		engine::Button& button = buttons[id++];
		button.panel.texture = buttonTexture;
		button.panel.npatch.source = { 0, 0, (float)button.panel.texture.width, (float)button.panel.texture.height };
		button.panel.destination = Rectangle{ (float)GetScreenWidth() / 2, vert, 180, 180 };
		button.panel.npatch.left = 24;
		button.panel.npatch.right = 24;
		button.panel.npatch.bottom = 24;
		button.panel.npatch.top = 24;
		button.panel.npatch.layout = NPATCH_NINE_PATCH;

		button.text.text = text.text;
		button.resize();
		vert += button.panel.destination.height + padding;
		button.altPanelColor = LIGHTGRAY;
		button.altTextColor = YELLOW;

		button.onClick = text.clickhandle;

	}

	settings.backgroundColor = BLACK;
}

void game::MainMenuScreen::Unload(engine::Settings& settings)
{
	settings.backgroundColor = RAYWHITE;
	buttons.clear();
	if(buttonTexture.id > 1)
		UnloadTexture(buttonTexture);
}

void game::MainMenuScreen::Update(engine::Settings& settings, float dt)
{
}

void game::MainMenuScreen::Draw(engine::Settings& settings)
{
	for (engine::Button& button : buttons)
	{
		if (button.Draw())
		{
			button.onClick(nullptr);
			break;
		}
	}

}

void game::MainMenuScreen::Edit(engine::Settings& settings)
{
	if (!editEnabled)
		return;

	ImGui::Begin("Main Menu Screen", &editEnabled);

	for (engine::Button& button : buttons)
	{
		if (ImGui::TreeNode(&button, "Button"))
		{
			if (ImGui::TreeNode("Panel"))
			{
				ImGui::DragFloat4("destination", &button.panel.destination.x);
				ImGui::DragFloat2("origin", &button.panel.origin.x);
				ImGui::DragFloat("angle", &button.panel.angle);

				Vector4 color = ColorNormalize(button.panel.tint);
				if (ImGui::ColorEdit4("tint", &color.x))
				{
					button.panel.tint = ColorFromNormalized(color);
				}
				if(ImGui::TreeNode("N patch Info"))
				{
					ImGui::DragInt("left", &button.panel.npatch.left);
					ImGui::DragInt("right", &button.panel.npatch.right);
					ImGui::DragInt("top", &button.panel.npatch.top);
					ImGui::DragInt("bottom", &button.panel.npatch.bottom);
					ImGui::SliderInt("layout", &button.panel.npatch.layout, 0, 2);
					ImGui::TreePop();
				}
				ImGui::TreePop();
			}

			if (ImGui::Button("resize"))
				button.resize();
			ImGui::TreePop();
		}
	}


	ImGui::End();
}
