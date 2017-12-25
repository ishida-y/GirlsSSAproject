#include "Action.h"
#include "System.h"

Action::Action() :
ease(0.8),
camera(Window::Center()),
t_camera(Window::Center()),
camera_size(1),
t_camera_size(1),
player(world),
enemymanager(world),
blockmanager(world){
	world.setGravity(Vec2(0.0, 9.8));
	camera = Window::Center() - player.player.getPos();
	t_camera = Window::Center() - player.player.getPos();

	TextureAsset::Register(L"dog_1", L"Data/dog_1.png");
	TextureAsset::Register(L"dog_2", L"Data/dog_2.png");
	TextureAsset::Register(L"dog_3", L"Data/dog_3.png");
	TextureAsset::Register(L"oak_1", L"Data/oak_1.png");
	TextureAsset::Register(L"oak_2", L"Data/oak_2.png");
	TextureAsset::Register(L"oak_3", L"Data/oak_3.png");
	TextureAsset::PreloadAll;
}

<<<<<<< HEAD
void Action::update() {
=======
void Action::update(String &part) {

	if (GameSystem::get().input.buttonA.clicked) {
		part = L"novel"; //Aボタン押したらクリア
		return;
	}

	player.update();

>>>>>>> 6b238e83c793737db2c1bc90a400ebebac2ebade
	world.update(1.0 / 60.0);

	enemymanager.update(player);
	player.update(enemymanager);

	t_camera = Window::Center() - player.player.getPos();
	camera = ease * camera + (1 - ease) * t_camera;
	if (GameSystem::get().input.buttonUp.clicked && t_camera_size < 1.3) {
		t_camera_size += 0.2;
	}
	if (GameSystem::get().input.buttonDown.clicked && t_camera_size > 0.7) {
		t_camera_size -= 0.2;
	}
	camera_size = ease * camera_size + (1 - ease) * t_camera_size;
}

void Action::draw() const {
	{
		const Transformer2D transformer(Mat3x2::Translate(camera).scale(100 * camera_size, { 640, 360 }), true);
		player.draw();
		enemymanager.draw();
		blockmanager.draw();
	}
}
