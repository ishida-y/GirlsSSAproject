#include<Siv3D.hpp>
#include<HamFramework.hpp>
#include"Title.h"
#include"System.h"

void Title::init() {
	
}

void Title::update() {
	if (GameSystem::get().input.buttonA.clicked) {
		changeScene(L"Game");
	}
}

void Title::draw() const {
	Println(L"�^�C�g�����:A�ŃZ���N�g��ʂ�");
}
