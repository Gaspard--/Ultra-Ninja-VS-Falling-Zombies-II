#ifndef MOB_HPP_
# define MOB_HPP_

#include "Entity.hpp"

class Mob
{
public:
  Mob(Entity entity, int life);
  ~Mob();

  Entity entity;

  void setLife(int life);
  int const& getLife() const;

  void setOffset(double offsetY);
  double const& getOffset() const;

  bool isJumping;

protected:
  int life;
  double offsetY;
};

#endif //!MOB_HPP_
