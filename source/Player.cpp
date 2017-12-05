#include "Player.hpp"
#include "Slash.hpp"
#include "Shuriken.hpp"
#include "Bomb.hpp"
#include "SoundHandler.hpp"

Player::Player(Entity entity)
  : entity(entity),
    canHighfive(false),
    ulti(0.0),
    nbBombs(0),
    nbUlti(0),
    slashCooldown(0),
    shurikenCooldown(0),
    bombCooldown(0),
    circleCooldown(0),
    offsetY(0),
    isJumping(false)
{
}

Player::~Player()
{
}

float Player::getAnimationFrame() const
{
  return anim.getAnimationFrame();
}

void Player::handleJump()
{
  constexpr double const maxHeight = 0.05;

  if (isJumping && offsetY < maxHeight)
    offsetY += 0.005;
  if (isJumping && offsetY >= maxHeight)
    isJumping = false;
  if (!isJumping && offsetY > 0)
    offsetY -= 0.005;
}

void Player::update()
{
  handleJump();
  if (!isJumping)
    anim.animate(entity);
  static auto updateCd = [](int &cd) { cd -= cd > 0; };
  updateCd(slashCooldown);
  updateCd(shurikenCooldown);
  updateCd(bombCooldown);
  updateCd(circleCooldown);
}

void Player::highFive(Human &villager)
{
  constexpr int const cd = 1150;
  unsigned int choice;

  if (// !canHighfive ||
      !villager.canHighFive())
    return ;
  isJumping = true;
  villager.isJumping = true;
  choice = rand() % 4;
  if (choice < 3)
    ulti += (ulti < 100.0) ? 20.0 : 0.0;
  else if (nbBombs < 5)
    nbBombs += 1;
  if (ulti >= 100.0 && nbUlti < 5)
    {
      ulti = 0.0;
      nbUlti += 1;
    }
  villager.setCoolDown(cd);
}

double const& Player::getOffset() const
{
  return offsetY;
}

void Player::slash(std::vector<Slash> &slashes)
{
  constexpr int cd = 20;

  if (slashCooldown == 0)
    {
      SoundHandler::getInstance().playSound(SoundHandler::SoundList::DASH, 50);
      slashes.emplace_back(entity.fixture.pos + entity.fixture.speed.normalized() * 0.15,
			   entity.fixture.speed * 0.2, 2);
      slashCooldown = cd;
    }
}

void Player::circleAttack(std::vector<Slash> &slashes)
{
  static constexpr double posOffset = 0.1;
  static constexpr double speed = 0.03;
  static constexpr int iteration = 1;
  constexpr int cd = 20;
  auto &pos = entity.fixture.pos;

  if (circleCooldown > 0 || nbUlti == 0)
    return ;
  nbUlti -= 1;
  circleCooldown = cd;
  SoundHandler::getInstance().playSound(SoundHandler::SoundList::CIRCLE_ATTACK, 60);
  slashes.emplace_back(Vect<2, double>(pos[0], pos[1] - posOffset), Vect<2, double>(0.0, -speed), 2, iteration); // UP
  slashes.emplace_back(Vect<2, double>(pos[0] + posOffset, pos[1] - posOffset), Vect<2, double>(speed, -speed), 2, iteration); // UP RIGHT
  slashes.emplace_back(Vect<2, double>(pos[0] + posOffset, pos[1] - posOffset), Vect<2, double>(speed, -speed), 2, iteration); // UP RIGHT
  slashes.emplace_back(Vect<2, double>(pos[0] + posOffset, pos[1]), Vect<2, double>(speed, 0.0), 2, iteration); // RIGHT
  slashes.emplace_back(Vect<2, double>(pos[0] + posOffset, pos[1] + posOffset), Vect<2, double>(speed, speed), 2, iteration); // DOWN RIGHT
  slashes.emplace_back(Vect<2, double>(pos[0], pos[1] + posOffset), Vect<2, double>(0.0, speed), 2, iteration); // DOWN
  slashes.emplace_back(Vect<2, double>(pos[0] - posOffset, pos[1] + posOffset), Vect<2, double>(-speed, speed), 2, iteration); // DOWN LEFT
  slashes.emplace_back(Vect<2, double>(pos[0] - posOffset, pos[1]), Vect<2, double>(-speed, 0.0), 2, iteration); // LEFT
  slashes.emplace_back(Vect<2, double>(pos[0] - posOffset, pos[1] - posOffset), Vect<2, double>(-speed, -speed), 2, iteration); // UP LEFT
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
  if (shurikenCooldown > 0)
    return ;
  SoundHandler::getInstance().playSound(SoundHandler::SoundList::SHURIKEN, 30);
  shurikens.emplace_back(entity.fixture.pos + entity.fixture.speed.normalized() * 0.1,
			 entity.fixture.speed.normalized() * 0.08, 1);

  shurikenCooldown = /*0;*/15;
}

void Player::accelerate(Vect<2, int> const& dir)
{
  if (((entity.fixture.speed[0] > 0 && dir[0] > 0) ||
      (entity.fixture.speed[0] <= 0 && dir[0] <= 0)) || dir[0] == 0)
    entity.fixture.speed[0] += 0.001 * dir[0];
  else
    entity.fixture.speed[0] = 0.001 * dir[0];

  if (((entity.fixture.speed[1] > 0 && dir[1] > 0) ||
      (entity.fixture.speed[1] <= 0 && dir[1] <= 0)) || dir[1] == 0)
    entity.fixture.speed[1] += 0.001 * dir[1];
  else
    entity.fixture.speed[1] = 0.001 * dir[1];
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

void Player::setNbUlti(int nbUlti)
{
  if (this->nbUlti > 0)
    this->nbUlti = nbUlti;
}

int Player::getNbUlti() const
{
  return nbUlti;
}

double Player::getUlti() const
{
  return ulti;
}
