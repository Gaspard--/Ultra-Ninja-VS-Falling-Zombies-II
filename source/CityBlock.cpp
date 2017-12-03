#include "CityBlock.hpp"
#include "CityMap.hpp"

CityBlock::CityBlock()
  : hab(0), habMax(0), cooldown(0), type(BlockType::NONE), x(0), y(0)
{
}

void CityBlock::tick(CityMap const &ref/*, Logic &logic*/)
{
  cooldown -= (cooldown != 0);
  if (hab != habMax && !cooldown && hasNeighbors(ref, x, y))
    {
      int newHab((hab + habMax / 2) % habMax);

      // createCitizen(newHab - hab)
      hab = newHab;
      cooldown = REPOP_HAB_CD;
    }
}

bool CityBlock::upgrade(/*Logic &logic*/)
{
  if (static_cast<int>(type) > static_cast<int>(BlockType::HOUSE) || hab != habMax)
    return (false);
  habMax += 2;
  // createCitizen(2)
  hab = habMax;
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
