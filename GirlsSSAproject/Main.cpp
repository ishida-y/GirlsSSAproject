# include <Siv3D.hpp>
# include <HamFramework.hpp>
# include "Title.h"
# include "Select.h"
# include "Game.h"
# include "System.h"


void Main()
{
	SceneManager<String> manager;

	manager.add<Title>(L"Title");
	manager.add<Select>(L"Select");
	manager.add<Game>(L"Game");

	while (System::Update())
	{
		ClearPrint();
		GameSystem::get().update();
		manager.updateAndDraw();
	}
}