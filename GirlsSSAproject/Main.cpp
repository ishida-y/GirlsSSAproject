# include <Siv3D.hpp>
# include <HamFramework.hpp>
# include "Title.h"
# include "Select.h"
# include "Game.h"


void Main()
{
	SceneManager<String> manager;

	manager.add<Title>(L"Title");
	manager.add<Select>(L"Result");
	manager.add<Game>(L"Game");

	while (System::Update())
	{
		manager.updateAndDraw;
	}
}