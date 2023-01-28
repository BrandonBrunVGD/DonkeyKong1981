#ifndef __BARREL_H
#define __BARREL_H
#include "AnimatedTexture.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "PhysEntity.h"


using namespace SDLFramework;

class Barrel : public PhysEntity {
private:
	Timer* mTimer;
	AudioManager* mAudio;

	bool mVisible;
	bool mAnimating;

	int mScore;

	//Texture * mMario;
	AnimatedTexture* mBarrel;
	AnimatedTexture* mBarrelLadder;

	float mMoveSpeed;
	Vector2 mMoveBounds;

public:
	Barrel();
	~Barrel();

	int Score();

	void Visible(bool visible);
	bool GetVisible();

	bool IsAnimating();

	void AddScore(int change);

	// Inherited from PhysEntity
	bool IgnoreCollisions() override;

	void Hit(PhysEntity* other) override;

	void SetBarrelLadder(bool down);

	void Update() override;
	void Render() override;
};
#endif
