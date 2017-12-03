#include <cstdlib>
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
	  x += 1;
	}
      y += 1;
    }
}

void CityMap::tick(/*Logic &logic*/)
{
  cooldown -= (cooldown != 0);
  if (cooldown)
    return;
  for (auto &line : cityMap)
    for (auto &block : line)
      {
	block.tick(/*logic*/);
	if (block.getType() != BlockType::ROAD)
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
		      }
		  }
	      }
	  }
      }
}
