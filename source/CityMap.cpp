#include "CityMap.hpp"

CityMap::CityMap()
{
  int x, y;

  y = 0;
  for (auto &line : cityMap)
    {
      x = 0;
      for (auto &block : line)
	{
	  block.x = x;
	  block.y = y;
	  if (!y || (y == MAP_SIZE - 1))
	    block.type = BlockType::BORDER;
	  else if (!x || (x == MAP_SIZE - 1))
	    block.type = BlockType::BORDER;
	  else if (!(y % 2))
	    block.type = BlockType::ROAD;
	  else
	    {
	      if ((x - 1) % 4)
		block.type = BlockType::NONE;
	      else
		block.type = BlockType::ROAD;
	    }
	  x += 1;
	}
      y += 1;
    }
  /*
  for (auto &line : cityMap)
    {
      for (auto &block : line)
	if (block.type == BlockType::BORDER)
	  std::cout << 'X';
	else if (block.type == BlockType::ROAD)
	  std::cout << '.';
	else if (block.type == BlockType::NONE)
	  std::cout << 'O';
      std::cout << std::endl;
    }
  */
}

void CityMap::tick(/*Logic &logic*/)
{
  cooldown -= (cooldown != 0);
  if (cooldown)
    return;
  /*cooldown = HOUSE_SPAWN_CD;*/
  for (auto &line : cityMap)
    for (auto &block : line)
      {
	block.tick(/*logic*/);
	if (block.type != BlockType::ROAD)
	  {
	    int newHouse = std::rand() % 100;

	    if (newHouse < HOUSE_SPAWN_RATE)
	      {
		int count = 0;
		bool search = true;

		while (search && count < 3)
		  {
		    switch(std::rand() % 6)
		      {
		      case 0:
			if (block.x > 1)
			  search = cityMap[block.y][block.x - 2].upgrade(/*logic*/);
			break;
		      case 1:
			if (block.x < (MAP_SIZE - 2))
			  search = cityMap[block.y][block.x + 2].upgrade(/*logic*/);
			break;
		      case 2:
			if (block.y > 1)
			  search = cityMap[block.y - 2][block.x].upgrade(/*logic*/);
			break;
		      case 3:
			if (block.y < (MAP_SIZE - 2))
			  search = cityMap[block.y + 2][block.x].upgrade(/*logic*/);
			break;
		      case 4:
			search = cityMap[block.y][block.x - 1].upgrade(/*logic*/);
			break;
		      case 5:
			search = cityMap[block.y][block.x + 1].upgrade(/*logic*/);
			break;
		      default:
			break;
		      }
		    count += 1;
		  }
	      }
	  }
      }
}

std::array<std::array<CityBlock, MAP_SIZE>, MAP_SIZE> const &CityMap::getCityMap() const
{
  return (cityMap);
}
