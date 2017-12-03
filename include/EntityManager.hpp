#pragma once

#include <vector>
#include <algorithm>

#include "Weapon.hpp"
#include "Slash.hpp"
#include "Explosion.hpp"
#include "Bomb.hpp"
#include "Shuriken.hpp"
#include "Player.hpp"
#include "Human.hpp"
#include "Zombie.hpp"
#include "Vect.hpp"

struct Logic;

class EntityManager
{
public:
  std::vector<Player> players;
  std::vector<Human> humans;
  std::vector<Zombie> zombies;
  std::vector<Slash> slashes;
  std::vector<Bomb> bombs;
  std::vector<Explosion> explosions;
  std::vector<Shuriken> shurikens;

  EntityManager() = default;
  ~EntityManager() = default;

  void updateWeapons(Physics const &physics);
  void update(Physics const &physics, Logic const &logic);
  void mobDeath();
  void spawnHuman(Vect<2, double> const& pos, CityBlock &home);
  void spawnZombie(Vect<2, double> const& pos);
  void spawnPlayer(Vect<2, double> const& pos);
  Player& getPlayer();
  Player const& getPlayer() const;
};
