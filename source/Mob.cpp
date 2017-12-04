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
  Vect<2, double> tmppos(entity.fixture.pos);
  Vect<2, double> directPath((target.fixture.pos - entity.fixture.pos).normalized());
  Vect<2, double> targetpos(entity.fixture.pos[0], entity.fixture.pos[1]);
  Vect<2, int> dist(static_cast<int>(target.fixture.pos[0]) - selfpos[0],
		    static_cast<int>(target.fixture.pos[1]) - selfpos[1]);
  Vect<2, int> dir(dist[0] > 0 ? 1 : dist[0] < 0 ? -1 : 0,
		   dist[1] > 0 ? 1 : dist[1] < 0 ? -1 : 0);
  Vect<2, BlockType> blk(map[selfpos[1]][selfpos[0] + dir[0]].type,
			 map[selfpos[1] + dir[1]][selfpos[0]].type);

  /*
  dist[0] = abs(dist[0]);
  dist[1] = abs(dist[1]);
  std::cout << "TEST" << std::endl;
  while (static_cast<int>(tmppos[0]) != static_cast<int>(target.fixture.pos[0]) ||
	 static_cast<int>(tmppos[1]) != static_cast<int>(target.fixture.pos[1]))
    {
      BlockType tmpBlk(map[static_cast<int>(tmppos[1])][static_cast<int>(tmppos[0])].type);

      std::cout << tmppos[0] << " " << tmppos[1] << std::endl;
      std::cout << target.fixture.pos[0] << " " << target.fixture.pos[1] << std::endl;
      std::cout << directPath[0] << " " << directPath[1] << std::endl;
      if (tmpBlk != BlockType::ROAD && tmpBlk != BlockType::NONE)
	break;
      tmppos[0] += directPath[0];
      tmppos[1] += directPath[1];
    }
  if (static_cast<int>(tmppos[0]) == static_cast<int>(target.fixture.pos[0]) &&
    static_cast<int>(tmppos[1]) == static_cast<int>(target.fixture.pos[1]))*/
    return (target.fixture.pos +
	    Vect<2, double>(static_cast<double>(dir[0]), static_cast<double>(dir[1])));
  /*selfpos = {static_cast<int>(tmppos[0]), static_cast<int>(tmppos[1])};
  targetpos = {static_cast<int>(tmppos[0]), static_cast<int>(tmppos[1])};
  dist = {static_cast<int>(target.fixture.pos[0]) - selfpos[0],
	  static_cast<int>(target.fixture.pos[1]) - selfpos[1]};
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
      targetpos[0] += static_cast<double>(dir[0] < 0) * 0.8 + 0.1;
      targetpos[1] += static_cast<double>(dir[1] > 0) * 0.8 + 0.1;
    }
  else
    {
      findTarget(1, 0);
      targetpos[0] += static_cast<double>(dir[0] > 0) * 0.8 + 0.1;
      targetpos[1] += static_cast<double>(dir[1] < 0) * 0.8 + 0.1;
    }
    return (Vect<2, double>(targetpos[0], targetpos[1]));*/
}

void Mob::setOffset(double offsetY)
{
  this->offsetY = offsetY;
}

double const& Mob::getOffset() const
{
  return offsetY;
}
