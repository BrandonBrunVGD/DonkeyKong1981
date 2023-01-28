#include "Barrel.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

Barrel::Barrel() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mVisible = true;
	mAnimating = false;

	mScore = 0;

	//Barrel Rolling
	mBarrel = new AnimatedTexture("mario.png", 266, 140, 12, 12, 4, 0.550f, AnimatedTexture::Horizontal);
	mBarrel->Scale(Vector2(3.50f, 3.50f));
	mBarrel->Parent(this);
	mBarrel->Position(Graphics::SCREEN_WIDTH * 0.0f, Graphics::SCREEN_HEIGHT * 0.0f);

	//Barrel Rolling Down Ladder
	mBarrelLadder = new AnimatedTexture("mario.png", 360, 141, 16, 10, 2, 0.550f, AnimatedTexture::Horizontal);
	mBarrelLadder->Scale(Vector2(3.50f, 3.50f));
	mBarrelLadder->Parent(this);
	mBarrelLadder->Position(Graphics::SCREEN_WIDTH * 0.0f, Graphics::SCREEN_HEIGHT * 0.0f);

	AddCollider(new BoxCollider(Vector2(40.0f, 34.0f)));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);
} 

Barrel::~Barrel() {
	mTimer = nullptr;
	mAudio = nullptr;

	delete mBarrel;
	mBarrel = nullptr;

	delete mBarrelLadder;
	mBarrelLadder = nullptr;
}

void Barrel::Visible(bool visible) {
	mVisible = visible;
}

bool Barrel::IsAnimating() {
	return mAnimating;
}

int Barrel::Score() {
	return mScore;
}

void Barrel::AddScore(int change) {
	mScore += change;
}

bool Barrel::IgnoreCollisions()
{
	return !mVisible || !Active();
}

void Barrel::Update() {
	if (Active()) {

		if (mVisible) {

			if (mAnimating) {
				mBarrelLadder->Update();
			}
			else {
				mBarrel->Update();
			}
		}
	}
}

void Barrel::Render() {
	if (Active()) {

		if (mVisible) {

			if (mAnimating) {
				mBarrelLadder->Render();
			}
			else {
				mBarrel->Render();
			}
		}

		PhysEntity::Render();
	}
}

void Barrel::SetBarrelLadder(bool down) {
	mAnimating = down;
}

void Barrel::Hit(PhysEntity* other) {

	mVisible = false;
}

bool Barrel::GetVisible() {
	return mVisible;
}