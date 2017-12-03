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

void Player::setNewAnimationFrame(int stop, int move, int move2)
{
  if (animationFrame != stop && animationFrame != move && animationFrame != move2)
    animationFrame = stop;
  else if (++internalFrame > maxFrame)
    {
      internalFrame = 0;
      if (animationFrame == move)
	animationFrame = move2;
      else
	animationFrame = move;
    }
}

void Player::animate()
{
  if (entity.fixture.speed[0] <= 0.005 && entity.fixture.speed[0] >= -0.005 &&
      entity.fixture.speed[1] <= 0.005 && entity.fixture.speed[1] >= -0.005)
    {
      switch (animationFrame) {
      case 0 ... 1:
	animationFrame = 0;
	break;
      case 2 ... 4:
	animationFrame = 2;
	break;
      case 5 ... 7:
	animationFrame = 5;
	break;
      case 8 ... 9:
	animationFrame = 8;
	break;
      }
      return;
    }

  // x axis animation
  if (abs(entity.fixture.speed[0]) > abs(entity.fixture.speed[1]))
    {
      // check right side animation
      if (entity.fixture.speed[0] > 0)
	setNewAnimationFrame(8, 9);
      else
	setNewAnimationFrame(0, 1);
    }
  // y axis animation
  else
    {
      // check up side animation
      if (entity.fixture.speed[1] > 0)
	setNewAnimationFrame(5, 6, 7);
      else
	setNewAnimationFrame(2, 3, 4);
    }
}

void Player::update()
{
  animate();
}

void Player::accelerate(Vect<2, int> const& dir)
{
  this->entity.fixture.speed += Vect<2, double>(0.005, 0.005) * dir;
}
