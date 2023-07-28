#include "Ladder.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

Ladder::Ladder() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mVisible = true;
	mAnimating = false;

	mScore = 0;

	AddCollider(new BoxCollider(Vector2(32.0f, 34.0f)));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);
}

Ladder::~Ladder() {
	mTimer = nullptr;
	mAudio = nullptr;

}

void Ladder::Visible(bool visible) {
	mVisible = visible;
}

bool Ladder::IsAnimating() {
	return mAnimating;
}

int Ladder::Score() {
	return mScore;
}

void Ladder::AddScore(int change) {
	mScore += change;
}

bool Ladder::IgnoreCollisions()
{
	return !mVisible || mAnimating;
}

void Ladder::Update() {

}

void Ladder::Render() {
	if (mVisible) {
		if (mAnimating) {

		}
		else {
			
		}
	}

	PhysEntity::Render();
}