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
  Human() = delete;
  Human(Human const &);
  Human(Entity entity, CityBlock &home);
  ~Human();

  void update();
  void handleJump();

  void setInfected(bool infected);
  bool const& getInfected() const;
  CityBlock &getHome() const;

  void setCoolDown(int cooldown);
  bool canHighFive() const;

  float getAnimationFrame() const;

  void	beScaredOf(const Vect<2, double>&);

  void	runAway(void);

  bool isRunningAway(void) const;

private:
  EntityAnimation anim;
  bool infected;
  CityBlock *homePtr;
  int coolDown;

  int	basicWalkCooldown;
  double	dir;

  int			runAwayCooldown;
  bool			mustRunAway;
  Vect<2, double>	posToEscape;

public:
  bool canHighfive;

};

#endif //!HUMAN_HPP_
