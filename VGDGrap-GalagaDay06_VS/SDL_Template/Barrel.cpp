#include "Barrel.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

Barrel::Barrel() {
    mTimer = Timer::Instance();
    mAudio = AudioManager::Instance();
    mVisible = true;
    mAnimating = false;
    mScore = 0;

    // from playscreen
    mBarrelMoveSpeed = 160;
    mBarrelCanGoDown = false;
    mBarrelFallSpeed = 60;
    mDecline = false;
    mRandomNumber = rand();
    

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
    // from playscreen
    BarrelMove();
    

    mBarrelCanGoDown = CheckCollision((184 * 3.5) + 148, 216 * 3.5, 8 * 3.5, 22 * 3.5) ||
        CheckCollision((85 * 3.5) + 148, 179 * 3.5, 8 * 3.5, 30 * 3.5) ||
        CheckCollision((32 * 3.5) + 148, 183 * 3.5, 8 * 3.5, 22 * 3.5) ||
        CheckCollision((112 * 3.5) + 148, 146 * 3.5, 8 * 3.5, 30 * 3.5) ||
        CheckCollision((184 * 3.5) + 148, 150 * 3.5, 8 * 3.5, 22 * 3.5) ||
        CheckCollision((61 * 3.5) + 148, 100 * 3.5, 8 * 3.5, 41 * 3.5) ||
        CheckCollision((32 * 3.5) + 148, 102 * 3.5, 8 * 3.5, 37 * 3.5) ||
        CheckCollision((184 * 3.5) + 148, 69 * 3.5, 8 * 3.5, 37 * 3.5);

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

void Barrel::BarrelMove() {
    int RandomLadder;

    if (mBarrelCanGoDown) {
        RandomLadder = (mRandomNumber % 2) + 1;
        if (RandomLadder == 1) {
            Position(Position().x, Position().y + mBarrelFallSpeed * mTimer->DeltaTime());
            SetBarrelLadder(true);
            RandomLadder = 0;
        }  

        if (Position().y > 370) {
            mBarrelMoveSpeed = -160;
        }
        if (Position().y > 490) {
            mBarrelMoveSpeed = 160;
        }
        if (Position().y > 615) {
            mBarrelMoveSpeed = -160;
        }
        if (Position().y > 699) {
            mBarrelMoveSpeed = 160;
        }
        if (Position().y > 830) {
            mBarrelMoveSpeed = -160;
        }
    }
    else {
        SetBarrelLadder(false);

        Position(Position().x + mBarrelMoveSpeed * mTimer->DeltaTime(), Position().y);

        if (mDecline) {
            Position(Position().x, Position().y + 9 * mTimer->DeltaTime());
        }
        if (Position().y > 275 && Position().x > 620) {
            mDecline = true;
        }
        else if (Position().y > 850 && Position().x < 520) {
            mDecline = false;
        }
    }
}

bool Barrel::CheckCollision(float x, float y, float w, float h) {
    float p_left = Position().x;
    float p_right = p_left + 12;
    float p_top = Position().y;
    float p_bottom = p_top + 12;
    float l_left = x;
    float l_right = x + w;
    float l_top = y;
    float l_bottom = y + h;
    return p_right > l_left && p_left < l_right&& p_bottom > l_top && p_top < l_bottom;
}

