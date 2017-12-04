#include "EntityManager.hpp"
#include "CollisionSolver.hpp"
#include "Logic.hpp"

void EntityManager::updateWeapons(Physics const &physics, Logic const &logic)
{
  static constexpr auto lifetimeCheck = [](auto &container)
    {
      container.erase(std::remove_if(container.begin(), container.end(),
							[](auto const &elem)
							{
							  return elem.lifetime <= 0;
							}),
		      container.end());
    };
  static auto updateWeapon = [&physics](auto &weaponContainer)
    {
      for (auto &elem : weaponContainer)
	{
	  elem.update();
	  elem.updateAnimation();
	  physics.move(elem.entity.fixture);
	}
    };
  updateWeapon(slashes);
  updateWeapon(bombs);
  updateWeapon(explosions);
  updateWeapon(shurikens);
  lifetimeCheck(slashes);
  lifetimeCheck(explosions);
  for (auto it = bombs.begin(); it != bombs.end();)
    {
      if (it->lifetime <= 0)
	{
	  explosions.emplace_back(Vect<2, double>{it->entity.fixture.pos[0],
				  it->entity.fixture.pos[1]},
				  0.5, 1);
	  explosions.emplace_back(Vect<2, double>{it->entity.fixture.pos[0],
				  it->entity.fixture.pos[1]},
				  0.25, 2);
	  it = bombs.erase(it);
	}
      else
	++it;
    }
  for (auto it = shurikens.begin(); it != shurikens.end();)
    {
      if (it->lifetime <= 0)
	it = shurikens.erase(it);
      else
	++it;
    }

  static auto weaponMapCollision = [&physics, &logic] (auto &weaponContainer)
    {
      for (auto &weapon : weaponContainer)
	{
	  if (physics.haveCollision(weapon.entity.fixture, logic.getCityMap().getCityMap()))
	    {
	      weapon.lifetime = 0;
	    }
	}
    };
  weaponMapCollision(bombs);
  weaponMapCollision(shurikens);
}

void EntityManager::update(Physics const &physics, Logic const &logic, CityMap const &cityMap)
{
  for (auto &player : players)
    player.update();
  for (auto &human : humans)
    human.update();
  std::vector<ZombieDetectionRange> tmpDetectionRanges;

  for (auto &zombie : zombies)
    {
      zombie.updateTarget(getPlayer().entity, cityMap);// TODO delete this
      zombie.update(tmpDetectionRanges);
    }

  for (auto &player : players)
    physics.move(player.entity.fixture);
  for (auto &human : humans)
    physics.move(human.entity.fixture);
  for (auto &zombie : zombies)
    physics.move(zombie.entity.fixture);

  updateWeapons(physics, logic);

  for (auto &player : players)
    physics.fixMapCollision(player.entity.fixture, logic.getCityMap().getCityMap());
  for (auto &human : humans)
    physics.fixMapCollision(human.entity.fixture, logic.getCityMap().getCityMap());
  for (auto &zombie : zombies)
    physics.fixMapCollision(zombie.entity.fixture, logic.getCityMap().getCityMap());

  // for (auto &range : detectionRanges)
  //   if (range.refreshRange())
  //     tmpDetectionRanges.push_back(range);
  {
    CollisionSolver collisionSolver{cityMap};

    physics.quadTree(collisionSolver, players, humans, zombies, tmpDetectionRanges,
		     shurikens, explosions, slashes);
  }
  mobDeath();
}

void EntityManager::mobDeath()
{
  auto bound(std::partition(humans.begin(), humans.end(), [](auto const &human)
			    {
			      return !human.getInfected();
			    }));
  static constexpr auto lifeCheck = [](auto &container)
    {
      container.erase(std::remove_if(container.begin(), container.end(),
							[](auto const &elem)
    {
      return elem.getLife() <= 0;
    }),
		      container.end());
    };

  lifeCheck(zombies);
  for (auto it(bound); it != humans.end(); ++it)
    {
      zombies.push_back(*it);
    }
  humans.erase(bound, humans.end());
  lifeCheck(humans);
}

void EntityManager::spawnHuman(Vect<2, double> const &pos, CityBlock &home)
{
  Entity e({pos, {0.0, 0.0}, 0.062, 0.0, 0.0});

  humans.emplace_back(e, home);
}

void EntityManager::spawnZombie(Vect<2, double> const& pos)
{
  Entity e({pos, {0.0, 0.0}, 0.062, 0.0, 0.0});

  zombies.emplace_back(e);
  detectionRanges.emplace_back(zombies.back());
}

void EntityManager::spawnPlayer(Vect<2, double> const& pos)
{
  if (!players.empty())
    return;
  Entity e({pos, {0.0, 0.0}, 0.062, 0.0, 0.0});

  players.emplace_back(e);
}

Player& EntityManager::getPlayer()
{
  return players[0];
}

Player const& EntityManager::getPlayer() const
{
  return players.at(0);
}
