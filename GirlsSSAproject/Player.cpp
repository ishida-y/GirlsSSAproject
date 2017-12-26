#include "Player.h"
#include "System.h"
#include "Enemy.h"



FallZone::FallZone(int _id, RectF _zone, Vec2 _retry) :
	id(_id),
	zone(_zone),
	retry(_retry) {

}

const Vec2 Player::BLOCK_SIZE = Vec2(64.0 / 100.0, 64.0 / 100.0);
//const Vec2 Player::PLAYER_SIZE = Vec2(32.0 / 100.0, 96.0 / 100.0);
const Vec2 Player::PLAYER_SIZE = Vec2(64.0 / 100.0, 128.0 / 100.0);


Player::Player(const ham::PhysicsWorld& world) :
	player(world.createRect(Vec2(0, 0), RectF(PLAYER_SIZE), PhysicsMaterial(1.0, 0.01, 0.0), none, PhysicsBodyType::Dynamic)),
	player1(RectF(player.getPos(), PLAYER_SIZE)),
	player2(RectF(player.getPos(), PLAYER_SIZE)),
	hp(100),
	ease9(0.9),
	ease6(0.6),
	fall_c(0),
	atc_range(RectF(0, 0, 0, 0)),
	atc_c(0),
	dir(1),
	c_hit(0),
	foot(RectF(player.getPos() + Vec2(-0.01, 0.0), PLAYER_SIZE + Vec2(0.02, BLOCK_SIZE.y))) {
	player.setGravityScale(2.0);
	player.setFixedRotation(true);

	CSVReader csv(L"Data/map.csv");
	for (int i = 0; i < csv.rows; i++) {
		int x = -1;
		int j = 0;
		for (; j < csv.columns(i); j++) {
			if ((int)csv.get<int>(i, j) == 1) {
				player.setPos(Vec2(BLOCK_SIZE.x*(double)j, BLOCK_SIZE.y*(double)i));
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
							zone = RectF(Vec2(BLOCK_SIZE.x*(double)x, BLOCK_SIZE.y*(double)k), BLOCK_SIZE.x*(l - x), BLOCK_SIZE.y);
							x = -1;
						}
					}
					if (x != -1) {
						zone = RectF(Vec2(BLOCK_SIZE.x*(double)x, BLOCK_SIZE.y*(double)k), BLOCK_SIZE.x*(l - x), BLOCK_SIZE.y);
					}
				}


				fall_zone.emplace_back((int)csv.get<int>(i, j), zone, Vec2(BLOCK_SIZE.x*(double)j, BLOCK_SIZE.y*(double)i));
			}

		}
	}


}

void Player::update(const EnemyManager& enemymanager) {
	move();
	attack();
	check_hit(enemymanager);
	fall();
}

void Player::move() {
	static double yspeed = 0;
	if (c_hit == 0) {
		player.setVelocity(Vec2(4.0 * GameSystem::get().input.stick.L.x, player.getVelocity().y));

		if (player.getVelocity().y == 0 && yspeed >= 0 && GameSystem::get().input.buttonB.clicked) {
			player.applyForce(Vec2(0.0, -600.0));
		}
		yspeed = player.getVelocity().y;


		if (player.getVelocity().x > 0 && dir == -1) {
			dir = 1;
		}
		if (player.getVelocity().x < 0 && dir == 1) {
			dir = -1;
		}
	}
	player1.pos = player.getPos();
	player2.y = ease6 * player2.y + (1 - ease6) * player.getPos().y;
	if (player2.pos.distanceFrom(player.getPos()) >= 0.5) {
		player2.x = ease9 * player2.x + (1 - ease9) * player.getPos().x;
	}
	foot.pos = player.getPos() + Vec2(-0.01, 0.0);
}

void Player::attack() {
	if (atc_c == 0 && GameSystem::get().input.buttonX.clicked && c_hit == 0) {
		atc_c = 10;
	}
	if (atc_c == 5) {
		if (dir == 1) {
			atc_range = RectF(player.getPos() + Vec2(PLAYER_SIZE.x, 0.0), 64.0 / 100.0, PLAYER_SIZE.y);
		}
		else if (dir == -1) {
			atc_range = RectF(player.getPos() + Vec2(-64.0 / 100.0, 0.0), 64.0 / 100.0, PLAYER_SIZE.y);
		}

		SoundAsset(L"sword").playMulti();

	}
	if (atc_c == 4) {
		atc_range = RectF(0, 0, 0, 0);
	}
	if (atc_c > 0) {
		atc_c--;
	}
}

