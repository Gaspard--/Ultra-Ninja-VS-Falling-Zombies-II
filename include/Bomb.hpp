#pragma once

#include "Weapon.hpp"
#include "Zombie.hpp"

class Bomb : public Weapon
{
private:
  bool explode;

public:
  Bomb(Vect<2, double> const& pos,
       Vect<2, double> const& speed,
       int damage);
  ~Bomb() = default;

  void explosion();

  bool isExploding() const;
};
