#include "MobManager.hpp"

void MobManager::mutation()
{
  std::vector<Human>::iterator bound;

  bound = std::partition(humans.begin(), humans.end(), [](auto const &human)
			 {
			   return !human.getInfected();
			 });
  for (auto it(bound); it != humans.end(); ++it)
    {
      zombies.push_back(*it);
    }
  humans.erase(bound, humans.end());
}
