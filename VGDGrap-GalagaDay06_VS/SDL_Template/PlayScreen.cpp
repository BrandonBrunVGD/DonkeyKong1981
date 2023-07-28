#include "PlayScreen.h"
PlayScreen::PlayScreen() {
    mTimer = Timer::Instance();
    mAudio = AudioManager::Instance();
    mBarrelSpawnInterval = 2.0;
    mBarrelSpawnTimer = 0;
    mBarrelJumped = false;
    mTimerLength = 100;
    mStartTimer = "null";
    mIgniteBarrel = 1;
    mBarrelJumpedTimer = 0;
    mBarrelJumpedDelay = 1.0;
    mHelpTimer = 250;
    mToadstoolIdle = true;
    mPlayHelp = false;

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

    mToadstool = new Texture("mario.png", 103, 89, 16, 22);
    mToadstool->Parent(this);
    mToadstool->Position(Graphics::SCREEN_WIDTH * 0.45f, Graphics::SCREEN_HEIGHT * 0.175f);
    mToadstool->Scale(Vector2(3.50f, 3.50f));

    mToadstoolHelp = new AnimatedTexture("mario.png", 103, 89, 16, 22, 3, 0.250f, AnimatedTexture::Horizontal);
    mToadstoolHelp->Parent(this);
    mToadstoolHelp->Position(Graphics::SCREEN_WIDTH * 0.45f, Graphics::SCREEN_HEIGHT * 0.175f);
    mToadstoolHelp->Scale(Vector2(3.50f, 3.05f));
    //mToadstoolHelp->SetWrapMode(AnimatedTexture::Once);

    mHelp = new Texture("mario.png", 224, 94, 23, 8);
    mHelp->Parent(this);
    mHelp->Position(Graphics::SCREEN_WIDTH * 0.53f, Graphics::SCREEN_HEIGHT * 0.12f);
    mHelp->Scale(Vector2(3.50f, 3.50f));

    SpawnBarrel();
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

    // todo: clean up after barrels
    for (auto b : mBarrels) {
        delete b;
    }

    mBarrels.clear();
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

    delete mToadstool;
    mToadstool = nullptr;

    delete mToadstoolHelp;
    mToadstoolHelp = nullptr;

    delete mHelp;
    mHelp = nullptr;
}

void PlayScreen::Update() {
    mBackground->Update();
    mScoreTexture->Update();
    mLivesTexture->Update();
    mItem->Update();
    mItem2->Update();
    mToadstool->Update();
    mToadstoolHelp->Update();
    mHelp->Update();

    mBarrelSpawnTimer += mTimer->DeltaTime();
    if (mBarrelSpawnTimer >= mBarrelSpawnInterval) {
        SpawnBarrel();
        mBarrelSpawnTimer = 0;
    }

    for (auto b : mBarrels) {
        b->Update();
    }

    if (mBarrelJumped = true) {
        mBarrelJumpedTimer += mTimer->DeltaTime();
        if (mBarrelJumpedTimer >= mBarrelJumpedDelay) {
            mBarrelJumped = false;
            mBarrelJumpedTimer = 0;
        }
    }

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

    //std::cout << std::endl << "Barrel Y:  " << mBarrel->Position().y;
    //std::cout << std::endl << "Barrel X:  " << mBarrel->Position().x;

    std::cout << std::endl << "Player Y:  " << mPlayer->Position().y;
    std::cout << std::endl << "Player X:  " << mPlayer->Position().x;

    //std::cout << std::endl << "GroundLevel:   " << mPlayer->GetGroundLevel();
    std::cout << std::endl;

    mCanJumpScore = CheckCollision(mPlayer->Position().x + 16, mPlayer->Position().y - 16, mPlayer->Position().x + 32, mPlayer->Position().y - 16);
    if (mPlayer->GetCanJump() == false) {
        if (!mBarrelJumped) {
            if (mCanJumpScore) {
                mPlayer->AddScore(100);
                mBarrelJumped = true;
                mStartTimer = "100";
            }
        }
    }

    if (mPlayer->GetDestroyBarrel() == true) {
        mPlayer->AddScore(300);
        mStartTimer = "300";
        mPlayer->SetDestroyBarrel(false);
    }

    mCheckIgniteBarrel = CheckCollision(200, 850, 16 * 3.5, 16 * 3.5);

    if (mCheckIgniteBarrel) {
        for (auto b : mBarrels) {
            if (b->GetVisible() == true) {
                mIgniteBarrel = 2;
                b->Visible(false);
            }
        }
    }


    StartTextureTimer(1, "100");
    StartTextureTimer(1, "300");

    mHelpTimer -= mTimer->DeltaTime();
    if (mHelpTimer <= 0) {
        mHelpTimer = 250;
    }
    else if (mHelpTimer <= 50) {
        mPlayHelp = true;
        mToadstoolIdle = false;
    }
    else if (mHelpTimer > 200) {
        mPlayHelp = false;
        mToadstoolIdle = true;
    }
    
}

void PlayScreen::Render() {

    mBackground->Render();
    mScoreTexture->Render();
    mItem->Render();
    mItem2->Render();

    for (auto b : mBarrels) {
        b->Render();
    }

    mPlayer->Render();
    mBarrelStack->Render();
    mDonkeyKong->Render();
    mHighScore->Render();

    
    Timer(m100, "100");
    Timer(m300, "300"); 

    if (mToadstoolIdle) {     
        mToadstool->Render();
    } 

    if (mPlayHelp) {
        mToadstoolHelp->Render();
        mHelp->Render();
    }

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

bool PlayScreen::CheckCollision(float x, float y, float w, float h) {
    bool collision = false;
    for (auto b : mBarrels) {
        float p_left = b->Position().x;
        float p_right = p_left + 12;
        float p_top = b->Position().y;
        float p_bottom = p_top + 12;
        float l_left = x;
        float l_right = x + w;
        float l_top = y;
        float l_bottom = y + h;
        if (p_right > l_left && p_left < l_right && p_bottom > l_top && p_top < l_bottom) {
            collision = true;
            break;
        }
    }
    return collision;
}
void PlayScreen::Timer(Texture* other, std::string timer) {
    if (mStartTimer == timer) {
        if (mTimerLength != 0) {
            other->Render();
        }
    }
}

void PlayScreen::StartTextureTimer(int multiplyer, std::string timer) {
    if (mStartTimer == timer) {
        mTimerLength -= mTimer->DeltaTime();
        if (mTimerLength <= 0) {
            mTimerLength = 100;
            mStartTimer = "null";
        }
    }
}

void PlayScreen::SpawnBarrel() {
    mBarrels.push_back(new Barrel());
    mBarrels.back()->Parent(this);
    mBarrels.back()->Position(Graphics::SCREEN_WIDTH * 0.3f, Graphics::SCREEN_HEIGHT * 0.31f);
    mBarrels.back()->SetTag("Enemy");
}


