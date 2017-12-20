#include "Block.h"

BlockManager::BlockManager(const ham::PhysicsWorld& world) {
	normal_block = world.createRect(Vec2(0.0, 0.0), RectF(0, 0), PhysicsMaterial(1.0, 0.01, 0.0), none, PhysicsBodyType::Static);
	CSVReader csv(L"map.csv");
	for (int i = 0; i < csv.rows; i++) {
		int x = -1;
		int j = 0;
		for (; j < csv.columns(i); j++) {
			if ((int)csv.get<int>(i, j)  / 10 == 1 && x == -1) {
				x = j;
			}
			if ((int)csv.get<int>(i, j)  / 10 != 1 && x != -1) {
				normal_block.addRect(RectF(Vec2(64.0*(double)x / 100.0, 64.0*(double)i / 100.0), 64.0*(j - x) / 100.0, 64.0 / 100.0));
				x = -1;
			}

			if ((int)csv.get<int>(i, j) / 10 == 1) {
				ground.emplace_back((int)csv.get<int>(i, j),RectF(Vec2(64.0*(double)j / 100.0, 64.0*(double)i / 100.0), 64.0 / 100.0, 64.0 / 100.0));
			}
		}
		if (x != -1) {
			normal_block.addRect(RectF(Vec2(64.0*(double)x / 100.0, 64.0*(double)i / 100.0), 64.0*(j - x) / 100.0, 64.0 / 100.0));
		}
	}
}

void BlockManager::draw() const{
	normal_block.draw();
	
	for (int i = 0; i < ground.size(); i++) {
		ground[i].draw();
	}
}

Ground::Ground(int _id, RectF _obj) :
id(_id),
obj(_obj){

}

Ground::Ground() {

}

void Ground::draw() const {
	if (id == 10) {
		obj.drawFrame(0.01, 0.0 , Palette::Green);
	}
	else if (id == 11) {
		obj.drawFrame(0.01, 0.0, Palette::Greenyellow);
	}
	else if (id == 12) {
		obj.drawFrame(0.01, 0.0, Palette::Lightgreen);
	}
}