#include "CityBlock.hpp"
#include "CityMap.hpp"
#include "Logic.hpp"

CityBlock::CityBlock()
  : habMax(0), cooldown(0), type(BlockType::NONE), hab(0), x(0), y(0)
{
}

void CityBlock::update(CityMap const &ref, Logic &logic)
{
  cooldown -= cooldown ? 1 : 0;
  if (hab < habMax && hasNeighbors(ref, x, y) && !cooldown)
    {
      cooldown = REPOP_HAB_CD;
      int newHab(std::min((hab + habMax / 2), habMax) - hab);

      for (int i = 0; i < newHab; i++)
	logic.getEntityManager().spawnHuman({static_cast<double>(x) +
	      (1 / static_cast<double>(newHab)) * (0.5 + i),
	      static_cast<double>(y) - 0.2}, *this);
    }
}

bool CityBlock::upgrade(Logic &logic)
{
  if (static_cast<int>(type) > static_cast<int>(BlockType::HOUSE) || hab != habMax)
    return (false);
  type = static_cast<BlockType>(static_cast<int>(type) + 1);
  habMax = static_cast<int>(type) * 2;
  cooldown = REPOP_HAB_CD;
  logic.getEntityManager().spawnHuman({static_cast<double>(x) +
	1.0 / 3.0,
	static_cast<double>(y) - 0.2}, *this);
  logic.getEntityManager().spawnHuman({static_cast<double>(x) +
	2.0 / 3.0,
	static_cast<double>(y) - 0.2}, *this);
  return (true);
}

bool CityBlock::hasNeighbors(CityMap const &ref, int x, int y)
{
  return ((y > 2 && ref.getCityMap()[y - 2][x].hab) ||
	  (y < MAP_SIZE - 3 && ref.getCityMap()[y + 2][x].hab) ||
	  (x > 2 && ref.getCityMap()[y][x - 2].hab) ||
	  (x > 1 && ref.getCityMap()[y][x - 1].hab) ||
	  (x < MAP_SIZE - 3 && ref.getCityMap()[y][x + 2].hab) ||
	  (x < MAP_SIZE - 2 && ref.getCityMap()[y][x + 1].hab) || hab);
}
