#include "StartSCreen.h"

StartScreen::StartScreen() {
    mTimer = Timer::Instance();
    mInput = InputManager::Instance();

    // logo entities
    mLogo = new Texture("Donky_Kong_Start_Screen.png", 25, 25, 208, 88);

    mLogo->Parent(this); //57 121

    mLogo->Position(Graphics::SCREEN_WIDTH * 0.50f, Graphics::SCREEN_HEIGHT * 0.30f);
    mLogo->Scale(Vector2(4.0, 4.0));

    // play mode entities
    mPlayModes = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.55f);
    mOnePlayerModeA = new Texture("1 PLAYER GAME A", "emulogic.ttf", 32, { 255, 165, 0 });
    mOnePlayerModeB = new Texture("1 PLAYER GAME B", "emulogic.ttf", 32, { 255, 165, 0 });
    mTwoPlayerModeA = new Texture("2 PLAYER GAME A", "emulogic.ttf", 32, { 255, 165, 0 });
    mTwoPlayerModeB = new Texture("2 PLAYER GAME B", "emulogic.ttf", 32, { 255, 165, 0 });
    mCursor = new Texture("Donky_Kong_Start_Screen.png", 56, 120, 7, 7);

    mPlayModes->Parent(this);
    mOnePlayerModeA->Parent(mPlayModes);
    mOnePlayerModeB->Parent(mPlayModes);
    mTwoPlayerModeA->Parent(mPlayModes);
    mTwoPlayerModeB->Parent(mPlayModes);
    mCursor->Parent(mPlayModes);

    mOnePlayerModeA->Position(0.0f, 0.0f);
    mOnePlayerModeB->Position(0.0f, 65.0f);
    mTwoPlayerModeA->Position(0.0f, 130.0f);
    mTwoPlayerModeB->Position(0.0f, 195.0f);
    mCursor->Position(-280.0f, 0.0f);
    mCursor->Scale(Vector2(4.0, 4.0));

    mCursorStartPos = mCursor->Position(Local);
    mCursorOffset = Vector2(0.0f, 65.0f);
    mSelectedMode = 0;

    //bottom bar entities
    mBottomBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.7f);

    mDates = new Texture("©1981 NINTENDO CO.,LTD.", "emulogic.ttf", 32, { 255, 255, 255 });
    mRights = new Texture("MADE IN JAPAN", "emulogic.ttf", 32, { 255, 255, 255 });

    mDates->Parent(mPlayModes);
    mRights->Parent(mPlayModes);

    mDates->Position(0.0f, 260.0f);
    mRights->Position(0.0f, 325.0f);

    // screen animation variables
    mAnimationStartPos = Vector2(0.0f, Graphics::SCREEN_HEIGHT);
    mAnimationEndPos = Vec2_Zero;
    mAnimationTotalTime = 5.0f;
    mAnimationTimer = 0.0f;
    mAnimationDone = false;

    Position(mAnimationStartPos);
}

StartScreen::~StartScreen() {
    mTimer = nullptr;
    mInput = nullptr;

    // logo entities
    delete mLogo;
    mLogo = nullptr;

    // play mode entities
    delete mPlayModes;
    mPlayModes = nullptr;
    delete mOnePlayerModeA;
    mOnePlayerModeA = nullptr;
    delete mOnePlayerModeB;
    mOnePlayerModeB = nullptr;
    delete mTwoPlayerModeA;
    mTwoPlayerModeA = nullptr;
    delete mTwoPlayerModeB;
    mTwoPlayerModeB = nullptr;
    delete mCursor;
    mCursor = nullptr;

    // bottom bar entities
    delete mBottomBar;
    mBottomBar = nullptr;

    delete mDates;
    mDates = nullptr;
    delete mRights;
    mRights = nullptr;

}

void StartScreen::Update() {

    if (!mAnimationDone) {
        mAnimationTimer += mTimer->DeltaTime();
        Position(Lerp(mAnimationStartPos, mAnimationEndPos, mAnimationTimer / mAnimationTotalTime));

        if (mAnimationTimer >= mAnimationTotalTime) {
            mAnimationDone = true;
        }

        if (mInput->KeyPressed(SDL_SCANCODE_DOWN) || mInput->KeyPressed(SDL_SCANCODE_UP)) {
            mAnimationTimer = mAnimationTotalTime;
        }
    }
    else {


        if (mInput->KeyPressed(SDL_SCANCODE_DOWN)) {
            ChangeSelectedMode(1);
        }
        else if (mInput->KeyPressed(SDL_SCANCODE_UP)) {
            ChangeSelectedMode(-1);
        }
    }
}

void StartScreen::Render() {

    //logo

    mLogo->Render();


    //play modes
    mOnePlayerModeA->Render();
    mOnePlayerModeB->Render();
    mTwoPlayerModeA->Render();
    mTwoPlayerModeB->Render();
    mCursor->Render();

    //bottom bar

    mDates->Render();
    mRights->Render();

}

void StartScreen::ChangeSelectedMode(int change) {
    mSelectedMode += change;

    if (mSelectedMode < 0) {
        mSelectedMode = 3;
    }
    else if (mSelectedMode > 3) {
        mSelectedMode = 0;
    }

    mCursor->Position(mCursorStartPos + mCursorOffset * (float)mSelectedMode);
}