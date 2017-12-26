#include"Enemy.h"
#include"Player.h"

Enemy::Enemy() :
	hp(100),
	atc_range(RectF(0, 0, 0, 0)),
	atc_c(0),
	dir(1),
	isDead(false),
	disPlayer(false),
	hit(false),
	c_move(0),
	c_hit(0) {

}

void Enemy::update(const Player& player) {
	//check_dir();
	move(player);
	attack(player);
	check_hit(player);
	check_dead();
}

void Enemy::check_dir() {
	if (c_hit == 0) {
		if (obj.getVelocity().x > 0 && dir == -1) {
			dir = 1;
		}
		if (obj.getVelocity().x < 0 && dir == 1) {
			dir = -1;
		}
	}
}

void Enemy::check_dead() {
	if (range.pos.y > 1000) {
		isDead = true;
	}
	if (hp <= 0) {
		isDead = true;
	}
}







const Vec2 Dog::DOG_SIZE = Vec2(128.0 / 100.0, 64.0 / 100.0);

Dog::Dog(const ham::PhysicsWorld& world, Vec2 _pos) {
	obj = world.createRect(_pos, RectF(DOG_SIZE), PhysicsMaterial(1.0, 0.01, 0.0), none, PhysicsBodyType::Dynamic);
	obj.setFixedRotation(true);
	range = RectF(obj.getPos(), DOG_SIZE);
	c_move = Random(0, 100);
}

void Dog::move(const Player& player) {
	if (c_hit == 0) {
		//‰“‚¢‚Æ‚«”½•œok
		if (fabs(player.player1.pos.x - range.pos.x) > 500.0 / 100.0) {
			if (c_move <= 0) {
				dir *= -1;
				c_move = 100;
			}
			else {
				c_move--;
			}
			obj.setVelocity(Vec2(3.0 * dir, obj.getVelocity().y));
		}
		//’´‹ß‚¢‚Æ‚«’âŽ~ok
		else if (fabs(player.player1.pos.x - range.pos.x) < (32.0 + 10.0) / 100.0 && dir == -1) {
			obj.setVelocity(Vec2(0, obj.getVelocity().y));
			if (player.player1.pos.x + player.player1.w / 2 > range.pos.x + range.w / 2) {
				dir = 1;
			}
		}
		else if (fabs(player.player1.pos.x - range.pos.x) < (10.0 / 100.0 + DOG_SIZE.x) && dir == 1) {
			obj.setVelocity(Vec2(0, obj.getVelocity().y));
			if (player.player1.pos.x + player.player1.w / 2 < range.pos.x + range.w / 2) {
				dir = -1;
			}
		}
		//‹ß‚¢‚Æ‚«’Ç‚¢‚©‚¯‚éok
		else {
			if (player.player1.pos.x - range.pos.x < 0 && Random(1, 20) == 1) {
				dir = -1;
			}
			else if (player.player1.pos.x - range.pos.x > 0 && Random(1, 20) == 1) {
				dir = 1;
			}
			obj.setVelocity(Vec2(3.0 * dir, obj.getVelocity().y));
		}
	}

	range.pos = obj.getPos();
}

void Dog::attack(const Player& player) {
	if (atc_c == 0 && Random(1, 60) == 1) {
		if (fabs(player.player1.pos.x - range.pos.x) < (150.0 + 32.0) / 100.0 && dir == -1) {
			atc_c = 60;
		}
		else if (fabs(player.player1.pos.x - range.pos.x) < (150.0 / 100.0 + DOG_SIZE.x) && dir == 1) {
			atc_c = 60;
		}
	}

	if (atc_c == 30) {
		if (dir == 1) {
			atc_range = RectF(obj.getPos() + Vec2(DOG_SIZE.x, 0.0), 64.0 / 100.0, DOG_SIZE.y);
		}
		else if (dir == -1) {
			atc_range = RectF(obj.getPos() + Vec2(-64.0 / 100.0, 0.0), 64.0 / 100.0, DOG_SIZE.y);
		}
		if (fabs(player.player1.pos.x - range.pos.x) < 600.0 / 100.0) {
			SoundAsset(L"dog").playMulti();
		}
	}
	if (atc_c == 29) {
		atc_range = RectF(0, 0, 0, 0);
	}
	if (atc_c > 0) {
		atc_c--;
		if (atc_c == 0) {
			dir *= -1;
		}
	}
}

