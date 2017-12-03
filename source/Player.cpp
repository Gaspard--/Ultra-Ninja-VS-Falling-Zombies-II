#include "Player.hpp"

Player::Player(Entity entity)
  : entity(entity),
    ulti(0.0),
    nbBombs(0)
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
