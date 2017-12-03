#pragma once

# include "Weapon.hpp"

class Explosion : public Weapon
{
private:

public:
  Explosion(Vect<2, double> const& pos,
	    double radius,
	    int damage);

  void updateAnimation();
};
