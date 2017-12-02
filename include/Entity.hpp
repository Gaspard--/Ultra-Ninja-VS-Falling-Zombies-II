#ifndef ENTITY_HPP
# define ENTITY_HPP

# include <functional>
# include "Physics.hpp"
# include "Renderable.hpp"

/*
** kind of entity class
*/
struct Entity
{
  Entity(Fixture = {{0, 0}, {0, 0}, 0, 0, 0});

  void update();

  Fixture fixture;
  bool isUseless = false;
  Renderable renderable;
};

#endif /* ENTITY_HPP */
