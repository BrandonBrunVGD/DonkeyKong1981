#include "Player.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

void Player::HandleMovement() {

	if (mCanClimb) {
		if (mInput->KeyDown(SDL_SCANCODE_W)) {
			Translate(-Vec2_Up * mMoveSpeed * mTimer->DeltaTime(), World);
			mAudio->PlaySFX("SFX/Sequence 01.wav");
			mClimbing = true;
		}
		else if (mInput->KeyDown(SDL_SCANCODE_S)) {
			Translate(Vec2_Up * mMoveSpeed * mTimer->DeltaTime(), World);
			mAudio->PlaySFX("SFX/Sequence 01.wav");
			mClimbing = true;
		}
		else {
			//mClimbing = false;
		}
		 
	}
	else mClimbing = false;

	if (mClimbing == false) {
		//mStopClimbing = true;

		//if (!mHammering) {
			if (mInput->KeyDown(SDL_SCANCODE_D)) {
				Translate(Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), World);
				mAudio->PlaySFX("SFX/Sequence 01.wav");
				
				//if (mSlope) {
					if (mIncline) {
						Position(Position().x, Position().y - 9 * mTimer->DeltaTime());
					}

					if (mDecline) {
						Position(Position().x, Position().y + 9 * mTimer->DeltaTime());
					}
				//}

				if (mCanJump) {
					mAnimating = false;
					mAnimatingRight = true;
					mIdleLeft = false;
					mIdleRight = true;
				}

				if (mHammering) {
					mAnimating = false;
					mAnimatingRight = false;
					mHammeringLeft = false;
					mHammeringRight = true;
				}
			}
			else if (mInput->KeyDown(SDL_SCANCODE_A)) {
				Translate(-Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), World);
				mAudio->PlaySFX("SFX/Sequence 01.wav");

				//if (mSlope) {
					if (mIncline) {
						Position(Position().x, Position().y + 9 * mTimer->DeltaTime());
					}

					if (mDecline) {
						Position(Position().x, Position().y - 9 * mTimer->DeltaTime());
					}
				//}

				if (mCanJump) {
					mAnimatingRight = false;
					mAnimating = true;
					mIdleRight = false;
					mIdleLeft = true;
				}

				if (mHammering) {
					mAnimating = false;
					mAnimatingRight = false;
					mHammeringRight = false;
					mHammeringLeft = true;
				}
			}
			else {
				mAnimating = false;
				mAnimatingRight = false;
			}
		
		if (mInput->KeyDown(SDL_SCANCODE_SPACE) && mCanJump) {

			mYVelocity = -250;
			mGroundLevel = Position().y;
			mCanJump = false;		
		}		
	}

	Vector2 pos = Position(Local);
	if (pos.x < mMoveBounds.x) {
		pos.x = mMoveBounds.x;
	}
	else if (pos.x > mMoveBounds.y) {
		pos.x = mMoveBounds.y;
	}

	Position(pos);
}

