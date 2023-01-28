#ifndef __PLAYSCREEN_H
#define __PLAYSCREEN_H
#include "Timer.h"
#include "AudioManager.h"
#include "Player.h"
#include "item.h"
#include "Barrel.h"
#include "Scoreboard.h"

class PlayScreen : public GameEntity {
private:
	Timer * mTimer;
	AudioManager * mAudio;
	Barrel* mBarrel;

	float mBarrelMoveSpeed;
	bool mBarrelCanGoDown;
	float mBarrelFallSpeed;

	bool mSlope;
	bool mDecline;

	bool mBarrelJumped;
	int mScoreTimer;
	int mStartTimer;

	bool mCanJumpScore;
	bool mCheckIgniteBarrel;
	int mIgniteBarrel;

	Item* mItem;
	Item* mItem2;
	Player * mPlayer;
	Texture* mBackground;
	
	Texture* mBarrelStack;
	AnimatedTexture* mDonkeyKong;
	Texture* mHighScore;
	Texture* m100;
	Texture* m300;

	Scoreboard* mScoreTexture;
	Texture* mLivesTexture;

	Texture* mBottomBarrel;
	AnimatedTexture* mBottomBarrelIgnite;
	AnimatedTexture* mBottomBarrelFlaming;

public:
	PlayScreen();
	~PlayScreen();

	void Update() override;
	void Render() override;

	void BarrelMove();

	bool CheckCollision(float x, float y, float w, float h);

	void Timer(Texture* other, int timer);

	void StartTimer(int timer);
};
#endif