#include "Player.h"
#include "System.h"

Player::Player(const ham::PhysicsWorld& world) :
	player(world.createRect({ 100.0 / 100.0, 200.0 / 100.0 }, RectF(48.0 / 100.0, 96.0 / 100.0), PhysicsMaterial(1.0, 0.01, 0.0), none, PhysicsBodyType::Dynamic)) {
	player.setGravityScale(2.0);
	player.setFixedRotation(true);
}

void Player::update() {
	move();
}

void Player::move() {

	static double yspeed = 0;

	player.setVelocity(Vec2(4.0 * GameSystem::get().input.stick.L.x, player.getVelocity().y));
	/*
	if (Input::KeyRight.pressed) {
		player.setVelocity(player.getVelocity() + Vec2(4.0, 0.0));
	}
	if (Input::KeyLeft.pressed) {
		player.setVelocity(player.getVelocity() + Vec2(-4.0, 0.0));
	}
*/
	if (player.getVelocity().y == 0 && yspeed >= 0 && GameSystem::get().input.buttonB.clicked) {
		player.applyForce(Vec2(0.0, -300.0));
	}
	yspeed = player.getVelocity().y;
}

void Player::draw() const{
	player.draw(Palette::Red);
}