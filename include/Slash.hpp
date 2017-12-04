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
  int nbLaunch;
  bool horizontal;
  bool reversed;

public:
  Slash(Vect<2, double> const& pos,
	Vect<2, double> const& speed,
	int damage, int nbLaunch = 0);
  ~Slash() = default;

  void updateAnimation();
  int getNbLaunch() const;

  float getAnimationFrame() const;
  bool isHorizontal() const;
  bool isReversed() const;
};
