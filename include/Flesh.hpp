#pragma once

# include "Entity.hpp"
# include "Blood.hpp"

class Flesh
{
public:
  double yOffset;
  double ySpeed;
  Entity entity;
  int type;

  Flesh(Entity const &entity)
    : yOffset(0.0),
      ySpeed(0.007),
      entity(entity),
      type(rand() % 3)
  {}

  ~Flesh() = default;

  void update(std::vector<Blood> &bloods)
  {
    yOffset += ySpeed;
    ySpeed -= 0.0005;
    if (yOffset < 0.0)
      {
	for (int i(0); i < 2; ++i)
	  {
	    Blood::spawnBlood(bloods, entity.fixture.pos, entity.fixture.speed);
	  }
	yOffset = 0.0;
	ySpeed *= -0.7;
	if (ySpeed < 0.005)
	  entity.isUseless = true;
      }
  }
};
