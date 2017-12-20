#pragma once
# include <Siv3D.hpp>

class Button {
public:
	bool clicked;
	bool pressed;
	int32  pressedDuration;
	bool released;

	Button();
	void update(s3d::Key Xcon, s3d::Key pad, s3d::Key key);
};

class Stick {
public:
	Vec2 R;
	Vec2 L;
	Stick();
	void update(s3d::Key Rup, s3d::Key Rdown, s3d::Key Rright, s3d::Key Rleft, s3d::Key Lup, s3d::Key Ldown, s3d::Key Lright, s3d::Key Lleft);
};

class KeyInput {
public:
	Button buttonStart;
	Button buttonBack;
	Button buttonUp;
	Button buttonDown;
	Button buttonRight;
	Button buttonLeft;
	Button buttonA;
	Button buttonB;
	Button buttonX;
	Button buttonY;
	Button buttonR;
	Button buttonL;
	Button buttonRS;
	Button buttonLS;
	double triggerR;
	double triggerL;
	Stick stick;

	KeyInput();
	void update();
};

class GameSystem {
public:
	static GameSystem& get() {
		static GameSystem inst;
		return inst;
	}
	void update();
	//void draw() const;

	KeyInput input;
	int sound_vol;


private:
	GameSystem();
	GameSystem(const GameSystem& r) {}
	GameSystem& operator=(const GameSystem& r) {}
	//void key_config();
	//void set_sound_vol();
};