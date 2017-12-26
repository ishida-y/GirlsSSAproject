#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>
#include<vector>

class Player;

class Enemy {
public:
	ham::PhysicsBody obj;
	RectF range;
	int hp;
	RectF atc_range;
	int atc_c;
	int dir;
	bool isDead;
	bool disPlayer;
	bool hit;
	int c_move;
	int c_hit;
	int atc_damage;
	int hit_damage;


	Enemy();
	void update(const Player& player);
	virtual void move(const Player& player) = 0;
	void check_dir();
	virtual void attack(const Player& player) = 0;
	virtual void check_hit(const Player& player) = 0;
	void check_dead();
	virtual void draw() const = 0;
	virtual ~Enemy() = default;
};

class Dog : public Enemy {
public:

	const static Vec2 DOG_SIZE;

	Dog(const ham::PhysicsWorld& world, Vec2 _pos);

	void move(const Player& player) override;
	void attack(const Player& player) override;
	void check_hit(const Player& player) override;
	void draw() const override;
};

class Orc : public Enemy {
public:

	const static Vec2 ORC_SIZE;

	Orc(const ham::PhysicsWorld& world, Vec2 _pos);

	void move(const Player& player) override;
	void attack(const Player& player) override;
	void check_hit(const Player& player) override;
	void draw() const override;
};

class EnemyManager {
public:
	std::vector<std::shared_ptr<Enemy>> enemies;

	EnemyManager(const ham::PhysicsWorld& world);

	void update(const Player& player);
	void dead();
	void draw() const;
};