void Dog::check_hit(const Player& player) {
	if (c_hit > 0) {
		c_hit--;
	}
	if (player.atc_range.intersects(range) && c_hit == 0) {
		//hp -= 20;

		SoundAsset(L"hit").playMulti();

		obj.setVelocity(Vec2(0, 0));
		if (range.pos.x > player.player1.pos.x) {
			obj.applyForce(Vec2(200, -100));
		}
		else {
			obj.applyForce(Vec2(-200, -100));
		}
		c_hit = 30;
	}
}

void Dog::draw() const {
	if (c_hit == 0) {
		range.draw(Palette::Yellow);
	}
	else {
		range.draw(Palette::Orange);
	}
	atc_range.draw();
	Println(range.pos);
	if (atc_c == 0) {
		if (dir == 1) {
			TextureAsset(L"dog_1").mirror().scale(1.0 / 6.0 / 100.0).draw(range.pos + Vec2(-38, -64) / 100.0);
		}
		else if (dir == -1) {
			TextureAsset(L"dog_1").scale(1.0 / 6.0 / 100.0).draw(range.pos + Vec2(-20, -64) / 100.0);
		}
	}
	else if (atc_c > 30) {
		if (dir == 1) {
			TextureAsset(L"dog_2").mirror().scale(1.0 / 6.0 / 100.0).draw(range.pos + Vec2(-38, -64) / 100.0);
		}
		else if (dir == -1) {
			TextureAsset(L"dog_2").scale(1.0 / 6.0 / 100.0).draw(range.pos + Vec2(-20, -64) / 100.0);
		}
	}
	else {
		if (dir == 1) {
			TextureAsset(L"dog_3").mirror().scale(1.0 / 6.0 / 100.0).draw(range.pos + Vec2(-38, -64) / 100.0);
		}
		else if (dir == -1) {
			TextureAsset(L"dog_3").scale(1.0 / 6.0 / 100.0).draw(range.pos + Vec2(-20, -64) / 100.0);
		}
	}
}






const Vec2 Orc::ORC_SIZE = Vec2(80.0 / 100.0, 180.0 / 100.0);

Orc::Orc(const ham::PhysicsWorld& world, Vec2 _pos) {
	obj = world.createRect(_pos, RectF(ORC_SIZE), PhysicsMaterial(1.0, 0.01, 0.0), none, PhysicsBodyType::Dynamic);
	obj.setFixedRotation(true);
	range = RectF(obj.getPos(), ORC_SIZE);
	c_move = Random(0, 80);
}

void Orc::move(const Player& player) {
	if (c_hit == 0) {
		//‰“‚¢‚Æ‚«”½•œok
		if (fabs(player.player1.pos.x - range.pos.x) > 400.0 / 100.0) {
			if (c_move <= 0) {
				dir *= -1;
				c_move = 80;
			}
			else {
				c_move--;
			}
			obj.setVelocity(Vec2(2.0 * dir, obj.getVelocity().y));
		}
		//’´‹ß‚¢‚Æ‚«’âŽ~ok
		else if (fabs(player.player1.pos.x - range.pos.x) < (10.0 + 32.0) / 100.0 && dir == -1) {
			obj.setVelocity(Vec2(0, obj.getVelocity().y));
			if (player.player1.pos.x + player.player1.w / 2 > range.pos.x + range.w / 2) {
				dir = 1;
			}
		}
		else if (fabs(player.player1.pos.x - range.pos.x) < (10.0 / 100.0 + ORC_SIZE.x) && dir == 1) {
			obj.setVelocity(Vec2(0, obj.getVelocity().y));
			if (player.player1.pos.x + player.player1.w / 2 < range.pos.x + range.w / 2) {
				dir = -1;
			}
		}
		//‹ß‚¢‚Æ‚«’Ç‚¢‚©‚¯‚éok
		else {
			if (player.player1.pos.x - range.pos.x < 0 && Random(1, 20) == 1) {
				dir = -1;
			}
			else if (player.player1.pos.x - range.pos.x > 0 && Random(1, 20) == 1) {
				dir = 1;
			}
			obj.setVelocity(Vec2(2.0 * dir, obj.getVelocity().y));
		}
	}

	range.pos = obj.getPos();
}

