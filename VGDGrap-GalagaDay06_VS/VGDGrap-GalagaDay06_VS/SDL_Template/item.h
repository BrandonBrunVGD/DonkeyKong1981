#ifndef __ITEM_H
#define __ITEM_H
#include "AnimatedTexture.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "PhysEntity.h"

using namespace SDLFramework;

class Item : public PhysEntity {
private:
	Timer* mTimer;
	AudioManager* mAudio;

	bool mVisible;
	bool mAnimating;

	int mScore;

	//Texture * mMario;
	Texture* mHammer;

	float mMoveSpeed;
	Vector2 mMoveBounds;

public:
	Item();
	~Item();

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