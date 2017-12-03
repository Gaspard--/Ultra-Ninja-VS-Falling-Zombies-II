#ifndef PLAYER_HPP_
# define PLAYER_HPP_

#include "Entity.hpp"
#include "Zombie.hpp"

class Player
{
public:
  Player(Entity entity);
  ~Player();

  Entity entity;

  void update();

};

#endif //!PLAYER_HPP_
