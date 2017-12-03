#ifndef PHYSICS_HPP
# define PHYSICS_HPP

# include "Vect.hpp"
# include "Fixture.hpp"
# include <array>
# include <cmath>
# include <vector>

struct Entity;

# define CAR(x) ((x) * (x))

class Physics
{
public:

  void move(Fixture&) const;

  bool haveCollision(const Fixture& a, const Fixture& b) const;
  bool haveCollision(Vect<2, int> const& a, Fixture const& b) const;
  void fixMapCollision(Fixture&, std::array<std::array<int/*cityBlock*/, 100>, 100> const& cityMap);

  template <class H, class T>
  void quadTree(H &h, std::vector<T> &entities)
  {
    std::vector<T*> &e;

    for (auto i = entities.begin() ; i != entities.end() ; ++i)
      e.push_back(&(*i));
    this->quadTreeRec(h, e);
  }

  template <class T>
  void updateFixtures(T begin, T end)
  {
    for (T i = begin ; i != end ; ++i)
      this->move((*i)->fixture);
  }

private:

  static const int	m_endCond = 20;

  template <class H, class T>
  void classicComparaison(H &h, std::vector<T*> &entities)
  {
    for (auto i = entities.begin() ; i != entities.end() ; ++i)
      for (auto j = i + 1 ; j != entities.end() ; ++j)
	if (this->haveCollision((*i)->entity.fixture, (*j)->entity.fixture))
	  h(i, j);
  }

  template <class H, class T>
  void quadTreeRec(H &h, std::vector<T*> &entities)
  {
    if (entities.size() == 0)
      return ;
    if (entities.size() <= m_endCond) {
      this->classicComparaison(h, entities);
      return ;
    }
  }

};

#endif /* PHYSICS_HPP */
