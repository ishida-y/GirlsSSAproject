#include "Player.h"
#include "System.h"

FallZone::FallZone(int _id, RectF _zone, Vec2 _retry) :
	id(_id),
	zone(_zone),
	retry(_retry) {

}

Player::Player(const ham::PhysicsWorld& world) :
	player(world.createRect({ 100.0 / 100.0, 200.0 / 100.0 }, RectF(48.0 / 100.0, 96.0 / 100.0), PhysicsMaterial(1.0, 0.01, 0.0), none, PhysicsBodyType::Dynamic)),
	player1(RectF(player.getPos(), 48.0 / 100.0, 96.0 / 100.0)),
	player2(RectF(player.getPos(), 48.0 / 100.0, 96.0 / 100.0)),
	hp(100),
	ease9(0.9),
	ease6(0.6) {
	player.setGravityScale(2.0);
	player.setFixedRotation(true);

	CSVReader csv(L"Data/map.csv");
	for (int i = 0; i < csv.rows; i++) {
		int x = -1;
		int j = 0;
		for (; j < csv.columns(i); j++) {
			if ((int)csv.get<int>(i, j) == 1) {
				player.setPos(Vec2(64.0*(double)j / 100.0, 64.0*(double)i / 100.0));
				player1.pos = player.getPos();
				player2.pos = player.getPos();
			}

			if ((int)csv.get<int>(i, j) / 10 == 3) {
				RectF zone;
				for (int k = 0; k < csv.rows; k++) {
					int x = -1;
					int l = 0;

					for (; l < csv.columns(k); l++) {
						if ((int)csv.get<int>(k, l) == -(int)csv.get<int>(i, j) && x == -1) {
							x = l;
						}
						if ((int)csv.get<int>(k, l) != -(int)csv.get<int>(i, j) && x != -1) {
							zone = RectF(Vec2(64.0*(double)x / 100.0, 64.0*(double)k / 100.0), 64.0*(l - x) / 100.0, 64.0 / 100.0);
							x = -1;
						}
					}
					if (x != -1) {
						zone = RectF(Vec2(64.0*(double)x / 100.0, 64.0*(double)k / 100.0), 64.0*(l - x) / 100.0, 64.0 / 100.0);
					}
				}


				fall_zone.emplace_back((int)csv.get<int>(i, j), zone, Vec2(64.0*(double)j / 100.0, 64.0*(double)i / 100.0));
			}

		}
	}


}

void Player::update() {
	move();
	fall();
}

void Player::move() {

	player.setVelocity(Vec2(4.0 * GameSystem::get().input.stick.L.x, player.getVelocity().y));

	static double yspeed = 0;
	if (player.getVelocity().y == 0 && yspeed >= 0 && GameSystem::get().input.buttonB.clicked) {
		player.applyForce(Vec2(0.0, -300.0));
	}
	yspeed = player.getVelocity().y;

	player1.pos = player.getPos();
	player2.y = ease6 * player2.y + (1 - ease6) * player.getPos().y;
	if (player2.pos.distanceFrom(player.getPos()) >= 0.5) {
		player2.x = ease9 * player2.x + (1 - ease9) * player.getPos().x;
	}
}

void Player::fall() {
	for (int i = 0; i < fall_zone.size(); i++) {
		if (player1.intersects(fall_zone[i].zone)) {
			player.setPos(fall_zone[i].retry);
			player.setVelocity(Vec2(0, 0));
			player1.pos = player.getPos();
			player2.pos = player.getPos();
		}
	}
}

void Player::draw() const {
	player2.draw(Color(0, 0, 255, 64));
	player.draw(Palette::Red);
	//player1.draw(Palette::Red);
}