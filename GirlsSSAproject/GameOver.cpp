# include <Siv3D.hpp>
# include <HamFramework.hpp>
# include "GameOver.h"
#include"System.h"

void GameOver::init() {
	TextureAsset::Register(L"gameover", L"Data/gameover.png");
	TextureAsset::PreloadAll;
}
void GameOver::update() {
	if (GameSystem::get().input.buttonA.clicked) {
		changeScene(L"Title");
	}
}
void GameOver::draw() const {
	//Println(L"Game Over:A�Ń^�C�g����ʂ�");
	TextureAsset(L"gameover").draw();
}