#include "Player.h"
#include "System.h"

Player::Player(const ham::PhysicsWorld& world) :
	player1(world.createRect({ 100.0 / 100.0, 200.0 / 100.0 }, RectF(48.0 / 100.0, 96.0 / 100.0), PhysicsMaterial(1.0, 0.01, 0.0), none, PhysicsBodyType::Dynamic)) ,
	player2(RectF(player1.getPos(), 48.0 / 100.0, 96.0 / 100.0)),
	hp(100),
	ease9(0.9),
	ease6(0.6){
	player1.setGravityScale(2.0);
	player1.setFixedRotation(true);
}

void Player::update() {
	move();
}

void Player::move() {

	player1.setVelocity(Vec2(4.0 * GameSystem::get().input.stick.L.x, player1.getVelocity().y));

	static double yspeed = 0;
	if (player1.getVelocity().y == 0 && yspeed >= 0 && GameSystem::get().input.buttonB.clicked) {
		player1.applyForce(Vec2(0.0, -300.0));
	}
	yspeed = player1.getVelocity().y;

	player2.y = ease6 * player2.y + (1 - ease6) * player1.getPos().y;
	if (player2.pos.distanceFrom(player1.getPos()) >= 0.5) {
		player2.x = ease9 * player2.x + (1 - ease9) * player1.getPos().x;
	}
}

void Player::draw() const {
	player2.draw(Color(0, 0, 255, 64));
	player1.draw(Palette::Red);
}