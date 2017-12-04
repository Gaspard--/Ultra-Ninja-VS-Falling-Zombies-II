#ifndef HUMAN_HPP_
# define HUMAN_HPP_

# include <vector>

#include "Mob.hpp"
#include "CityBlock.hpp"
#include "Zombie.hpp"

class Zombie;

class Human : public Mob
{
public:
  Human(Entity entity, CityBlock &home);
  ~Human();

  void update();

  void setInfected(bool infected);
  bool const& getInfected() const;
  CityBlock const &getHome() const;

  void setCoolDown(int cooldown);
  bool canHighFive() const;

  void addHunter(Zombie&);
  void removeHunter(Zombie&);
  float getAnimationFrame() const;

private:
  EntityAnimation anim;
  CityBlock &getHome();
  bool infected;
  CityBlock *homePtr;
  int coolDown;

  std::vector<Zombie*>	hunters;

public:
  bool canHighfive;

};

#endif //!HUMAN_HPP_
