# include <Siv3D.hpp>
# include <HamFramework.hpp>
# include "Novel.h"
#include "System.h"

Novel::Novel() :
	window(RectF(Vec2(0, 720 * 2 / 3), Vec2(1280, 720 / 3))),
	text(TextReader(L"Data/novel1.txt")),
	WaitCount(0),
	font(Font(18, L"HGê≥û≤èëëÃ-PRO"))
{
	TextureAsset::Register(L"haikei_novel1", L"Data/haikei_novel1.png");
	TextureAsset::Register(L"tatie_rag_normal", L"Data/tatie_rag_normal.png");
	TextureAsset::Register(L"tatie_sophie_normal", L"Data/tatie_sophie_normal.png");
	TextureAsset::PreloadAll();

	TalkInfo info;// (-1, nullptr, nullptr);
	String str;// = nullptr;
	while (str != L" ") {
		text.readLine(str);
		if (str.startsWith(L"scene:")) {
			info.scene = Parse<int>(str.remove(L"scene:"));
		}
		else if (str.startsWith(L"talker:")) {
			info.talker = str.remove(L"talker:");
		}
		else {
			info.words += (str + L"\n");
		}
	}
	talk_log.emplace_back(info);
}

void Novel::update(String &part) {
	if (WaitCount > 0) {
		WaitCount--;
	}
	//EnptyFlag = true;
	if (WaitCount <= 0 && GameSystem::get().input.buttonA.clicked) {
		TalkInfo info;//(-1, nullptr, nullptr);
		String str;
		while (str != L" ") {
			if (text.readLine(str) == false) {
				part = L"action";
				return;
			}
			if (str.startsWith(L"scene:")) {
				info.scene = Parse<int>(str.remove(L"scene:"));
			}
			else if (str.startsWith(L"talker:")) {
				info.talker = str.remove(L"talker:");
			}
			else {
				EnptyFlag = false;
				info.words += (str + L"\n");
			}
		}
		//if (EnptyFlag) {
		//	part = L"action";
		//	return;
		//}

		if (info.scene == -1) {
			info.scene = (talk_log.end() -1)->scene;
		}
		talk_log.emplace_back(info);
		if ((talk_log.end() -1)->scene - (talk_log.end() -2)->scene > 0) {
			WaitCount = 60;
		}
	}
}

void Novel::draw() const {
	if ((talk_log.end() -1)->scene == 1) {
		if (WaitCount > 0) {
			TextureAsset(L"haikei_novel1").draw(Vec2(0, 0), Alpha(255 * (60 - WaitCount) / 60));
		}
		else {
			TextureAsset(L"haikei_novel1").draw(Vec2(0, 0));
		}
	}
	

	window.draw(Color(0, 0, 0, 255 * 0.5));

	if ((talk_log.end() -1)->talker != L"none") {
		font(L"Åy" + (talk_log.end() -1)->talker + L"Åz").draw(Vec2(1280 * 1 / 5, 720 * 2 / 3 + 5), Color(255, 255, 255));
	}
	font((talk_log.end() -1)->words).draw(Vec2(1280 * 1 / 5, 720 * 2 / 3 + 5) + Vec2(20, font.height), Color(255, 255, 255));
}
