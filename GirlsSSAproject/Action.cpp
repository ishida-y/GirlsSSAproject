# include "Action.h"

Action::Action() :
ease(0.9),
camera(Window::Center()),
t_camera(Window::Center()),
player(world),
blockmanager(world){
	world.setGravity(Vec2(0.0, 9.8));
}

void Action::update() {
	player.update();

	world.update(1.0 / 60.0);
	t_camera = Window::Center() - player.player.getPos();
	camera = ease * camera + (1 - ease) * t_camera;
}

void Action::draw() const {
	{
		const Transformer2D transformer(Mat3x2::Translate(camera).scale(100, { 640, 360 }), true);
		player.draw();
		blockmanager.draw();
	}
}
