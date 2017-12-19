#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>

class Player {
public:
	ham::PhysicsBody player;

	Player(const ham::PhysicsWorld& world);
	void update();
	void move();
	void draw() const;
};