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
	double camera_size, t_camera_size;

	Player player;
	BlockManager blockmanager;

	Action();
	void update(String &part);
	void draw() const;
private:
};