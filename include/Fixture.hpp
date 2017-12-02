#ifndef FIXTURE_HPP_
# define FIXTURE_HPP_

# include "Vect.hpp"

struct Fixture
{
  Vect<2, double> pos;
  Vect<2, double> speed;
  double radius;
  double mass;
  double bounciness{0.0};
};

#endif /* !FIXTURE_HPP_ */
