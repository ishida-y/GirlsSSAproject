#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>
#include "Action.h"
#include "Novel.h"

class Game : public SceneManager<String>::Scene
{
public:
	String part;

	Action actoin;
	Novel novel;

	void init() override;
	void update() override;
	void draw() const override;
};
