#ifndef PHYSICS_HPP
# define PHYSICS_HPP

# include "Vect.hpp"
# include "Fixture.hpp"
# include <array>
# include <cmath>
# include <vector>

struct Entity;

# define CAR(x) ((x) * (x))

class Physics
{
public:
  Physics(const Vect<2, int>& planetCenter, double radius, double mass)
    : _planet{planetCenter, Vect<2, int>(0, 0), radius, mass, 0.0} {}

  bool haveCollision(Fixture const&, Fixture const&) const;
  bool haveCollision(Vect<2, int> const& a, Fixture const& b) const;
  void fixMapCollision(Fixture&, std::array<std::array<int/*cityBlock*/, 100>, 100> const& cityMap);
  bool move(Fixture&) const;

  template <class T>
  void updateFixtures(T begin, T end)
  {
    for (T i = begin ; i != end ; ++i)
      (*i)->isOnPlanet = this->move((*i)->fixture);
  }

  /* Planet size getter */
  double getPlanetRadius(void) const;

private:
  const Fixture _planet;
  static const double _G;
};


#endif /* PHYSICS_HPP */
