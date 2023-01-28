#include "PlayScreen.h"

PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mBarrelMoveSpeed = 160;
	mBarrelCanGoDown = false;
	mBarrelFallSpeed = 60;

	mDecline = false;
	mBarrelJumped = false;
	mScoreTimer = 100;
	mStartTimer = 0;
	
	mIgniteBarrel = 1;

	delete mPlayer;
	mPlayer = new Player();
	mPlayer->Parent(this);
	mPlayer->Position(Graphics::SCREEN_WIDTH * 0.30f, Graphics::SCREEN_HEIGHT * 0.937f);
	mPlayer->Active(true); 

	mItem = new Item();
	mItem->Parent(this);
	mItem->Position(Graphics::SCREEN_WIDTH * 0.72f, Graphics::SCREEN_HEIGHT * 0.75f);
	mItem->SetTag("Hammer");

	mItem2 = new Item();
	mItem2->Parent(this);
	mItem2->Position(Graphics::SCREEN_WIDTH * 0.19f, Graphics::SCREEN_HEIGHT * 0.39f);
	mItem2->SetTag("Hammer");

	mBarrel = new Barrel();
	mBarrel->Parent(this);
    mBarrel->Position(Graphics::SCREEN_WIDTH * 0.3f, Graphics::SCREEN_HEIGHT * 0.31f);
	mBarrel->SetTag("Enemy");

	mBackground = new Texture("Arcade - Donkey Kong - 25 M50 M.png", 8, 176, 224, 256);
	mBackground->Parent(this);
	mBackground->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);
	mBackground->Scale(Vector2(3.50f, 3.50f));

	mScoreTexture = new Scoreboard();
	mScoreTexture->Position(Graphics::SCREEN_WIDTH * 0.295f, Graphics::SCREEN_HEIGHT * 0.0455f);
	mScoreTexture->Scale(Vector2(0.87f, 0.87f));

	mHighScore = new Texture("999999", "emulogic.ttf", 32, { 255, 255, 255 });
	mHighScore->Parent(this);
	mHighScore->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.045f);
	mHighScore->Scale(Vector2(0.930f, 0.930f));

	mLivesTexture = new Texture("mario.png", 553, 94, 7, 8);
	mLivesTexture->Position(Graphics::SCREEN_WIDTH * 0.160f, Graphics::SCREEN_HEIGHT * 0.11f);
	mLivesTexture->Scale(Vector2(3.50f, 3.50f));

	mBarrelStack = new Texture("mario.png", 210, 122, 20, 32);
	mBarrelStack->Parent(this);
	mBarrelStack->Position(Graphics::SCREEN_WIDTH * 0.150f, Graphics::SCREEN_HEIGHT * 0.265f);
	mBarrelStack->Scale(Vector2(3.50f, 3.50f));

	mDonkeyKong = new AnimatedTexture("mario.png", 173, 42, 43, 32, 3, 1.50f, AnimatedTexture::Horizontal);
	mDonkeyKong->Parent(this);
	mDonkeyKong->Position(Graphics::SCREEN_WIDTH * 0.260f, Graphics::SCREEN_HEIGHT * 0.265f);
	mDonkeyKong->Scale(Vector2(3.50f, 3.50f));

	m100 = new Texture("mario.png", 433, 94, 15, 7);
	m100->Parent(mPlayer);
	m100->Position(Graphics::SCREEN_WIDTH * 0.0f, Graphics::SCREEN_HEIGHT * -0.06f);
	m100->Scale(Vector2(3.50f, 3.50f));

	m300 = new Texture("mario.png", 481, 94, 15, 7);
	m300->Parent(mPlayer);
	m300->Position(Graphics::SCREEN_WIDTH * 0.0f, Graphics::SCREEN_HEIGHT * -0.06f);
	m300->Scale(Vector2(3.50f, 3.50f));

	mBottomBarrel = new Texture("mario.png", 504, 122, 24, 32);
	mBottomBarrel->Parent(this);
	mBottomBarrel->Position(Graphics::SCREEN_WIDTH * 0.213f, Graphics::SCREEN_HEIGHT * 0.907f);
	mBottomBarrel->Scale(Vector2(3.50f, 3.50f));

	mBottomBarrelIgnite = new AnimatedTexture("mario.png", 452, 122, 24, 32, 2, 1.0f, AnimatedTexture::Horizontal);
	mBottomBarrelIgnite->Parent(this);
	mBottomBarrelIgnite->Position(Graphics::SCREEN_WIDTH * 0.20f, Graphics::SCREEN_HEIGHT * 0.907f);
	mBottomBarrelIgnite->Scale(Vector2(3.50f, 3.50f));

	mBottomBarrelFlaming = new AnimatedTexture("mario.png", 404, 122, 24, 32, 2, 1.0f, AnimatedTexture::Horizontal);
	mBottomBarrelFlaming->Parent(this);
	mBottomBarrelFlaming->Position(Graphics::SCREEN_WIDTH * 0.20f, Graphics::SCREEN_HEIGHT * 0.907f);
	mBottomBarrelFlaming->Scale(Vector2(3.50f, 3.50f));
}

