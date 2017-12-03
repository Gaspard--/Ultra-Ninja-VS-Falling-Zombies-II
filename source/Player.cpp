#include "Player.hpp"

Player::Player(Entity entity)
  : entity(entity)
{
}

Player::~Player()
{
}

void Player::update()
{
}

void Player::accelerate(Vect<2, int> const& dir)
{
  this->entity.fixture.speed += Vect<2, double>(0.005, 0.005) * dir;
}
