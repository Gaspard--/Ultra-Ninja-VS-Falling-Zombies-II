#pragma once

#include "Weapon.hpp"

struct Shuriken : public Weapon
{
private:
  int animationFrame;
  static constexpr int spriteSheetSize = 2;

  int maxFrame;
  int nbFrames;
public:

  Shuriken(Vect<2, double> const& pos,
	   Vect<2, double> const& speed,
	   int damage);
  ~Shuriken() = default;

  void updateAnimation();

  float getAnimationFrame() const;
};