Player::Player() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mVisible = true;
	mAnimating = false;
	mAnimatingRight = false;
	mIdleRight = true;
	mClimbing = false;
	mStopClimbing = false;
	mWasHit = false;

	mCanClimb = false;
	mCanPickUp = true;

	mSlope = false;

	mGravity = 500;
	mCanJump = true;
	mYVelocity = 0;

	mHammering = false;
	mHammeringRight = false;
	mHammeringLeft = false;
	mHammerTimer = 10;

	mScore = 0;
	mLives = 1;

	mDestroyBarrel = false;

	//idle left
	mMarioIdle = new Texture("MarioRunning.png", 0, 0, 16, 16);
	mMarioIdle->Scale(Vector2(3.50f, 3.50f));
	mMarioIdle->Parent(this);
	mMarioIdle->Position(Graphics::SCREEN_WIDTH * 0.0f, Graphics::SCREEN_HEIGHT * 0.0f);

	//idle right
	mMarioIdleRight = new Texture("MarioRunningRight.png", 0, 0, 16, 16);
	mMarioIdleRight->Scale(Vector2(3.50f, 3.50f));
	mMarioIdleRight->Parent(this);
	mMarioIdleRight->Position(Graphics::SCREEN_WIDTH * 0.0f, Graphics::SCREEN_HEIGHT * 0.0f);

	//running left
	mMarioRunning = new AnimatedTexture("MarioRunning.png", 0, 0, 16, 16, 3, 0.250f, AnimatedTexture::Horizontal);
	mMarioRunning->Scale(Vector2(3.50f, 3.50f));
	mMarioRunning->Parent(this);
	mMarioRunning->Position(Graphics::SCREEN_WIDTH * 0.0f, Graphics::SCREEN_HEIGHT * 0.0f);

	//running right
	mMarioRunningRight = new AnimatedTexture("MarioRunningRight.png", 0, 0, 16, 16, 3, 0.250f, AnimatedTexture::Horizontal);
	mMarioRunningRight->Scale(Vector2(3.50f, 3.50f));
	mMarioRunningRight->Parent(this);
	mMarioRunningRight->Position(Graphics::SCREEN_WIDTH * 0.0f, Graphics::SCREEN_HEIGHT * 0.0f);

	//climbing
	mMarioClimbing = new AnimatedTexture("mario.png", 112, 10, 16, 16, 2, 0.250f, AnimatedTexture::Horizontal);
	mMarioClimbing ->Scale(Vector2(3.50f, 3.50f));
	mMarioClimbing->Parent(this);
	mMarioClimbing->Position(Graphics::SCREEN_WIDTH * 0.0f, Graphics::SCREEN_HEIGHT * 0.0f);

	//stop climbing
	mMarioStopClimbing = new AnimatedTexture("mario.png", 153, 10, 16, 16, 3, 0.250f, AnimatedTexture::Horizontal);
	mMarioStopClimbing->Scale(Vector2(3.50f, 3.50f));
	mMarioStopClimbing->Parent(this);
	mMarioStopClimbing->Position(Graphics::SCREEN_WIDTH * 0.0f, Graphics::SCREEN_HEIGHT * 0.0f);

	//mario hammering
	mMarioHammerLeft = new AnimatedTexture("mario.png", 400, 0, 32, 26, 2, 0.250f, AnimatedTexture::Horizontal);
	mMarioHammerLeft->Scale(Vector2(3.50f, 3.50f));
	mMarioHammerLeft->Parent(this);
	mMarioHammerLeft->Position(Graphics::SCREEN_WIDTH * -0.026f, Graphics::SCREEN_HEIGHT * -0.02f);

	//mario hammering
	mMarioHammerRight = new AnimatedTexture("mario.png", 340, 0, 32, 26, 2, 0.250f, AnimatedTexture::Horizontal);
	mMarioHammerRight->Scale(Vector2(3.50f, 3.50f));
	mMarioHammerRight->Parent(this);
	mMarioHammerRight->Position(Graphics::SCREEN_WIDTH * 0.026f, Graphics::SCREEN_HEIGHT * -0.02f);

	mMoveSpeed = 150.0f;
	mMoveBounds = Vector2(140.0f, 883.0f);

	mGroundLevel = Position().y;

	mDeathAnimation = new AnimatedTexture("mario.png", 290, 1, 16, 16, 3, 1.0f, AnimatedTexture::Horizontal);
	mDeathAnimation->Scale(Vector2(3.50f, 3.50f));
	mDeathAnimation->Parent(this);
	mDeathAnimation->Position(Vec2_Zero);
	mDeathAnimation->SetWrapMode(AnimatedTexture::Once);
	
	mJumpTexture = new Texture("mario.png", 263, 20, 16, 15);
	mJumpTexture->Scale(Vector2(3.50f, 3.50f));
	mJumpTexture->Parent(this);
	mJumpTexture->Position(Graphics::SCREEN_WIDTH * 0.0f, Graphics::SCREEN_HEIGHT * 0.0f);

	

	AddCollider(new BoxCollider(Vector2(45.0f, 58.0f)));
	
	//AddCollider(new BoxCollider(Vector2(20.0f, 37.0f)), Vector2( 18.0f, 10.0f));
	//AddCollider(new BoxCollider(Vector2(20.0f, 37.0f)), Vector2(-18.0f, 10.0f));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);
}

