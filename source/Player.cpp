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
  Vect<2, double> vec(0.005, 0.005);
  this->entity.fixture.speed += vec * dir;
}
