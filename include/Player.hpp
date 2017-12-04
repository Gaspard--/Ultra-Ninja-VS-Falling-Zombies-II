#ifndef PLAYER_HPP_
# define PLAYER_HPP_

#include "Zombie.hpp"
#include "Human.hpp"
#include "EntityAnimation.hpp"
#include "Shuriken.hpp"
#include "Slash.hpp"

class Bomb;

class Player
{
public:
  Player(Entity entity);
  ~Player();

  Entity entity;

  void update();
  void accelerate(Vect<2, int> const& dir);
  float getAnimationFrame() const;

  void highFive(Human &villager);
  // dir[0] = x axis , dir[1] = y axis
  void setNbBombs(int nbBombs);
  int getNbBombs() const;
  void setUlti(double ulti);
  double getUlti() const;

  void slash(std::vector<Slash> &slashes);
  void circleAttack(std::vector<Slash> &slashes);
  void bomb(std::vector<Bomb> &bombs);

  void shuriken(std::vector<Shuriken> &shurikens);
  bool canShuriken() const;

private:
  EntityAnimation anim;
  double ulti;
  int nbBombs;

  int slashCooldown;
  int shurikenCooldown;
  int bombCooldown;
};

#endif //!PLAYER_HPP_