Player::~Player() {
	mTimer = nullptr;
	mInput = nullptr;
	mAudio = nullptr;

	delete mMarioIdle;
	mMarioIdle = nullptr;

	delete mMarioIdleRight;
	mMarioIdleRight = nullptr;

	delete mMarioRunning;
	mMarioRunning = nullptr;

	delete mMarioRunningRight;
	mMarioRunningRight = nullptr;

	delete mMarioClimbing;
	mMarioClimbing = nullptr;

	delete mMarioStopClimbing;
	mMarioStopClimbing = nullptr;

	delete mMarioHammerLeft;
	mMarioHammerLeft = nullptr;

	delete mMarioHammerRight;
	mMarioHammerRight = nullptr;

	delete mDeathAnimation;
	mDeathAnimation = nullptr;

	delete mJumpTexture;
	mJumpTexture = nullptr;

	
}

void Player::Visible(bool visible) {
	mVisible = visible;
}

bool Player::IsAnimating() {
	return mAnimating;
}

int Player::Score() {
	return mScore;
}

int Player::Lives() {
	return mLives;
}

void Player::AddScore(int change) {
	mScore += change;
}

bool Player::IgnoreCollisions()
{
	return !mVisible;
}

void Player::Hit(PhysEntity * other) {

	if (other->GetTag() == "Hammer") {
		
		if (mCanPickUp) {

			other->Active(false);
			mHammering = true;
			mCanPickUp = false;
		}
	}

	if (other->GetTag() == "Enemy") {

		if (mHammering) {
			if (mCanJump) {
				mDestroyBarrel = true;
				mAudio->PlaySFX("SFX/hammerSmash.wav");
			}
		}
		else {
			mDeathAnimation->ResetAnimation();
			mAudio->PlaySFX("SFX/death.wav");
			mWasHit = true;
			mLives -= 1;
			
		}
	}
}

bool Player::WasHit() {

	return mWasHit;
}

void Player::Update() {

	if (Active()) {
		HandleMovement();

		mMarioRunning->Update();
		mMarioRunningRight->Update();
		mMarioClimbing->Update();
		mMarioStopClimbing->Update();
		mMarioHammerLeft->Update();
		mMarioHammerRight->Update();
		
		
		//mMarioIdle->Update();
		//mMarioIdleRight->Update();

		//if (mAnimating) {

		if (mWasHit) {
			mDeathAnimation->Update();
			//mWasHit = false;
		}
		
		if (!mCanJump) {
			mJumpTexture->Update();
		}

			//mDeathAnimation->Update();
			//mAnimating = mDeathAnimation->IsAnimating();
			
		
	}
	
	mCanClimb = CheckCollision((184 * 3.5) + 148, 216 * 3.5, 8 * 3.5, 27 * 3.5) ||
		CheckCollision((96 * 3.5) + 148, 179 * 3.5, 8 * 3.5, 35 * 3.5) ||
		CheckCollision((32 * 3.5) + 148, 183 * 3.5, 8 * 3.5, 27 * 3.5) ||
		CheckCollision((112 * 3.5) + 148, 146 * 3.5, 8 * 3.5, 35 * 3.5) ||
		CheckCollision((184 * 3.5) + 148, 150 * 3.5, 8 * 3.5, 27 * 3.5) ||
		CheckCollision((72 * 3.5) + 148, 115 * 3.5, 8 * 3.5, 31 * 3.5) ||
		CheckCollision((32 * 3.5) + 148, 117 * 3.5, 8 * 3.5, 27 * 3.5) ||
		CheckCollision((184 * 3.5) + 148, 84 * 3.5, 8 * 3.5, 27 * 3.5) ||
		CheckCollision((128 * 3.5) + 148, 53 * 3.5, 8 * 3.5, 31 * 3.5);
	//std::cout << "Can Climb     " << mCanClimb << "\t" << "Hammering " << mHammering << std::endl;

	if (!mCanJump) {

		mYVelocity += mGravity * mTimer->DeltaTime();
		Position(Position().x, Position().y + mYVelocity * mTimer->DeltaTime());

		if (Position().y > mGroundLevel) {

			mYVelocity = 0;
			mCanJump = true;
			Position(Position().x, mGroundLevel);
		}
	} 
	//std::cout << "Slope		" << mSlope << std::endl;
	/////


	if (Position().y < 278 && Position().x < 640) {
		mMoveBounds = Vector2(140.0f, 825.0f);
		std::cout << "\nPlatform 6" << std::endl;
	}
	else if (Position().y < 278 && Position().x > 640) {
		mMoveBounds = Vector2(140.0f, 825.0f);
		std::cout << "\nPlatform 6" << std::endl;
	}
	else if (Position().y < 395 && Position().y >= 278) {
		mMoveBounds = Vector2(197.0f, 883.0f);
		std::cout << "\nPlatform 5" << std::endl;
	}
	else if (Position().y < 510 && Position().y >= 395) {
		mMoveBounds = Vector2(140.0f, 825.0f);
		std::cout << "\nPlatform 4" << std::endl;
	}
	else if (Position().y < 629 && Position().y >= 510) {
		mMoveBounds = Vector2(197.0f, 883.0f);
		std::cout << "\nPlatform 3" << std::endl;
	}
	else if (Position().y < 741 && Position().y >= 629) {
		mMoveBounds = Vector2(140.0f, 825.0f);
		std::cout << "\nPlatform 2" << std::endl;
	}
	else if (Position().x > (112 * 3.5) + 148 && Position().y > 741 && Position().x < 870) {
		std::cout << "\nPlatform 1" << std::endl;
	}
	else {
		std::cout << "\nPlatform 1" << std::endl;
	}
	if (Position().y < 278 && Position().x < 640) {
		mIncline = false;
		mDecline = false;
	}
	else if (Position().y < 278 && Position().x > 640) {
		mIncline = false;
		mDecline = true;
	}
	else if (Position().y < 395 && Position().x < 870) {
		mIncline = true;
		mDecline = false;
	}
	else if (Position().y < 510 && Position().x > 16 + 148) {
		mIncline = false;
		mDecline = true;
	}
	else if (Position().y < 629 && Position().x < 870) {
		mIncline = true;
		mDecline = false;
	}
	else if (Position().y < 741 && Position().x > 16 + 148) {
		mIncline = false;
		mDecline = true;
	}
	else if (Position().x > (112 * 3.5) + 148 && Position().y > 741 && Position().x < 870) {
		mIncline = true;
		mDecline = false;
	}
	else {
		mIncline = false;
		mDecline = false;
	}
	
	if (mHammering) {

		mCanClimb = false;
		mHammerTimer -= mTimer->DeltaTime();

		if (mHammerTimer <= 0) {

			mHammering = false;
			mHammerTimer = 10;
			mHammeringLeft = false;
			mHammeringRight = false;
			mCanClimb = true;
			mCanPickUp = true;
		}
	}

	

	//std::cout << Position().y << std::endl;
	//std::cout << Position().x << std::endl;
	std::cout << "Score    " << mScore << std::endl;
}