PlayScreen::~PlayScreen() {
	mTimer = nullptr;
	mAudio = nullptr;

	delete mPlayer;
	mPlayer = nullptr;

	delete mItem;
	mItem = nullptr;

	delete mItem2;
	mItem2 = nullptr;

	delete mBarrel;
	mBarrel = nullptr;

	delete mBackground;
	mBackground = nullptr;

	delete mScoreTexture;
	mScoreTexture = nullptr;

	delete mLivesTexture;
	mLivesTexture = nullptr;

	delete mBarrelStack;
	mBarrelStack = nullptr;

	delete mDonkeyKong;
	mDonkeyKong = nullptr;

	delete mHighScore;
	mHighScore = nullptr;

	delete m100;
	m100 = nullptr;

	delete mBottomBarrel;
	mBottomBarrel = nullptr;

	delete mBottomBarrelIgnite;
	mBottomBarrelIgnite = nullptr;

	delete mBottomBarrelFlaming;
	mBottomBarrelFlaming = nullptr;

	delete m300;
	m300 = nullptr;
}

void PlayScreen::Update() {
	mBackground->Update();
	mScoreTexture->Update();
	mLivesTexture->Update();
	mItem->Update();
	mItem2->Update();
	mBarrel->Update();
	mPlayer->Update();	
	mScoreTexture->Score(mPlayer->GetScore());
	mBarrelStack->Update();
	mDonkeyKong->Update();
	mHighScore->Update();
	m100->Update();
	mBottomBarrel->Update();
	mBottomBarrelIgnite->Update();
	mBottomBarrelFlaming->Update();
	m300->Update();

	std::cout << std::endl << "Barrel Y:  " << mBarrel->Position().y;
	std::cout << std::endl << "Barrel X:  " << mBarrel->Position().x;
	std::cout << std::endl << "Player Y:  " << mPlayer->Position().y;
	std::cout << std::endl << "Player X:  " << mPlayer->Position().x;
	std::cout << std::endl << "GroundLevel:   " << mPlayer->GetGroundLevel();

	BarrelMove();

	mBarrelCanGoDown = CheckCollision((184 * 3.5) + 148, 216 * 3.5, 8 * 3.5, 22 * 3.5) ||
		CheckCollision((85 * 3.5) + 148, 179 * 3.5, 8 * 3.5, 30 * 3.5) ||
		CheckCollision((32 * 3.5) + 148, 183 * 3.5, 8 * 3.5, 22 * 3.5) ||
		CheckCollision((112 * 3.5) + 148, 146 * 3.5, 8 * 3.5, 30 * 3.5) ||
		CheckCollision((184 * 3.5) + 148, 150 * 3.5, 8 * 3.5, 22 * 3.5) ||
		CheckCollision((61 * 3.5) + 148, 100 * 3.5, 8 * 3.5, 41 * 3.5) ||
		CheckCollision((32 * 3.5) + 148, 102 * 3.5, 8 * 3.5, 37 * 3.5) ||
		CheckCollision((184 * 3.5) + 148, 69 * 3.5, 8 * 3.5, 37 * 3.5);

	//std::cout << "Barrel On Ladder " << mBarrelCanGoDown << std::endl;

	mCanJumpScore = CheckCollision(mPlayer->Position().x + 16, mPlayer->Position().y - 16, mPlayer->Position().x + 32, mPlayer->Position().y - 16);

	if (mPlayer->GetCanJump() == false) {
		if (!mBarrelJumped) {
			if (mCanJumpScore) {

				mPlayer->AddScore(100);
				mBarrelJumped = true;
				mStartTimer = 1;
			}
		}
	}

	if (mPlayer->GetDestroyBarrel() == true) {
		mPlayer->AddScore(300);
		mStartTimer = 3;
		mPlayer->SetDestroyBarrel(false);
	}

	StartTimer(1);
	StartTimer(3);

	mCheckIgniteBarrel = CheckCollision(200, 850, 16 * 3.5, 16 * 3.5);

	if (mCheckIgniteBarrel) {
		if (mBarrel->GetVisible() == true) {
			mIgniteBarrel = 2;
			mBarrel->Visible(false);
		}
	}
}

