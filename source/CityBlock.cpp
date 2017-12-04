#include "CityBlock.hpp"
#include "CityMap.hpp"
#include "Logic.hpp"

CityBlock::CityBlock()
  : hab(0), habMax(0), cooldown(0), type(BlockType::NONE), x(0), y(0)
{
}

void CityBlock::tick(CityMap const &ref, Logic &logic)
{
  cooldown -= (cooldown != 0);
  if (hab != habMax && !cooldown && hasNeighbors(ref, x, y))
    {
      int newHab((hab + habMax / 2) % habMax);

      hab = newHab;
      for (int i = 0; i < newHab - hab; i++)
	logic.getEntityManager().spawnHuman({static_cast<double>(x) +
	      (1 / static_cast<double>(hab)) * (0.5 + i),
	      static_cast<double>(y) - 0.2}, *this);
      cooldown = REPOP_HAB_CD;
    }
}

bool CityBlock::upgrade(Logic &logic)
{
  if (static_cast<int>(type) > static_cast<int>(BlockType::HOUSE) || hab != habMax)
    return (false);
  habMax += 2;
  hab = habMax;
  logic.getEntityManager().spawnHuman({static_cast<double>(x) +
	1.0 / 3.0,
	static_cast<double>(y) - 0.2}, *this);
  logic.getEntityManager().spawnHuman({static_cast<double>(x) +
	2.0 / 3.0,
	static_cast<double>(y) - 0.2}, *this);
  cooldown = REPOP_HAB_CD;
  type = static_cast<BlockType>(static_cast<int>(type) + 1);
  return (true);
}

bool CityBlock::hasNeighbors(CityMap const &ref, int x, int y)
{
  return ((y > 2 && ref.getCityMap()[y - 2][x].getHab()) ||
	  (y < MAP_SIZE - 3 && ref.getCityMap()[y + 2][x].getHab()) ||
	  (x > 2 && ref.getCityMap()[y][x - 2].getHab()) ||
	  (x > 1 && ref.getCityMap()[y][x - 1].getHab()) ||
	  (x < MAP_SIZE - 3 && ref.getCityMap()[y][x + 2].getHab()) ||
	  (x < MAP_SIZE - 2 && ref.getCityMap()[y][x + 1].getHab()));
}

int CityBlock::getHab() const
{
  return (hab);
}
