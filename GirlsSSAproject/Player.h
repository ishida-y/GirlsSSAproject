#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>

class FallZone {
	int id;
	RectF zone;
	Vec2 retry;
};

class Player {
public:
	ham::PhysicsBody player1;
	RectF player2;
	int hp;
	double ease9;
	double ease6;

	Player(const ham::PhysicsWorld& world);
	void update();
	void move();
	//void fall();
	void draw() const;
};