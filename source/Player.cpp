#include "Player.hpp"

Player::Player(Entity entity)
  : entity(entity), animationFrame(2), internalFrame(0)
{
}

Player::~Player()
{
}

int Player::getAnimationFrame() const
{
  return animationFrame;
}

void Player::setNewAnimationFrame(int stop, int move)
{
  if (animationFrame != stop && animationFrame != move)
    animationFrame = stop;
  else if (++internalFrame > maxFrame)
    {
      internalFrame = 0;
      animationFrame = animationFrame == move ? stop : move;
    }
}

void Player::animate()
{
  if (entity.fixture.speed[0] <= 0.005 && entity.fixture.speed[0] >= -0.005 &&
      entity.fixture.speed[1] <= 0.005 && entity.fixture.speed[1] >= -0.005)
    {
      animationFrame -= (animationFrame % 2 != 0);
      return;
    }
  // x axis animation
  if (abs(entity.fixture.speed[0]) > abs(entity.fixture.speed[1]))
    {
      // check right side animation
      if (entity.fixture.speed[0] > 0)
	setNewAnimationFrame(6, 7);
      else
	setNewAnimationFrame(0, 1);
    }
  // y axis animation
  else
    {
      // check up side animation
      if (entity.fixture.speed[1] > 0)
	setNewAnimationFrame(5, 4);
      else
	setNewAnimationFrame(3, 2);
    }
}

void Player::update()
{
  animate();
}

void Player::accelerate(Vect<2, int> const& dir)
{
  this->entity.fixture.speed += Vect<2, double>(0.0005, 0.0005) * dir;
}
