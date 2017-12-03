#ifndef HUMAN_HPP_
# define HUMAN_HPP_

#include "Mob.hpp"
#include "CityBlock.hpp"

class Human : public Mob
{
public:
  Human(Entity entity, CityBlock &home);
  ~Human();

  void setInfected(bool infected);
  bool const& getInfected() const;
  CityBlock const &getHome() const;

private:
  CityBlock &getHome();
  bool infected;
  CityBlock *homePtr;
};

#endif //!HUMAN_HPP_
