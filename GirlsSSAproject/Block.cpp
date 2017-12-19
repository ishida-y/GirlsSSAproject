#include "Block.h"

BlockManager::BlockManager(const ham::PhysicsWorld& world) {
	block = world.createRect(Vec2(0.0, 0.0), RectF(0, 0), PhysicsMaterial(1.0, 0.01, 0.0), none, PhysicsBodyType::Static);
	CSVReader csv(L"map.csv");
	for (int i = 0; i < csv.rows; i++) {
		int x = -1;
		int j = 0;
		for (i; j < csv.columns(i); j++) {
			if (csv.get<int>(i, j) == 1 && x == -1) {
				x = j;
			}
			if (csv.get<int>(i, j) != 1 && x != -1) {
				block.addRect(RectF(Vec2(64.0*(double)x / 100.0, 64.0*(double)i / 100.0), 64.0*(j - x) / 100.0, 64.0 / 100.0));
				x = -1;
			}

			if (csv.get<int>(i, j) == 1) {
			}
		}
		if (x != -1) {
			block.addRect(RectF(Vec2(64.0*(double)x / 100.0, 64.0*(double)i / 100.0), 64.0*(j - x + 1) / 100.0, 64.0 / 100.0));
		}
	}
}

void BlockManager::draw() const{
	block.draw();
}