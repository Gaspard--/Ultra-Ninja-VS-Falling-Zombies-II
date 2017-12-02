#ifndef ZOMBIE_HPP_
# define ZOMBIE_HPP_

#include "Mob.hpp"
#include "Human.hpp"

class Zombie : public Mob
{
public:
  Zombie(Entity entity);
  Zombie(Human &villager);
  ~Zombie();

  void setLead(bool lead);
  bool const& getLead() const;

private:
  bool lead;
};

#endif //!ZOMBIE_HPP_

