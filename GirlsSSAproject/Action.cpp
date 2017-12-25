#include "Action.h"
#include "System.h"

Action::Action() :
ease(0.8),
camera(Window::Center()),
t_camera(Window::Center()),
camera_size(1),
t_camera_size(1),
player(world),
blockmanager(world){
	world.setGravity(Vec2(0.0, 9.8));
	camera = Window::Center() - player.player.getPos();
	t_camera = Window::Center() - player.player.getPos();
}

void Action::update(String &part) {

	if (GameSystem::get().input.buttonA.clicked) {
		part = L"novel"; //Aボタン押したらクリア
		return;
	}

	player.update();

	world.update(1.0 / 60.0);

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
		blockmanager.draw();
	}
}
