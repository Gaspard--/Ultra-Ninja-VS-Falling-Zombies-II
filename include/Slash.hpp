#pragma once

#include "Weapon.hpp"
#include "Zombie.hpp"

struct Slash : public Weapon
{
private:
  int animationFrame;
  int maxFrame;
  static constexpr int spriteSheetSize = 5;
  int frameRatio;

public:
  Slash(Vect<2, double> const& pos,
	Vect<2, double> const& speed,
	int damage);
  ~Slash() = default;

  void updateAnimation();

  float getAnimationFrame() const;
};
