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

  float getAnimationFrame() const;

  void	beScaredOf(const Vect<2, double>&);

private:
  EntityAnimation anim;
  CityBlock &getHome();
  bool infected;
  CityBlock *homePtr;
  int coolDown;

  int			runAwayCooldown;
  bool			mustRunAway;
  Vect<2, double>	posToEscape;

public:
  bool canHighfive;

};

#endif //!HUMAN_HPP_
