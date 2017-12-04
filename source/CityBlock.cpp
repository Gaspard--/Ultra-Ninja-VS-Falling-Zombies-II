#include "CityBlock.hpp"
#include "CityMap.hpp"
#include "Logic.hpp"

CityBlock::CityBlock()
  : habMax(0), type(BlockType::NONE), hab(0), x(0), y(0)
{
}

void CityBlock::update(CityMap const &ref, Logic &logic)
{
  /*
  bool a(hasNeighbors(ref, x, y));

  if (habMax)
    std::cout << hab << " " << habMax << " " << a << std::endl;
  if (hab != habMax && a)
    {
      int newHab(((hab + habMax / 2) % habMax) - hab);

      for (int i = 0; i < newHab; i++)
	logic.getEntityManager().spawnHuman({static_cast<double>(x) +
	      (1 / static_cast<double>(newHab)) * (0.5 + i),
	      static_cast<double>(y) - 0.2}, *this);
      hab = (hab + newHab) % habMax;
      }*/
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
  type = static_cast<BlockType>(static_cast<int>(type) + 1);
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
