#pragma once
#include<Siv3D.hpp>

class TalkInfo {
public:
	int scene;
	String talker;
	String words;

	TalkInfo() :
	scene(-1)
	{
		
	}
};

class Novel {
public:
	RectF window;
	TextReader text;
	String NextFileName;
	int WaitCount;
	//Font font;

	std::vector<TalkInfo> talk_log;

	Novel();
	void update(String &part);
	void draw() const;
private:
};