void PlayScreen::Render() {
	mBackground->Render();
	mScoreTexture->Render();
	mItem->Render();
	mItem2->Render();
	mBarrel->Render();
	mPlayer->Render();
	mBarrelStack->Render();
	mDonkeyKong->Render();
	mHighScore->Render();

	Timer(m100, 1);
	Timer(m300, 3);

	if (mPlayer->GetLives() > 0) {
		mLivesTexture->Render();
	}

	if (mIgniteBarrel == 1) {
		mBottomBarrel->Render();
	}
	else if (mIgniteBarrel == 2) {
		mBottomBarrelIgnite->Render();
		mIgniteBarrel = 3;
	}
	else if (mIgniteBarrel == 3) {
		mBottomBarrelFlaming->Render();
	}
}

void PlayScreen::BarrelMove() {

	if (mBarrelCanGoDown) {

		mBarrel->Position(mBarrel->Position().x, mBarrel->Position().y + mBarrelFallSpeed * mTimer->DeltaTime());

		mBarrel->SetBarrelLadder(true);

		if (mBarrel->Position().y > 370) {
			mBarrelMoveSpeed = -160;
			
		}	
		if (mBarrel->Position().y > 490) {
			mBarrelMoveSpeed = 160;
			
		}
		if (mBarrel->Position().y > 615) {
			mBarrelMoveSpeed = -160;
			
		}
		if (mBarrel->Position().y > 699) {
			mBarrelMoveSpeed = 160;
			
		}
		if (mBarrel->Position().y > 830) {
			mBarrelMoveSpeed = -160;
			
		}
	}
	else {
		mBarrel->SetBarrelLadder(false);

		mBarrel->Position(mBarrel->Position().x + mBarrelMoveSpeed * mTimer->DeltaTime(), mBarrel->Position().y);

		if (mDecline) {
			mBarrel->Position(mBarrel->Position().x, mBarrel->Position().y + 9 * mTimer->DeltaTime());
		}
		
		if (mBarrel->Position().y > 275 && mBarrel->Position().x > 620) {
			mDecline = true;
		}
		else if (mBarrel->Position().y > 850 && mBarrel->Position().x < 520) {
			mDecline = false;
		}
	}
}

bool PlayScreen::CheckCollision(float x, float y, float w, float h) {
	float p_left = mBarrel->Position().x;
	float p_right = p_left + 12;
	float p_top = mBarrel->Position().y;
	float p_bottom = p_top + 12;

	float l_left = x;
	float l_right = x + w;
	float l_top = y;
	float l_bottom = y + h;

	return p_right > l_left && p_left < l_right&& p_bottom > l_top && p_top < l_bottom;
}

void PlayScreen::Timer(Texture* other, int timer) {
	if (mStartTimer == timer) {
		if (mScoreTimer != 0) {
			other->Render();
		}
	}
}

void PlayScreen::StartTimer(int timer) {
	if (mStartTimer == timer) {
		mScoreTimer -= mTimer->DeltaTime();

		if (mScoreTimer <= 0) {

			mScoreTimer = 100;
			mStartTimer = 0;
		}
	}
}
