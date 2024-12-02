
#include "engine/engine.h"
#include "screens/logoScreen.h"
#include "screens/mainMenuScreen.h"
#include "screens/overworldScreen.h"
#include "screens/BattleMenuScreen.h"

int main(int argc, char** argv)
{
	engine::Settings settings;
	settings.windowTitle = GetFileNameWithoutExt(argv[0]);
	settings.nextScreenId = 1;
	engine::Application app(settings);
	app.AddScreen(new game::LogoScreen);
	game::MainMenuScreen* mainMenuScreen = new game::MainMenuScreen();
	app.AddScreen(mainMenuScreen);
	mainMenuScreen->newGameScreen = app.AddScreen(new game::Overworld)->screenId;
	mainMenuScreen->continueGameScreen = app.AddScreen(new game::BattleScreen)->screenId;
	//app.Init();
	app.Run();

	return 0;
}