#include "MobManager.hpp"

void MobManager::update(Physics const &physics)
{
  for (auto &player : players)
    physics.move(player.entity.fixture);
  for (auto &human : humans)
    physics.move(human.entity.fixture);
  for (auto &zombie : zombies)
    physics.move(zombie.entity.fixture);
  physics.quadTree([](auto &, auto &){}, humans, zombies, players);
  mobDeath();
}

void MobManager::mobDeath()
{
  auto bound(std::partition(humans.begin(), humans.end(), [](auto const &human)
			 {
			   return !human.getInfected();
			 }));
  zombies.erase(zombies.begin(), std::remove_if(zombies.begin(), zombies.end(),
						[](auto const &zombie)
						{
						  return zombie.getLife() > 0;
						}));
  for (auto it(bound); it != humans.end(); ++it)
    {
      zombies.push_back(*it);
    }
  humans.erase(bound, humans.end());
}

void MobManager::spawnZombie(Vect<2, double> const& pos)
{
  Entity e({pos, {0.0, 0.0}, 0.1, 0.0, 0.0});

  zombies.emplace_back(e);
}

void MobManager::spawnPlayer(Vect<2, double> const& pos)
{
  if (!players.empty())
    return;
  Entity e({pos, {0.0, 0.0}, 0.1, 0.0, 0.0});

  players.emplace_back(e);
}

Player& MobManager::getPlayer()
{
  return players[0];
}
