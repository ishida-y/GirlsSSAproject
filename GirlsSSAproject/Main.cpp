# include <Siv3D.hpp>
# include <HamFramework.hpp>

class Title : public SceneManager<String>::Scene
{
public:
	void init() override
	{

	}

	void update() override
	{

	}

	void draw() const override
	{

	}
};

class Select : public SceneManager<String>::Scene
{
public:
	void init() override
	{

	}

	void update() override
	{

	}

	void draw() const override
	{

	}
};

class Game : public SceneManager<String>::Scene
{
public:
	void init() override
	{

	}

	void update() override
	{

	}

	void draw() const override
	{

	}
};

void Main()
{
	SceneManager<String> manager;

	manager.add<Title>(L"Title");
	manager.add<Select>(L"Result");
	manager.add<Game>(L"Game");

	while (System::Update())
	{

	}
}