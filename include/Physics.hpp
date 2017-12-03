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
  Physics() = default;

  bool haveCollision(Fixture const&, Fixture const&) const;
  bool haveCollision(Vect<2, int> const& a, Fixture const& b) const;
  void fixMapCollision(Fixture&, std::array<std::array<int/*cityBlock*/, 100>, 100> const& cityMap);
  void move(Fixture&) const;

private:
  static constexpr const double G{6.67384 * pow(10.0, -11.0)};
};


#endif /* PHYSICS_HPP */
