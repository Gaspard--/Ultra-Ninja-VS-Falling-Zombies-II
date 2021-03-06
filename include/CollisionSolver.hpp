#pragma once

#include <cmath>

// Add fields to initailise at creation if outside context is needed (such as Logic etc)
struct CollisionSolver
{
  CityMap const &cityMap;
  std::vector<Blood> &bloods;

  // Pushes a and b appart.
  template<class T, class U>
  static void solveCollision(T &a, U &b)
  {
    auto middle((a.entity.fixture.pos + b.entity.fixture.pos) * 0.5);
    auto avg((a.entity.fixture.radius + b.entity.fixture.radius) * 1.1);
    auto dir((a.entity.fixture.pos - b.entity.fixture.pos).normalized() * avg * 0.5);

    a.entity.fixture.pos = middle + dir;
    b.entity.fixture.pos = middle - dir;
  }

  // default case
  template<class T, class U>
  void operator()(T &, U &)
  {
    // Do nothing
  }

  // Zombies should push themselves back
  void operator()(Zombie &a, Zombie &b)
  {
    solveCollision(a, b);
  }

  // Humans should push themselves back
  void operator()(Human &a, Human &b)
  {
    solveCollision(a, b);
  }

  void operator()(Zombie &a, Human &b)
  {
    if (!a.getIsFalling())
      a.infectHuman(b);
  }

  // Player should suffer knoback from zombies
  void operator()(Player &a, Zombie &b)
  {
    solveCollision(a, b);
    a.entity.fixture.speed += (a.entity.fixture.pos - b.entity.fixture.pos).normalized() * 0.02;
  }

  void operator()(Player &a, Human &b)
  {
    // b.canHighfive = true;
    a.highFive(b);
  }

  // Player should trigger zombie ranges
  void operator()(Player &a, ZombieDetectionRange &b)
  {
    b.affiliated->updateTarget(a.entity, cityMap);
  }

  // Human should trigger zombie ranges
  void operator()(Human &a, ZombieDetectionRange &b)
  {
    if (b.affiliated->updateTarget(a.entity, cityMap))
      a.beScaredOf(b.entity.fixture.pos);
  }

  void operator()(Slash &a, Zombie &b)
  {
    for (int i(0); i < 5; ++i)
      Blood::spawnBlood(bloods, b.entity.fixture.pos, a.entity.fixture.speed);
    a.hit(b);
  }

  void operator()(Slash &a, Human &b)
  {
    for (int i(0); i < 5; ++i)
      Blood::spawnBlood(bloods, b.entity.fixture.pos, a.entity.fixture.speed);
    a.hit(b);
  }

  void operator()(Explosion &a, Zombie &b)
  {
    for (int i(0); i < 5; ++i)
      Blood::spawnBlood(bloods, b.entity.fixture.pos, a.entity.fixture.speed);
    a.hit(b);
  }

  void operator()(Explosion &a, Human &b)
  {
    for (int i(0); i < 5; ++i)
      Blood::spawnBlood(bloods, b.entity.fixture.pos, a.entity.fixture.speed);
    a.hit(b);
  }

  void operator()(Bomb &a, Zombie &)
  {
    a.lifetime = 0;
  }

  void operator()(Bomb &a, Human &)
  {
    a.lifetime = 0;
  }

  void operator()(Shuriken &a, Zombie &b)
  {
    for (int i(0); i < 1; ++i)
      Blood::spawnBlood(bloods, b.entity.fixture.pos, {0.0, 0.0});
    a.hit(b);
    a.lifetime = 0;
  }

  void operator()(Shuriken &a, Human &b)
  {
    for (int i(0); i < 1; ++i)
      Blood::spawnBlood(bloods, b.entity.fixture.pos, {0.0, 0.0});
    a.hit(b);
    a.lifetime = 0;
  }
};
