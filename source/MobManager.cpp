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

void MobManager::update(Physics const &physics)
{
  for (auto &human : humans)
    physics.move(human.entity.fixture);
  for (auto &zombie : zombies)
    physics.move(zombie.entity.fixture);
  physics.quadTree([](auto &, auto &){}, humans, zombies);
}
