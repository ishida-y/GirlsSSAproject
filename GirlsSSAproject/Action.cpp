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

	TextureAsset::Register(L"ragu_1", L"Data/ragu_1.png");
	TextureAsset::Register(L"ragu_2", L"Data/ragu_2.png");
	TextureAsset::Register(L"ragu_3", L"Data/ragu_3.png");
	TextureAsset::Register(L"ragu_4", L"Data/ragu_4.png");
	TextureAsset::Register(L"dog_1", L"Data/dog_1.png");
	TextureAsset::Register(L"dog_2", L"Data/dog_2.png");
	TextureAsset::Register(L"dog_3", L"Data/dog_3.png");
	TextureAsset::Register(L"oak_1", L"Data/oak_1.png");
	TextureAsset::Register(L"oak_2", L"Data/oak_2.png");
	TextureAsset::Register(L"oak_3", L"Data/oak_3.png");
	SoundAsset::Register(L"bgm", L"Data/bgm.mp3");
	SoundAsset::Register(L"dog", L"Data/dog.mp3");
	SoundAsset::Register(L"hit", L"Data/hit.mp3");
	SoundAsset::Register(L"oak", L"Data/oak.mp3");
	SoundAsset::Register(L"sword", L"Data/sword.mp3");
	TextureAsset::PreloadAll;
	SoundAsset::PreloadAll;
	SoundAsset(L"bgm").setLoop(true);
}


void Action::update(String &part) {
	/*
	if (GameSystem::get().input.buttonA.clicked) {
		part = L"novel"; //Aボタン押したらクリア
		return;
	}*/

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
