#include "CityBlock.hpp"

CityBlock::CityBlock()
  : hab(0), habMax(0), cooldown(0), type(BlockType::NONE), x(0), y(0)
{
}

void CityBlock::tick(/*Logic &logic*/)
{
  cooldown -= (cooldown != 0);
  if (hab != habMax and !cooldown)
    {
      int newHab((hab + habMax / 2) % habMax);

      // createCitizen(newHab - hab)
      hab = newHab;
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

BlockType CityBlock::getType() const
{
  return (type);
}
