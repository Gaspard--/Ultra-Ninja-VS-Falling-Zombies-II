#pragma once

#include <cmath>

// Add fields to initailise at creation if outside context is needed (such as Logic etc)
struct CollisionSolver
{
  CityMap const &cityMap;

  // Pushes a and b appart.
  template<class T, class U>
  static void solveCollision(T &a, U &b)
  {
    auto middle((a.entity.fixture.pos + b.entity.fixture.pos) * 0.5);
    auto dist(std::sqrt((a.entity.fixture.pos - b.entity.fixture.pos).length2()));
    auto avg(dist * 0.5 + (a.entity.fixture.radius + b.entity.fixture.radius) * 0.5);
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

  // Player should suffer knoback from zombies
  void operator()(Player &a, Zombie &b)
  {
    solveCollision(a, b);
    a.entity.fixture.speed += (a.entity.fixture.pos - b.entity.fixture.pos).normalized() * 0.02;
  }

  // Player should trigger zombie ranges
  void operator()(Player &a, ZombieDetectionRange &b)
  {
    b.affiliated->updateTarget(a.entity, cityMap);
  }

  void operator()(Slash &a, Zombie &b)
  {
    a.hit(b);
  }

  void operator()(Explosion &a, Zombie &b)
  {
    a.hit(b);
  }

  void operator()(Bomb &a, Zombie &)
  {
    a.lifetime = 0;
  }

  void operator()(Shuriken &a, Zombie &b)
  {
    a.hit(b);
    a.lifetime = 0;
  }

  void operator()(Shuriken &a, Human &b)
  {
    a.hit(b);
    a.lifetime = 0;
  }

};
