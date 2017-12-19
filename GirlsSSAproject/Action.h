#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>
#include "Player.h"
#include "Block.h"

class Action {
public:
	ham::PhysicsWorld world;
	double ease;
	Vec2 camera, t_camera;

	Player player;
	BlockManager blockmanager;

	Action();
	void update();
	void draw() const;
private:
};