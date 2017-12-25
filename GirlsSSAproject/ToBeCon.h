#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>

class ToBeCon : public SceneManager<String>::Scene
{
public:
	Font font;

	void init() override;
	void update() override;
	void draw() const override;
};