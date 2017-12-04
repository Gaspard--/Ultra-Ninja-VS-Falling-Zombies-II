#include <stdlib.h>
#include "Mob.hpp"
#include "CityBlock.hpp"

Mob::Mob(Entity entity, int life)
  : entity(entity),
    life(life),
    offsetY(0)
{
}

Mob::~Mob()
{
}

void Mob::setLife(int life)
{
  this->life = life;
}

int const& Mob::getLife() const
{
  return life;
}

Vect<2, double> Mob::findPath(Entity const &target, CityMap const &cityMap) const
{
  auto map(cityMap.getCityMap());
  Vect<2, int> selfpos(static_cast<int>(entity.fixture.pos[0]),
		       static_cast<int>(entity.fixture.pos[1]));
  Vect<2, double> targetpos(entity.fixture.pos[0], entity.fixture.pos[1]);
  Vect<2, int> dist(static_cast<int>(target.fixture.pos[0]) - selfpos[0],
		    static_cast<int>(target.fixture.pos[1]) - selfpos[1]);
  Vect<2, int> dir(dist[0] > 0 ? 1 : dist[0] < 0 ? -1 : 0,
		   dist[1] > 0 ? 1 : dist[1] < 0 ? -1 : 0);
  Vect<2, BlockType> blk(map[selfpos[1]][selfpos[0] + dir[0]].type,
			 map[selfpos[1] + dir[1]][selfpos[0]].type);

  dist[0] = abs(dist[0]);
  dist[1] = abs(dist[1]);
  if (!dir[0] || !dir[1])
    return (Vect<2, double>(target.fixture.pos[0], target.fixture.pos[1]));
  auto findTarget = [&selfpos, &targetpos, &dist, &dir, &blk, &map](int i, int j)
    {
      while ((blk[i] == BlockType::ROAD || blk[i] == BlockType::NONE) &&
	     (dist[i] > dist[j] || !(blk[j] == BlockType::ROAD || blk[j] == BlockType::NONE)))
	{
	  blk[0] = map[selfpos[1]][selfpos[0] + dir[0]].type;
	  blk[1] = map[selfpos[1] + dir[1]][selfpos[0]].type;
	  selfpos[i] += dir[i];
	  targetpos[i] += static_cast<double>(dir[i]);
	  dist[i] -= 1;
	}
    };
  if (dist[0] > dist[1] && (blk[0] == BlockType::ROAD || blk[0] == BlockType::NONE))
    {
      findTarget(0, 1);
      targetpos[0] += static_cast<double>(dir[0] < 0) * 0.6 + 0.2;
      targetpos[1] += static_cast<double>(dir[1] > 0) * 0.6 + 0.2;
    }
  else
    {
      findTarget(1, 0);
      targetpos[0] += static_cast<double>(dir[0] > 0) * 0.6 + 0.2;
      targetpos[1] += static_cast<double>(dir[1] < 0) * 0.6 + 0.2;
    }
  return (Vect<2, double>(targetpos[0], targetpos[1]));
}

void Mob::setOffset(double offsetY)
{
  this->offsetY = offsetY;
}

double const& Mob::getOffset() const
{
  return offsetY;
}
