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
  void accelerate(Vect<2, int> const& dir);
  void circleAttack(std::vector<Slash> &);
  int getAnimationFrame() const;

private:
  int animationFrame;
  int internalFrame;
  int maxFrame = 20;

  void setNewAnimationFrame(int stop, int move);
  void animate();
};

#endif //!PLAYER_HPP_
