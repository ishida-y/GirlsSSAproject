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
	c_move(Random(0, 100)),
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

const Vec2 Okami::OKAMI_SIZE = Vec2(128.0 / 100.0, 64.0 / 100.0);

Okami::Okami(const ham::PhysicsWorld& world, Vec2 _pos) {
	obj = world.createRect(_pos, RectF(OKAMI_SIZE), PhysicsMaterial(1.0, 0.01, 0.0), none, PhysicsBodyType::Dynamic);
	obj.setFixedRotation(true);
	range = RectF(obj.getPos(), OKAMI_SIZE);
}

void Okami::move(const Player& player) {
	if (c_hit == 0) {
		//‰“‚¢‚Æ‚«”½•œ
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
		//’´‹ß‚¢‚Æ‚«’âŽ~
		else if (fabs(player.player1.pos.x - range.pos.x) < 42.0 / 100.0 && dir == -1) {
			obj.setVelocity(Vec2(0, obj.getVelocity().y));
		}
		else if (fabs(player.player1.pos.x - range.pos.x) < (10.0 / 100.0 + OKAMI_SIZE.x) && dir == 1) {
			obj.setVelocity(Vec2(0, obj.getVelocity().y));
		}
		//‹ß‚¢‚Æ‚«’Ç‚¢‚©‚¯‚é
		else {
			if (player.player1.pos.x - range.pos.x < 0 && Random(1,20) == 1) {
				dir = -1;
			}
			else if(player.player1.pos.x - range.pos.x > 0 && Random(1, 20) == 1) {
				dir = 1;
			}
			obj.setVelocity(Vec2(3.0 * dir, obj.getVelocity().y));
		}
	}

	range.pos = obj.getPos();
}

void Okami::attack(const Player& player) {
	if (atc_c == 0 && Random(1, 60) == 1 && fabs(player.player1.pos.x - range.pos.x) < 100.0 / 100.0) {
		atc_c = 10;
	}
	if (atc_c == 5) {
		if (dir == 1) {
			atc_range = RectF(obj.getPos() + Vec2(OKAMI_SIZE.x, 0.0), 64.0 / 100.0, OKAMI_SIZE.y);
		}
		else if (dir == -1) {
			atc_range = RectF(obj.getPos() + Vec2(-64.0 / 100.0, 0.0), 64.0 / 100.0, OKAMI_SIZE.y);
		}
	}
	if (atc_c == 4) {
		atc_range = RectF(0, 0, 0, 0);
	}
	if (atc_c > 0) {
		atc_c--;
		if (atc_c == 0 && Random(1,2) ==1) {
			dir*=-1;
		}
	}
}

void Okami::check_hit(const Player& player) {
	if (c_hit > 0) {
		c_hit--;
	}
	if (player.atc_range.intersects(range)) {
		hp -= 20;
		obj.setVelocity(Vec2(0, obj.getVelocity().y)); //?
		obj.applyForce(Vec2(dir*(-1) * 200, -100));
		c_hit = 20;
	}
}

void Okami::draw() const {
	range.draw(Palette::Yellow);
	obj.draw(Palette::Yellow);
	atc_range.draw();
	Println(range.pos);
}

EnemyManager::EnemyManager(const ham::PhysicsWorld& world) {
	CSVReader csv(L"map.csv");
	for (int i = 0; i < csv.rows; i++) {
		for (int j = 0; j < csv.columns(i); j++) {
			if ((int)csv.get<int>(i, j) == 20) {
				enemies.emplace_back(std::make_shared<Okami>(world, Vec2(j * 0.64, i *0.64)));
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