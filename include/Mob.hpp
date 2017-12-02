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

private:
  int life;
  //ref Maison
};

#endif //!MOB_HPP_
