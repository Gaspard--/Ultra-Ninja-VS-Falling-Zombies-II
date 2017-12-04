#ifndef MOB_HPP_
# define MOB_HPP_

#include "Entity.hpp"
#include "Vect.hpp"

class Mob
{
public:
  Mob(Entity entity, int life);
  ~Mob();

  Entity entity;

  void setLife(int life);
  int const& getLife() const;
  Vect<2, double> findPath(Entity const &, CityMap const &) const;

protected:
  int life;
};

#endif //!MOB_HPP_
