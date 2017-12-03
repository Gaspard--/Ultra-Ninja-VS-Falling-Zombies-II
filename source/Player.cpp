#include "Slash.hpp"
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
  this->entity.fixture.speed += Vect<2, double>(0.005, 0.005) * dir;
}

void Player::circleAttack(std::vector<Slash> &slashes)
{
  static constexpr double posOffset = 0.1;
  static constexpr double speed = 0.01;
  auto &pos = entity.fixture.pos;

  slashes.emplace_back(Vect<2, double>(pos[0], pos[1] - posOffset), Vect<2, double>(0.0, -speed), 2); // UP
  slashes.emplace_back(Vect<2, double>(pos[0] + posOffset, pos[1] - posOffset), Vect<2, double>(speed, -speed), 2); // UP RIGHT
  slashes.emplace_back(Vect<2, double>(pos[0] + posOffset, pos[1]), Vect<2, double>(speed, 0.0), 2); // RIGHT
  slashes.emplace_back(Vect<2, double>(pos[0] + posOffset, pos[1] + posOffset), Vect<2, double>(speed, speed), 2); // DOWN RIGHT
  slashes.emplace_back(Vect<2, double>(pos[0], pos[1] + posOffset), Vect<2, double>(0.0, speed), 2); // DOWN
  slashes.emplace_back(Vect<2, double>(pos[0] - posOffset, pos[1] + posOffset), Vect<2, double>(-speed, speed), 2); // DOWN LEFT
  slashes.emplace_back(Vect<2, double>(pos[0] - posOffset, pos[1]), Vect<2, double>(-speed, 0.0), 2); // LEFT
  slashes.emplace_back(Vect<2, double>(pos[0] - posOffset, pos[1] - posOffset), Vect<2, double>(-speed, -speed), 2); // UP LEFT
}
