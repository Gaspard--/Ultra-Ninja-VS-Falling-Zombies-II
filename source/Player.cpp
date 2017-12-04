#include "Slash.hpp"
#include "Player.hpp"

Player::Player(Entity entity)
  : entity(entity),
    ulti(0.0),
    nbBombs(0),
    slashCooldown(0)
{
}

Player::~Player()
{
}

float Player::getAnimationFrame() const
{
  return anim.getAnimationFrame();
}

void Player::update()
{
  anim.animate(entity);
  slashCooldown -= slashCooldown > 0;
}

void Player::highFive(Human &villager)
{
  constexpr int const cd = 1150;
  unsigned int choice;

  if (!villager.canHighFive())
    return ;
  choice = rand() % 5;
  if (choice < 4)
    ulti += (ulti < 100.0) ? 20.0 : 0.0;
  else if (nbBombs < 5)
    nbBombs += 1;
  villager.setCoolDown(cd);
}

Slash Player::slash()
{
  Slash sl(entity.fixture.pos + entity.fixture.speed.normalized() * 0.1, {0.0, 0.0}, 2);

  slashCooldown = 20;
  return sl;
}

bool Player::canSlash() const
{
  return slashCooldown == 0;
}

void Player::accelerate(Vect<2, int> const& dir)
{
  this->entity.fixture.speed += Vect<2, double>(0.001, 0.001) * dir;
}

void Player::setNbBombs(int nbBombs)
{
  this->nbBombs = nbBombs;
}

int Player::getNbBombs() const
{
  return nbBombs;
}

double Player::getUlti() const
{
  return ulti;
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
