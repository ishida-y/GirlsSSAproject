#include "System.h"

Button::Button() :
	clicked(false),
	pressed(false),
	pressedDuration(0),
	released(false) {

}

void Button::update(s3d::Key controller, s3d::Key keyboard) {

	if (XInput(0).isConnected()) {
		clicked = controller.clicked;
		pressed = controller.pressed;
		pressedDuration = controller.pressedDuration;
		released = controller.released;
	}

	else {
		clicked = keyboard.clicked;
		pressed = keyboard.pressed;
		pressedDuration = keyboard.pressedDuration;
		released = keyboard.released;
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
	buttonStart.update(XInput(0).buttonStart, Input::KeyEscape);
	buttonBack.update(XInput(0).buttonBack, Input::KeyBackspace);
	buttonUp.update(XInput(0).buttonUp, Input::KeyUp);
	buttonDown.update(XInput(0).buttonDown, Input::KeyDown);
	buttonRight.update(XInput(0).buttonRight, Input::KeyRight);
	buttonLeft.update(XInput(0).buttonLeft, Input::KeyLeft);
	buttonA.update(XInput(0).buttonA, Input::KeySlash);
	buttonB.update(XInput(0).buttonB, Input::KeyBackslash);
	buttonX.update(XInput(0).buttonX, Input::KeySemicolon);
	buttonY.update(XInput(0).buttonY, Input::KeyColon);
	buttonR.update(XInput(0).buttonRB, Input::KeyRShift);
	buttonL.update(XInput(0).buttonLB, Input::KeyLShift);
	buttonRS.update(XInput(0).buttonRThumb, Input::KeyRControl);
	buttonLS.update(XInput(0).buttonLThumb, Input::KeyLControl);
	if (XInput(0).isConnected()) {
		triggerR = XInput(0).rightTrigger;
		triggerL = XInput(0).leftTrigger;
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
	sound_vol(100) {

}

void GameSystem::update() {
	input.update();
}