#pragma once

#include "Weapon.hpp"
#include "Zombie.hpp"

class Bomb : public Weapon
{
private:
  int animationFrame;
  int maxFrame;
  static constexpr int spriteSheetSize = 5;
  int frameRatio;

public:
  Bomb(Vect<2, double> const& pos,
       Vect<2, double> const& speed,
       int damage);
  ~Bomb() = default;

  void updateAnimation();

  float getAnimationFrame() const;
};
