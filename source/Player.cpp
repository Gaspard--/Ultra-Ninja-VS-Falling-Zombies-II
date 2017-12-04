#include "Player.hpp"
#include "Slash.hpp"
#include "Shuriken.hpp"
#include "Bomb.hpp"

Player::Player(Entity entity)
  : entity(entity),
    ulti(0.0),
    nbBombs(0),
    slashCooldown(0),
    shurikenCooldown(0),
    bombCooldown(0)
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
  static auto updateCd = [](int &cd) { cd -= cd > 0; };
  updateCd(slashCooldown);
  updateCd(shurikenCooldown);
  updateCd(bombCooldown);
}

void Player::highFive(Human &villager)
{
  constexpr int const cd = 10;
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

void Player::slash(std::vector<Slash> &slashes)
{
  constexpr int cd = 20;

  if (slashCooldown == 0)
    {
      slashes.emplace_back(entity.fixture.pos + entity.fixture.speed.normalized() * 0.1,
			   Vect<2, double>{0.0, 0.0}, 2);
      slashCooldown = cd;
    }
}

void Player::circleAttack(std::vector<Slash> &slashes)
{
  constexpr double posOffset = 0.1;
  constexpr double speed = 0.01;
  auto &pos = entity.fixture.pos;

  if (ulti < 100.0)
    return ;
  ulti = 0.0;
      slashes.emplace_back(Vect<2, double>(pos[0], pos[1] - posOffset), Vect<2, double>(0.0, -speed), 2); // UP
      slashes.emplace_back(Vect<2, double>(pos[0] + posOffset, pos[1] - posOffset), Vect<2, double>(speed, -speed), 2); // UP RIGHT
      slashes.emplace_back(Vect<2, double>(pos[0] + posOffset, pos[1]), Vect<2, double>(speed, 0.0), 2); // RIGHT
      slashes.emplace_back(Vect<2, double>(pos[0] + posOffset, pos[1] + posOffset), Vect<2, double>(speed, speed), 2); // DOWN RIGHT
      slashes.emplace_back(Vect<2, double>(pos[0], pos[1] + posOffset), Vect<2, double>(0.0, speed), 2); // DOWN
      slashes.emplace_back(Vect<2, double>(pos[0] - posOffset, pos[1] + posOffset), Vect<2, double>(-speed, speed), 2); // DOWN LEFT
      slashes.emplace_back(Vect<2, double>(pos[0] - posOffset, pos[1]), Vect<2, double>(-speed, 0.0), 2); // LEFT
      slashes.emplace_back(Vect<2, double>(pos[0] - posOffset, pos[1] - posOffset), Vect<2, double>(-speed, -speed), 2); // UP LEFT
}

void Player::bomb(std::vector<Bomb> &bombs)
{
  static constexpr int cd = 40;

  if (nbBombs == 0)
    return ;
  if (bombCooldown == 0)
    {
      bombs.emplace_back(entity.fixture.pos, entity.fixture.speed.normalized() * 0.05, 0);
      nbBombs -= 1;
      bombCooldown = cd;
    }
}

void Player::shuriken(std::vector<Shuriken> &shurikens)
{
  Shuriken s(entity.fixture.pos + entity.fixture.speed.normalized() * 0.1,
	     entity.fixture.speed.normalized() * 0.08, 1);

  shurikens.push_back(s);
  shurikenCooldown = 15;
}

bool Player::canShuriken() const
{
  return shurikenCooldown == 0;
}

void Player::accelerate(Vect<2, int> const& dir)
{
  this->entity.fixture.speed += Vect<2, double>(0.001, 0.001) * dir;
}

void Player::setNbBombs(int nbBombs)
{
  if (this->nbBombs > 0)
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