void Player::check_hit(const EnemyManager& enemymanager) {
	if (c_hit > 0) {
		c_hit--;
	}
	for (int i = 0; i < enemymanager.enemies.size(); i++) {
		if (enemymanager.enemies[i]->atc_range.intersects(player1)) {
			hp -= 20;
			player.setVelocity(Vec2(0, 0));
			if (player1.pos.x > enemymanager.enemies[i]->range.pos.x) {
				player.applyForce(Vec2(150, -100));
			}
			else {
				player.applyForce(Vec2(-150, -100));
			}
			c_hit = 30;
		}
		/////////////////
		if (enemymanager.enemies[i]->range.intersects(foot) && c_hit == 0) {
			if (player1.pos.x + player1.w / 2 > enemymanager.enemies[i]->range.pos.x + enemymanager.enemies[i]->range.w / 2
				&& player1.pos.y + player1.h < enemymanager.enemies[i]->range.pos.y) {
				player.setVelocity(Vec2(4.1, player.getVelocity().y));
			}
			else if (player1.pos.y + player1.h < enemymanager.enemies[i]->range.pos.y) {
				player.setVelocity(Vec2(-4.1, player.getVelocity().y));
			}
		}
	}

}


void Player::fall() {
	static Vec2 tmp;
	for (int i = 0; i < fall_zone.size(); i++) {
		if (player1.intersects(fall_zone[i].zone)) {
			player.setPos(fall_zone[i].retry);
			tmp = fall_zone[i].retry;
			player.setVelocity(Vec2(0, 0));
			player1.pos = player.getPos();
			player2.pos = player.getPos();
			hp -= 20;
			fall_c = 30;
		}
	}
	if (fall_c > 0) {
		fall_c--;
		player.setPos(tmp);
		player.setVelocity(Vec2(0, 0));
		player1.pos = player.getPos();
		player2.pos = player.getPos();
	}
}

void Player::draw() const {
	static int c_8 = 0;
	c_8++;
	if (c_8 == 32) c_8 = 0;

	foot.draw();
	player2.draw(Color(0, 0, 255, 64));
	player1.draw(Palette::Red);
	if (c_hit != 0) player1.draw(Palette::Orange);

	if ((int)c_8 / 8 == 0) {
		if (dir == 1) {
			TextureAsset(L"ragu_1").mirror().scale(1.0 / 4.0 / 100.0).draw(player1.pos + Vec2(-68, -34) / 100.0);
		}
		else if (dir == -1) {
			TextureAsset(L"ragu_1").scale(1.0 / 4.0 / 100.0).draw(player1.pos + Vec2(-48, -34) / 100.0);
		}
	}
	else if ((int)c_8 / 8 == 1) {
		if (dir == 1) {
			TextureAsset(L"ragu_2").mirror().scale(1.0 / 4.0 / 100.0).draw(player1.pos + Vec2(-68, -34) / 100.0);
		}
		else if (dir == -1) {
			TextureAsset(L"ragu_2").scale(1.0 / 4.0 / 100.0).draw(player1.pos + Vec2(-48, -34) / 100.0);
		}
	}
	else if ((int)c_8 / 8 == 2) {
		if (dir == 1) {
			TextureAsset(L"ragu_3").mirror().scale(1.0 / 4.0 / 100.0).draw(player1.pos + Vec2(-68, -34) / 100.0);
		}
		else if (dir == -1) {
			TextureAsset(L"ragu_3").scale(1.0 / 4.0 / 100.0).draw(player1.pos + Vec2(-48, -34) / 100.0);
		}
	}
	else {
		if (dir == 1) {
			TextureAsset(L"ragu_4").mirror().scale(1.0 / 4.0 / 100.0).draw(player1.pos + Vec2(-68, -34) / 100.0);
		}
		else if (dir == -1) {
			TextureAsset(L"ragu_4").scale(1.0 / 4.0 / 100.0).draw(player1.pos + Vec2(-48, -34) / 100.0);
		}
	}


	if (GameSystem::get().debug) {
		atc_range.draw();
		Print(L"hp:");
		Println(hp);
	}
}