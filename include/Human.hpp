#ifndef HUMAN_HPP_
# define HUMAN_HPP_

# include <vector>

#include "Mob.hpp"
#include "CityBlock.hpp"
# include "Zombie.hpp"

class Zombie;

class Human : public Mob
{
public:
  Human(Entity entity, CityBlock &home);
  ~Human();

  void setInfected(bool infected);
  bool const& getInfected() const;
  CityBlock const &getHome() const;

  void addHunter(Zombie&);
  void removeHunter(Zombie&);

private:
  CityBlock &getHome();
  bool infected;
  CityBlock *homePtr;

  std::vector<Zombie*>	hunters;

};

#endif //!HUMAN_HPP_
