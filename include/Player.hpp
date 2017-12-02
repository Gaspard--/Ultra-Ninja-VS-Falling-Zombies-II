#ifndef PLAYER_HPP_
# define PLAYER_HPP_

#include "Entity.hpp"

class Player
{
public:
  Player();
  ~Player();

  Entity entity;

  void attack();
  void update();

};

#endif //!PLAYER_HPP_
