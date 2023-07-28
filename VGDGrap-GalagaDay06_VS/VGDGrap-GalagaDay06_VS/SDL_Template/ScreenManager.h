#ifndef __SCREENMANAGER_H
#define __SCREENMANAGER_H
#include "StartScreen.h"
#include "PlayScreen.h"
#include "AudioManager.h"

class ScreenManager {
private:
	static ScreenManager * sInstance;

	enum Screens { Start, Play };
	Screens mCurrentScreen;

	InputManager * mInput;

	AudioManager* mAudioManager;

	StartScreen * mStartScreen;
	PlayScreen * mPlayScreen;

public:
	static ScreenManager * Instance();
	static void Release();

	void Update();
	void Render();

	void ResetLevel();

private:
	ScreenManager();
	~ScreenManager();
};
#endif