#pragma once
#include<Siv3D.hpp>

class TalkInfo {
public:
	int scene;
	String talker;
	String words;

	TalkInfo(/*int _scene, String _talker, String _words*/) :
	scene(-1/*_scene*/)//,
	//talker(/*_talker*/),
	//words(/*_words*/)
	{
		
	}
};

class Novel {
public:
	RectF window;
	TextReader text;
	int WaitCount;
	Font font;
	bool EnptyFlag = true;

	std::vector<TalkInfo> talk_log;

	Novel();
	void update(String &part);
	void draw() const;
private:
};