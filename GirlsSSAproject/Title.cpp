#include<Siv3D.hpp>
#include<HamFramework.hpp>
#include"Title.h"
#include"System.h"

void Title::init() {
	TextureAsset::Register(L"title", L"Data/title.png");
	TextureAsset::PreloadAll;

	SoundAsset::Register(L"bgm", L"Data/bgm.mp3");
	SoundAsset::PreloadAll;
	SoundAsset(L"bgm").setLoop(true);
	SoundAsset(L"bgm").play();
}

void Title::update() {
	if (GameSystem::get().input.buttonA.clicked) {
		changeScene(L"Game");
		SoundAsset(L"bgm").stop();
	}
}

void Title::draw() const {
	//Println(L"タイトル画面:Aでセレクト画面へ");
	TextureAsset(L"title").draw();
}