void Orc::attack(const Player& player) {
	if (atc_c == 0 && Random(1, 100) == 1) {
		if (fabs(player.player1.pos.x - range.pos.x) < (150.0 + 32.0) / 100.0 && dir == -1) {
			atc_c = 70;
		}
		else if (fabs(player.player1.pos.x - range.pos.x) < (150.0 / 100.0 + ORC_SIZE.x) && dir == 1) {
			atc_c = 70;
		}
	}

	if (atc_c == 30) {
		if (dir == 1) {
			atc_range = RectF(obj.getPos() + Vec2(ORC_SIZE.x, 0.0), 120.0 / 100.0, ORC_SIZE.y);
		}
		else if (dir == -1) {
			atc_range = RectF(obj.getPos() + Vec2(-120.0 / 100.0, 0.0), 120.0 / 100.0, ORC_SIZE.y);
		}
		if (fabs(player.player1.pos.x - range.pos.x) < 600.0 / 100.0) {
			SoundAsset(L"oak").playMulti();
		}
	}
	if (atc_c == 29) {
		atc_range = RectF(0, 0, 0, 0);
	}
	if (atc_c > 0) {
		atc_c--;
		if (atc_c == 0 && Random(1, 2) == 2) {
			dir *= -1;
		}
	}
}

void Orc::check_hit(const Player& player) {
	if (c_hit > 0) {
		c_hit--;
	}
	if (player.atc_range.intersects(range) && c_hit == 0) {
		//hp -= 20;

		SoundAsset(L"hit").playMulti();

		obj.setVelocity(Vec2(0, 0));
		if (range.pos.x > player.player1.pos.x) {
			obj.applyForce(Vec2(300, -100));
		}
		else {
			obj.applyForce(Vec2(-300, -100));
		}
		c_hit = 30;
	}
}

void Orc::draw() const {
	if (c_hit == 0) {
		range.draw(Palette::Yellow);
	}
	else {
		range.draw(Palette::Orange);
	}
	atc_range.draw();
	Println(range.pos);

	if (atc_c == 0) {
		if (dir == 1) {
			TextureAsset(L"oak_1").mirror().scale(1.0 / 3.0 / 100.0).draw(range.pos + Vec2(-68, -54) / 100.0);
		}
		else if (dir == -1) {
			TextureAsset(L"oak_1").scale(1.0 / 3.0 / 100.0).draw(range.pos + Vec2(-140, -54) / 100.0);
		}
	}
	else if (atc_c > 30) {
		if (dir == 1) {
			TextureAsset(L"oak_2").mirror().scale(1.0 / 3.0 / 100.0).draw(range.pos + Vec2(-68, -54) / 100.0);
		}
		else if (dir == -1) {
			TextureAsset(L"oak_2").scale(1.0 / 3.0 / 100.0).draw(range.pos + Vec2(-140, -54) / 100.0);
		}
	}
	else {
		if (dir == 1) {
			TextureAsset(L"oak_3").mirror().scale(1.0 / 3.0 / 100.0).draw(range.pos + Vec2(-68, -54) / 100.0);
		}
		else if (dir == -1) {
			TextureAsset(L"oak_3").scale(1.0 / 3.0 / 100.0).draw(range.pos + Vec2(-140, -54) / 100.0);
		}
	}
}

EnemyManager::EnemyManager(const ham::PhysicsWorld& world) {
	CSVReader csv(L"Data/map.csv");
	for (int i = 0; i < csv.rows; i++) {
		for (int j = 0; j < csv.columns(i); j++) {
			if ((int)csv.get<int>(i, j) == 20) {
				enemies.emplace_back(std::make_shared<Dog>(world, Vec2(j * 0.64, i *0.64)));
			}
			if ((int)csv.get<int>(i, j) == 21) {
				enemies.emplace_back(std::make_shared<Orc>(world, Vec2(j * 0.64, i *0.64)));
			}
		}
	}
}

void EnemyManager::update(const Player& player) {
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->update(player);
	}
	dead();
}

void EnemyManager::dead() {
	auto rmvIter = std::remove_if(enemies.begin(), enemies.end(), [](const std::shared_ptr<Enemy>& a) {
		return a->isDead;
	});
	enemies.erase(rmvIter, enemies.end());
}

void EnemyManager::draw() const {
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->draw();
	}
}