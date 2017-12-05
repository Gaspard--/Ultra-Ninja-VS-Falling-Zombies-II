#include "EntityManager.hpp"
#include "CollisionSolver.hpp"
#include "Logic.hpp"
#include <random>

EntityManager::EntityManager()
  : rateOfSpawn(500), frame(360)
{

}

void EntityManager::updateSlashes()
{
  static constexpr double posOffset = 0.1;
  static constexpr double speed = 0.03;
  for (auto i = 0lu; i < slashes.size(); ++i)
    {
      if (slashes[i].lifetime <= 0 && slashes[i].getNbLaunch() > 0)
	{
	  auto &pos = slashes[i].entity.fixture.pos;
	  auto nbLaunch = slashes[i].getNbLaunch() - 1;
	  slashes.emplace_back(Vect<2, double>(pos[0], pos[1] - posOffset), Vect<2, double>(0.0, -speed), 2, nbLaunch); // UP
	  slashes.emplace_back(Vect<2, double>(pos[0] + posOffset, pos[1]), Vect<2, double>(speed, 0.0), 2, nbLaunch); // RIGHT
	  slashes.emplace_back(Vect<2, double>(pos[0], pos[1] + posOffset), Vect<2, double>(0.0, speed), 2, nbLaunch); // DOWN
	  slashes.emplace_back(Vect<2, double>(pos[0] - posOffset, pos[1]), Vect<2, double>(-speed, 0.0), 2, nbLaunch); // LEFT
	}
    }
}

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
  updateSlashes();
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
  for (auto &blood : bloods)
    {
      blood.intensity -= 0.001;
    }
  bloods.erase(std::remove_if(bloods.begin(), bloods.end(),
			      [](auto const &elem)
			      {
				return elem.intensity < 0.0;
			      }),
	       bloods.end());
  fleshs.erase(std::remove_if(fleshs.begin(), fleshs.end(),
			      [](auto const &elem)
			      {
				return elem.entity.isUseless;
			      }),
	       fleshs.end());
}

void EntityManager::update(Physics const &physics, Logic const &logic, CityMap const &cityMap)
{
  for (auto &player : players)
    player.update();
  for (auto &human : humans)
    human.update();
  for (auto &flesh : fleshs)
    flesh.update(bloods);
  std::vector<ZombieDetectionRange> tmpDetectionRanges;

  for (auto &zombie : zombies)
    zombie.update(tmpDetectionRanges);

  for (auto &player : players)
    physics.move(player.entity.fixture);
  for (auto &human : humans)
    physics.move(human.entity.fixture);
  for (auto &zombie : zombies)
    physics.move(zombie.entity.fixture);
  for (auto &flesh : fleshs)
    physics.move(flesh.entity.fixture);

  updateWeapons(physics, logic);

  for (auto &player : players)
    physics.fixMapCollision(player.entity.fixture, logic.getCityMap().getCityMap());
  for (auto &human : humans)
    physics.fixMapCollision(human.entity.fixture, logic.getCityMap().getCityMap());
  for (auto &zombie : zombies)
    physics.fixMapCollision(zombie.entity.fixture, logic.getCityMap().getCityMap());
  {
    CollisionSolver collisionSolver{cityMap, bloods};

    physics.quadTree(collisionSolver, players, humans, zombies, tmpDetectionRanges,
		     shurikens, explosions, slashes, bombs);
  }
  mobDeath();
}

void EntityManager::mobDeath()
{
  auto bound(std::partition(humans.begin(), humans.end(), [](auto const &human)
			    {
			      return !human.getInfected();
			    }));
  auto lifeCheck = [this](auto &container)
    {
      for (auto const &contained : container)
	{
	  if (contained.getLife() <= 0)
	    for (int i(0); i < 5; ++i)
	      {
		Vect<2u, float> randOffset(Vect<2u, float>(static_cast<float>(rand() & 255), static_cast<float>(rand() & 255)) - Vect<2u, float>(128.0f, 128.0f));

		fleshs.push_back(Entity({
		      contained.entity.fixture.pos,
			randOffset * 0.0004,
			0.1 * static_cast<double>(rand() % 100) * 0.01,
			0.0}));
	      }
	}
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

  if (humans.size() + zombies.size() >= MaxEntities)
    return ;

  humans.emplace_back(e, home);
}

void EntityManager::spawnZombie(Vect<2, double> const& pos)
{
  Entity e({pos, {0.0, 0.0}, 0.062, 0.0, 0.0});

  // if (humans.size() + zombies.size() >= MaxEntities)
  //   return ;

  zombies.emplace_back(e);
  detectionRanges.emplace_back(zombies.back());
}

static double getRandom(double min, double max) {
  return (max - min) * (static_cast<double>(rand()) / static_cast<double>(RAND_MAX)) + min;
}

void EntityManager::spawnZombies()
{
  if (++frame > rateOfSpawn)
    {
      if (!humans.empty())
	{
	  Vect<2, double> pos(humans.at(rand() % humans.size()).entity.fixture.pos);
	  double rnd = getRandom(-getPlayer().entity.fixture.radius * 10.0,
				 getPlayer().entity.fixture.radius * 10.0);
	  spawnZombie({pos[0] + rnd, pos[1]});
	}
      frame = 0;
    }
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