void Player::Render() {

	if (mVisible) {
		if (mAnimating) {

			mMarioRunning->Render();	
		}
		else if (mAnimatingRight) {
			
			mMarioRunningRight->Render();
		}
		else if (mClimbing) {

			mMarioClimbing->Render();
		}
		else if (mStopClimbing) {
		
			mMarioStopClimbing->Render();
		}
		else if (mHammeringLeft) {

			mMarioHammerLeft->Render();
		}
		else if (mHammeringRight) {

			mMarioHammerRight->Render();
		}
		else if (mWasHit) {

			mDeathAnimation->Render();
		}
		else if (!mCanJump) {

			mJumpTexture->Render();
		}
		else {

			if (mIdleLeft) {
				mMarioIdle->Render();
			}
			else if (mIdleRight) {
				mMarioIdleRight->Render();
			}		
		}

		
	}

	PhysEntity::Render();
}

bool Player::CheckCollision(float x, float y, float w, float h) {
	float p_left = Position().x;
	float p_right = p_left + mMarioRunningRight->GetWidth();
	float p_top = Position().y;
	float p_bottom = p_top + mMarioRunningRight->GetHeight();

	float l_left = x;
	float l_right = x + w;
	float l_top = y;
	float l_bottom = y + h;

	return p_right > l_left && p_left < l_right && p_bottom > l_top && p_top < l_bottom;
}

int Player::GetLives() {
	return mLives;
}

int Player::GetScore() {
	return mScore;
}

float Player::GetGroundLevel() {
	return mGroundLevel;
}

bool Player::GetCanJump() {
	return mCanJump;
}

bool Player::GetDestroyBarrel() {
	return mDestroyBarrel;
}

void Player::SetDestroyBarrel(bool destroy) {
	mDestroyBarrel = destroy;
}

bool Player::GetWasHit() {
	return mWasHit;
}
