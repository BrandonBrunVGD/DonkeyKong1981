#ifndef __LADDER_H
#define __LADDER_H
#include "AnimatedTexture.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "PhysEntity.h"

using namespace SDLFramework;

class Ladder : public PhysEntity {
private:
	Timer* mTimer;
	AudioManager* mAudio;

	bool mVisible;
	bool mAnimating;

	int mScore;

	float mMoveSpeed;
	Vector2 mMoveBounds;

public:
	Ladder();
	~Ladder();

	int Score();

	void Visible(bool visible);
	bool IsAnimating();

	void AddScore(int change);

	// Inherited from PhysEntity
	bool IgnoreCollisions() override;

	void Update() override;
	void Render() override;
};
#endif