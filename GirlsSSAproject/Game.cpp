# include <Siv3D.hpp>
# include <HamFramework.hpp>
# include "Game.h"

void Game::init() {
	part = L"novel";
}

void Game::update() {
	if (part == L"action") {
		actoin.update(part);
	}
	if (part == L"novel" || part == L"novel_on_action") {
		novel.update(part);
	}
}

void Game::draw() const {
	if (part == L"action" || part == L"novel_on_action") {
		actoin.draw();
	}
	if (part == L"novel" || part == L"novel_on_action") {
		novel.draw();
	}
}
