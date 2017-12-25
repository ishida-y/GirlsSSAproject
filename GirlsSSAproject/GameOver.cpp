# include <Siv3D.hpp>
# include <HamFramework.hpp>
# include "GameOver.h"
#include"System.h"

void GameOver::init() {

}
void GameOver::update() {
	if (GameSystem::get().input.buttonA.clicked) {
		changeScene(L"Title");
	}
}
void GameOver::draw() const {
	Println(L"Game Over:A‚Åƒ^ƒCƒgƒ‹‰æ–Ê‚Ö");
}
