#include "Item.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

Item::Item() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mVisible = true;
	mAnimating = false;

	mScore = 0; 

	mHammer = new Texture("mario.png", 340, 96, 9, 10);
	mHammer->Scale(Vector2(3.50f, 3.50f));
	mHammer->Parent(this);
	mHammer->Position(Graphics::SCREEN_WIDTH * 0.0f, Graphics::SCREEN_HEIGHT * 0.0f);

	AddCollider(new BoxCollider(Vector2(32.0f, 34.0f)));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Item);
}

Item::~Item() {
	mTimer = nullptr;
	mAudio = nullptr;

	delete mHammer;
	mHammer = nullptr;
}

void Item::Visible(bool visible) {
	mVisible = visible;
}

bool Item::IsAnimating() {
	return mAnimating;
}

int Item::Score() {
	return mScore;
}

void Item::AddScore(int change) {
	mScore += change;
}

bool Item::IgnoreCollisions()
{
	return !mVisible;
}

void Item::Update() {
	if (Active()) {

		mHammer->Update();
	}
}

void Item::Render() {
	if (Active()) {

		if (mVisible) {

			mHammer->Render();
			
		}
	}

	PhysEntity::Render();
}