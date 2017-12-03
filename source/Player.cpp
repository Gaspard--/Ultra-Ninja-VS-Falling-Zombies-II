#include "Slash.hpp"
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
