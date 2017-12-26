#include "System.h"

Button::Button() :
	clicked(false),
	pressed(false),
	pressedDuration(0),
	released(false) {

}

void Button::update(s3d::Key Xcon, s3d::Key pad, s3d::Key key) {

	if (XInput(0).isConnected()) {
		clicked = Xcon.clicked;
		pressed = Xcon.pressed;
		pressedDuration = Xcon.pressedDuration;
		released = Xcon.released;
	}
	else if (Gamepad(0).isConnected()) {
		clicked = pad.clicked;
		pressed = pad.pressed;
		pressedDuration = pad.pressedDuration;
		released = pad.released;
	}
	else {
		clicked = key.clicked;
		pressed = key.pressed;
		pressedDuration = key.pressedDuration;
		released = key.released;
	}

}


Stick::Stick() :
	R(Vec2(0, 0)),
	L(Vec2(0, 0)) {
		XInput(0).setRightThumbDeadZone();
		XInput(0).setLeftThumbDeadZone();
}

void Stick::update(s3d::Key Rup, s3d::Key Rdown, s3d::Key Rright, s3d::Key Rleft,
	s3d::Key Lup, s3d::Key Ldown, s3d::Key Lright, s3d::Key Lleft) {

	if (XInput(0).isConnected()) {
		R.x = XInput(0).rightThumbX;
		R.y = XInput(0).rightThumbY;
		L.x = XInput(0).leftThumbX;
		L.y = XInput(0).leftThumbY;
	}
	else if (Gamepad(0).isConnected()) {
		R.x = Gamepad(0).z;
		R.y = Gamepad(0).r;
		L.x = Gamepad(0).x;
		L.y = Gamepad(0).y;
	}
	else {
		R = Vec2(0, 0);
		if (Rup.pressed) {
			R.y += 1;
		}
		if (Rdown.pressed) {
			R.y += -1;
		}
		if (Rright.pressed) {
			R.x += 1;
		}
		if (Rleft.pressed) {
			R.x += -1;
		}
		L = Vec2(0, 0);
		if (Lup.pressed) {
			L.y += 1;
		}
		if (Ldown.pressed) {
			L.y += -1;
		}
		if (Lright.pressed) {
			L.x += 1;
		}
		if (Lleft.pressed) {
			L.x += -1;
		}
	}
}


KeyInput::KeyInput() :
	triggerR(0),
	triggerL(0) {
	XInput(0).setRightTriggerDeadZone();
	XInput(0).setLeftTriggerDeadZone();
}

void KeyInput::update() {
	buttonStart.update(XInput(0).buttonStart, Gamepad(0).button(9), Input::KeyEscape);
	buttonBack.update(XInput(0).buttonBack, Gamepad(0).button(8), Input::KeyBackspace);
	buttonUp.update(XInput(0).buttonUp, Gamepad(0).povForward, Input::KeyUp);
	buttonDown.update(XInput(0).buttonDown, Gamepad(0).povBackward, Input::KeyDown);
	buttonRight.update(XInput(0).buttonRight, Gamepad(0).povRight, Input::KeyRight);
	buttonLeft.update(XInput(0).buttonLeft, Gamepad(0).povLeft, Input::KeyLeft);
	buttonA.update(XInput(0).buttonA, Gamepad(0).button(2), Input::KeySlash);
	buttonB.update(XInput(0).buttonB, Gamepad(0).button(1), Input::KeyBackslash);
	buttonX.update(XInput(0).buttonX, Gamepad(0).button(0), Input::KeySemicolon);
	buttonY.update(XInput(0).buttonY, Gamepad(0).button(3), Input::KeyColon);
	buttonR.update(XInput(0).buttonRB, Gamepad(0).button(5), Input::KeyRShift);
	buttonL.update(XInput(0).buttonLB, Gamepad(0).button(4), Input::KeyLShift);
	buttonRS.update(XInput(0).buttonRThumb, Gamepad(0).button(11), Input::KeyRControl);
	buttonLS.update(XInput(0).buttonLThumb, Gamepad(0).button(10), Input::KeyLControl);
	if (XInput(0).isConnected()) {
		triggerR = XInput(0).rightTrigger;
		triggerL = XInput(0).leftTrigger;
	}
	else if (Gamepad(0).isConnected()) {
		triggerR = Gamepad(0).u;
		triggerL = Gamepad(0).v;
	}
	else {
		if (Input::KeyLBracket.pressed) {
			triggerR = 1;
		}
		else {
			triggerR = 0;
		}
		if (Input::KeyQ.pressed) {
			triggerL = 1;
		}
		else {
			triggerL = 0;
		}
	}
	stick.update(Input::KeyUp, Input::KeyDown, Input::KeyRight, Input::KeyLeft,
		Input::KeyW, Input::KeyS, Input::KeyD, Input::KeyA);
}


GameSystem::GameSystem() :
	sound_vol(1000),
	debug(false){

}

void GameSystem::update() {
	input.update();
}