#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>

class EnemyManager;
class Enemy;
class Dog;
class Orc;

class FallZone {
public:
	int id;
	RectF zone;
	Vec2 retry;
	FallZone(int _id, RectF _zone, Vec2 _retry);
};



class Player {
public:
	ham::PhysicsBody player;
	RectF player1;
	RectF player2;
	int hp;
	int fall_c;
	double ease9;
	double ease6;
	RectF atc_range;
	int atc_c;
	int dir;
	int c_hit;
	RectF foot;
	Vec2 clear;

	const static Vec2 BLOCK_SIZE;
	const static Vec2 PLAYER_SIZE;

	std::vector<FallZone> fall_zone;

	Player(const ham::PhysicsWorld& world);
	void update(const EnemyManager& enemymanager);
	void move();
	void fall();
	void attack();
	void check_hit(const EnemyManager& enemymanager);
	void draw() const;
};

