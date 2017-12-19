#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>
#include "Action.h"

class Game : public SceneManager<String>::Scene
{
public:
	Action actoin;

	void init() override;

	void update() override;

	void draw() const override;
};
