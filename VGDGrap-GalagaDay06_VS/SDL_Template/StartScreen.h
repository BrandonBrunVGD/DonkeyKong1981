#ifndef __STARTSCREEN_H
#define __STARTSCREEN_H
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "ScoreBoard.h"

using namespace SDLFramework;

class StartScreen : public GameEntity {

private:
    Timer* mTimer;
    InputManager* mInput;

    // Logo Entities
    Texture* mLogo;

    // Play Mode Entities
    GameEntity* mPlayModes;
    Texture* mOnePlayerModeA;
    Texture* mOnePlayerModeB;
    Texture* mTwoPlayerModeA;
    Texture* mTwoPlayerModeB;
    Texture* mCursor;

    Vector2 mCursorStartPos;
    Vector2 mCursorOffset;
    int mSelectedMode;

    // Bottom Bar Entities
    GameEntity* mBottomBar;

    Texture* mDates;
    Texture* mRights;

    // Screen Animation Variables
    Vector2 mAnimationStartPos;
    Vector2 mAnimationEndPos;
    float mAnimationTotalTime;
    float mAnimationTimer;
    bool mAnimationDone;

public:
    StartScreen();
    ~StartScreen();

    void ChangeSelectedMode(int change);

    void Update() override;
    void Render() override;
};
#endif