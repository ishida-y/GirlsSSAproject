#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>

class FallZone {
public:
	int id;
	RectF zone;
	Vec2 retry;
	FallZone(int _id, RectF _zone,Vec2 _retry);
};

class Player {
public:
	ham::PhysicsBody player;
	RectF player1;
	RectF player2;
	int hp;
	double ease9;
	double ease6;

	std::vector<FallZone> fall_zone;

	Player(const ham::PhysicsWorld& world);
	void update();
	void move();
	void fall();
	void draw() const;
};