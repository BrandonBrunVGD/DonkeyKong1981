 #include "ScreenManager.h"

ScreenManager * ScreenManager::sInstance = nullptr;

ScreenManager * ScreenManager::Instance() {
	if (sInstance == nullptr) {
		sInstance = new ScreenManager();
	}

	return sInstance;
}

void ScreenManager::Release() {
	delete sInstance;
	sInstance = nullptr;
}

void ScreenManager::Update() {

	switch (mCurrentScreen) {
	case Start:
		mStartScreen->Update();
		

		if (mInput->KeyPressed(SDL_SCANCODE_RETURN)) {
			mCurrentScreen = Play;
			mAudioManager->PlaySFX("SFX/bacmusic.wav", -1);
		}
		break;
	case Play:
		mPlayScreen->Update();
		
		break;
	}

	if (mPlayScreen->GetResetGame() == true) {
		ResetLevel();
		mPlayScreen->SetResetGame(false);
	}
}

void ScreenManager::Render() { 


	switch (mCurrentScreen) {
	case Start:
		mStartScreen->Render();
		break;
	case Play:
		mPlayScreen->Render();
		break;
	}
}

ScreenManager::ScreenManager() {
	mInput = InputManager::Instance();
	mAudioManager = AudioManager::Instance();

	mStartScreen = new StartScreen();
	mPlayScreen = new PlayScreen();

	mCurrentScreen = Start;

	mAudioManager->PlayMusic("SFX/Opening.mp3", 1);
}

ScreenManager::~ScreenManager() {
	mInput = nullptr;

	delete mStartScreen;
	mStartScreen = nullptr;

	delete mPlayScreen;
	mPlayScreen = nullptr;
}

void ScreenManager::ResetLevel() {
	delete mPlayScreen;
	mPlayScreen = new PlayScreen();
}