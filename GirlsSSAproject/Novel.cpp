# include <Siv3D.hpp>
# include <HamFramework.hpp>
# include "Novel.h"
#include "System.h"

Novel::Novel() :
	window(RectF(Vec2(0, 720 * 2 / 3), Vec2(1280, 720 / 3))),
	text(TextReader(L"Data/novel1.txt")),
	WaitCount(0)
	//font(Font(18, L"HG正楷書体-PRO"))
{
	TextureAsset::Register(L"haikei_novel1", L"Data/haikei_novel1.png");
	TextureAsset::Register(L"tatie_rag_normal", L"Data/tatie_rag_normal.png");
	TextureAsset::Register(L"tatie_sophie_normal", L"Data/tatie_sophie_normal.png");
	TextureAsset::PreloadAll();
	FontAsset::Register(L"novel", 18, L"HG正楷書体-PRO");
	FontAsset::PreloadAll();

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
	if (WaitCount <= 0 && (GameSystem::get().input.buttonA.clicked || GameSystem::get().input.buttonY.pressed)) {
		TalkInfo info;
		String str;
		while (str != L" ") {
			if (text.readLine(str) == false) {
				part = L"finish";
				return;
			}
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

		if (info.scene == -1) {
			info.scene = (talk_log.end() - 1)->scene;
		}
		if (info.scene == 100) {
			String str2;
			while (str2 != L" ") {
				if (text.readLine(str2) == false) {
					part = L"finish";
					return;
				}

				if (str2.startsWith(L"scene:")) {
					info.scene = Parse<int>(str2.remove(L"scene:"));
				}
				else if (str2.startsWith(L"talker:")) {
					info.talker = str2.remove(L"talker:");
				}
				else {
					info.words += (str2 + L"\n");
				}
			}
			talk_log.emplace_back(info);
			part = L"action";
			SoundAsset(L"bgm").play();
			return;
		}
		talk_log.emplace_back(info);
		if ((talk_log.end() - 1)->scene != (talk_log.end() - 2)->scene) {
			WaitCount = 60;
		}
	}
}

void Novel::draw() const {
	if ((talk_log.end() - 1)->scene == 1) {
		TextureAsset(L"haikei_novel1").draw(Vec2(0, 0), Alpha(255 * (60 - WaitCount) / 60));

		if ((talk_log.end() - 1)->talker == L"少女" || (talk_log.end() - 1)->talker == L"ソフィ") {
			TextureAsset(L"tatie_sophie_normal").scale(0.4).mirror().drawAt(Vec2(1280 * 1 / 8, 720 * 1 / 2), Alpha(255 * (60 - WaitCount) / 60));
			TextureAsset(L"tatie_rag_normal").scale(0.4).drawAt(Vec2(1280 * 7 / 8, 720 * 1 / 2), Color(128, 128, 128, 255 * (60 - WaitCount) / 60));
		}
		else if ((talk_log.end() - 1)->talker == L"？？？" || (talk_log.end() - 1)->talker == L"ラグ") {
			TextureAsset(L"tatie_sophie_normal").scale(0.4).mirror().drawAt(Vec2(1280 * 1 / 8, 720 * 1 / 2), Color(128, 128, 128, 255 * (60 - WaitCount) / 60));
			TextureAsset(L"tatie_rag_normal").scale(0.4).drawAt(Vec2(1280 * 7 / 8, 720 * 1 / 2), Alpha(255 * (60 - WaitCount) / 60));
		}
		else {
			TextureAsset(L"tatie_sophie_normal").scale(0.4).mirror().drawAt(Vec2(1280 * 1 / 8, 720 * 1 / 2), Color(128, 128, 128, 255 * (60 - WaitCount) / 60));
			TextureAsset(L"tatie_rag_normal").scale(0.4).drawAt(Vec2(1280 * 7 / 8, 720 * 1 / 2), Color(128, 128, 128, 255 * (60 - WaitCount) / 60));
		}
	}

	window.draw(Color(0, 0, 0, 255 * 0.5));

	if ((talk_log.end() - 1)->talker != L"none") {
		FontAsset(L"novel")(L"【" + (talk_log.end() - 1)->talker + L"】").draw(Vec2(1280 * 1 / 5, 720 * 2 / 3 + 5), Color(255, 255, 255));
	}
	FontAsset(L"novel")((talk_log.end() - 1)->words).draw(Vec2(1280 * 1 / 5, 720 * 2 / 3 + 5) + Vec2(20, FontAsset(L"novel").height + 5), Color(255, 255, 255));
}

