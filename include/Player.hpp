#ifndef PLAYER_HPP_
# define PLAYER_HPP_

#include "Entity.hpp"
#include "Zombie.hpp"

class Slash;

class Player
{
public:
  Player(Entity entity);
  ~Player();

  Entity entity;

  void update();
  // dir[0] = x axis , dir[1] = y axis
  void accelerate(Vect<2, int> const& dir);
  void circleAttack(std::vector<Slash> &);
};

#endif //!PLAYER_HPP_
