# include <Siv3D.hpp>
# include <HamFramework.hpp>
# include "Select.h"
# include "System.h"

void Select::init() {

}

void Select::update() {
	if (GameSystem::get().input.buttonA.clicked) {
		changeScene(L"Game");
	}
}

void Select::draw() const {
	Println(L"�Z���N�g���:A�ŃQ�[���{�҂�");
}
