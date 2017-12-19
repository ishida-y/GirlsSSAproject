#pragma once
#include <Siv3D.hpp>
#include<HamFramework.hpp>

class BlockManager {
public:
	ham::PhysicsBody block;

	BlockManager(const ham::PhysicsWorld& world);
	void draw() const;
};