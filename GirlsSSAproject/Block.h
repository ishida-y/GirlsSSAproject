#pragma once
#include <Siv3D.hpp>
#include<HamFramework.hpp>

class Ground {
public:
	RectF obj;
	int id;

	Ground(int _id, RectF _obj);
	Ground();
	void draw() const;
};

class BlockManager {
public:
	ham::PhysicsBody normal_block;
	std::vector<Ground> ground;

	BlockManager(const ham::PhysicsWorld& world);
	void draw() const;
};