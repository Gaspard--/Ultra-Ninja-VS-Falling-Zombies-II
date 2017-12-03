#pragma once

#include "Weapon.hpp"
#include "Zombie.hpp"

struct Slash : public Weapon
{
private:
  int animationFrame;
  int const maxFrame;
  static constexpr spriteSheetSize = 5;
  int const

public:
  Slash(Vect<2, double> const& pos,
	Vect<2, double> const& speed,
	int damage);
  ~Slash() = default;

  void update();

  int getAnimationFrame() const;
};
