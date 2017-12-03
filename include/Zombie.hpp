#ifndef ZOMBIE_HPP_
# define ZOMBIE_HPP_

#include "Mob.hpp"
#include "Human.hpp"

class Human;

class Zombie : public Mob
{
public:
  Zombie(Entity entity);
  Zombie(Human &villager);
  ~Zombie();

  void setLead(bool lead);
  bool const& getLead() const;
  void infectHuman(Human &villager) const;
  void updateTarget(Human&);

private:
  bool lead;
  Human* target;
};

#endif //!ZOMBIE_HPP_
