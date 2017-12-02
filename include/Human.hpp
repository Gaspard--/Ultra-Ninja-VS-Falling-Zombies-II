#ifndef HUMAN_HPP_
# define HUMAN_HPP_

#include "Mob.hpp"

class Human : public Mob
{
public:
  Human(Entity entity);
  ~Human();

  void setInfected(bool infected);
  bool const& getInfected() const;

private:
  bool infected;
};

#endif //!HUMAN_HPP_
