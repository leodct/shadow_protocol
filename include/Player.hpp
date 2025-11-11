#ifndef PLAYER_H
#define PLAYER_H

#include "gameObject.hxx"
#include "AnimatedTexture.hxx"

struct PlayerState {
    Vector2 position,
            velocity,
            acceleration;
    
};

class Player : public GameObject{
private:
    PlayerState state;
    AnimatedTexture texture_idle,
                    texture_move,
                    texture_jump,
                    texture_fall;
public:
    Player();
    ~Player();
};

#endif // PLAYER_H