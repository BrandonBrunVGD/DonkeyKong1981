#ifndef __BARREL_H
#define __BARREL_H
#include "AnimatedTexture.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "PhysEntity.h"
#include "Player.h"

using namespace SDLFramework;
class Barrel : public PhysEntity {
private:
    Timer* mTimer;
    AudioManager* mAudio;
    Player* mPlayer;

    bool mVisible;
    bool mAnimating;
    int mScore;

    int mRandomNumber;
    //int mRandomLadder;

    //Texture * mMario;
    AnimatedTexture* mBarrel;
    AnimatedTexture* mBarrelLadder;
    float mMoveSpeed;
    Vector2 mMoveBounds;

    //  temporarily public as i bring over functionality from 
    float mBarrelMoveSpeed;
    bool mBarrelCanGoDown;
    bool mBarrelIsGoingDown;
    bool mBarrelShouldGoDown;
    float mBarrelFallSpeed;
    bool mDecline;
    bool mBarrelCanFall;

    Vector2 mBarrelMoveBounds;
   
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
    void BarrelMove();
    void SetBarrelLadder(bool down);
    bool CheckCollision(float x, float y, float w, float h);
    void Update() override;
    void Render() override;       
};
#endif
