#include "player.h"
#include "Constants.h"
Player::Player()
{
    player = 1;
}
void Player::setPlayer(int player)
{
    this->player = player;
}

int Player::getPlayer()
{
    return this->player;
}
