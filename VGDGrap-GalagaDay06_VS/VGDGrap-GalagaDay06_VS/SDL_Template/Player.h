#ifndef __PLAYER_H
#define __PLAYER_H
#include "AnimatedTexture.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "PhysEntity.h"
#include "item.h"
//#include "Barrel.h"

using namespace SDLFramework;

class Player : public PhysEntity {
private:
	Timer * mTimer;
	InputManager * mInput;
	AudioManager * mAudio;

	bool mVisible;
	bool mAnimating;
	bool mAnimatingRight;
	bool mWasHit;
	bool mIdleLeft;
	bool mIdleRight;

	bool mCanClimb;
	bool mClimbing;
	bool mStopClimbing;

	bool mHammering;
	bool mHammeringLeft;
	bool mHammeringRight;
	float mHammerTimer;

	bool mCanJump;
	bool mCanPickUp;

	bool mSlope;
	int mIncline;
	int mDecline;

	float mGroundLevel;
	float mGravity;
	float mYVelocity;

	int mScore;
	int mLives;

	bool mDestroyBarrel;

	

	Texture* mMarioIdle;
	Texture* mMarioIdleRight;
	Texture* mJumpTexture;
	AnimatedTexture* mMarioHammerLeft;
	AnimatedTexture* mMarioHammerRight;
	AnimatedTexture* mMarioClimbing;
	AnimatedTexture* mMarioStopClimbing;
	AnimatedTexture* mMarioRunning;
	AnimatedTexture* mMarioRunningRight;
	AnimatedTexture* mDeathAnimation;
	Item* mPickUp;
	

	float mMoveSpeed;
	Vector2 mMoveBounds;

private:
	void HandleMovement();

public:
	Player();
	~Player();

	void Visible(bool visible);
	bool IsAnimating();

	int Score();
	int Lives();

	void AddScore(int change);

	// Inherited from PhysEntity
	bool IgnoreCollisions() override;
	void Hit(PhysEntity * other) override;
	
	bool WasHit();

	void Update() override;
	void Render() override;

	int GetLives();
	int GetScore();
	float GetGroundLevel();
	bool GetCanJump();

	bool CheckCollision(float x, float y, float w, float h);

	bool GetDestroyBarrel();
	void SetDestroyBarrel(bool destroy);

	bool GetWasHit();
};
#endif