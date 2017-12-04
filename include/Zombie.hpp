#ifndef ZOMBIE_HPP_
# define ZOMBIE_HPP_

#include <optional>

#include "EntityAnimation.hpp"
#include "Mob.hpp"
#include "Human.hpp"
#include "ZombieDetectionRange.hpp"

class Human;

class Zombie : public Mob
{
public:
  Zombie(Entity const &entity);
  Zombie(Human const &villager);
  ~Zombie();

  void update(std::vector<ZombieDetectionRange> &);
  void setLead(bool lead);
  bool const& getLead() const;
  void infectHuman(Human &villager) const;
  void updateTarget(Entity const&);
  float getAnimationFrame() const;

private:
  EntityAnimation anim;
  bool lead;
  std::optional<Vect<2u, double>> target;
  int detectionCooldown;

  static constexpr int detectionTickBetween()
  {
    return 40;
  }
};

#endif //!ZOMBIE_HPP_
