#ifndef PHYSICS_HPP
# define PHYSICS_HPP

# include "Vect.hpp"
# include "Fixture.hpp"
# include "CityMap.hpp"
# include <array>
# include <cmath>
# include <vector>

struct Entity;

# define CAR(x) ((x) * (x))

class Physics
{
private:
  static constexpr double const G{6.67384 * pow(10.0, -11.0)};

public:
  Physics() = default;

  void move(Fixture&) const;
  bool haveCollision(Fixture const& a, Fixture const& b) const;
  bool haveCollision(Vect<2, int> const& a, Fixture const& b) const;

  void fixMapCollision(Fixture&, std::array<std::array<CityBlock, MAP_SIZE>, MAP_SIZE> const& cityMap) const;

  template <class H, class T>
  void quadTree(H const &h, std::vector<T> &entities)
  {
    std::vector<T*> e;

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

  static constexpr int const endCond{20};

  template <class H, class T>
  void classicComparaison(H &h, std::vector<T*> &entities)
  {
    for (auto i = entities.begin() ; i != entities.end() ; ++i)
      for (auto j = i + 1 ; j != entities.end() ; ++j)
	if (this->haveCollision((*i)->entity.fixture, (*j)->entity.fixture))
	  h(*(*i), *(*j));
  }

  enum HPosition {
    TOP,
    BOTTOM,
    HMIDDLE
  };

  enum VPosition {
    LEFT,
    RIGHT,
    VMIDDLE
  };

  HPosition	getHRelativePosition(Vect<2, double> const& middle, Fixture const& f);
  VPosition	getVRelativePosition(Vect<2, double> const& middle, Fixture const& f);

  template <class H, class T>
  void quadTreeRec(H const &h, std::vector<T*> &entities)
  {
    if (entities.size() == 0)
      return ;
    if (entities.size() <= endCond) {
      this->classicComparaison(h, entities);
      return ;
    }
    Vect<2, double> lowCorner;
    Vect<2, double> highCorner;

    lowCorner = (*entities.begin())->entity.fixture.pos;
    highCorner = (*entities.begin())->entity.fixture.pos;
    for (auto i = entities.begin() + 1; i != entities.end() ; ++i) {
      Vect<2, double> currentPos = (*i)->entity.fixture.pos;

      for (int j = 0 ; j < 2 ; ++j) {
	if (currentPos[j] > highCorner[j])
	  highCorner[j] = currentPos[j];
	else if (currentPos[j] < lowCorner[j])
	  lowCorner[j] = currentPos[j];
      }
    }
    Vect<2, double> middle = (lowCorner + highCorner) / 2.0;
    std::array<std::vector<T*>, 4> children;
    for (auto i = entities.begin() + 1; i != entities.end() ; ++i) {
      VPosition vertical = getVRelativePosition(middle, (*i)->fixture);
      HPosition horizontal = getHRelativePosition(middle, (*i)->fixture);

      if (vertical != RIGHT) {
	if (horizontal != BOTTOM) {
	  children[0].push_back(*i);
	}
	if (horizontal != TOP) {
	  children[1].push_back(*i);
	}
      }
      if (vertical != LEFT) {
	if (horizontal != BOTTOM) {
	  children[2].push_back(*i);
	}
	if (horizontal != TOP) {
	  children[3].push_back(*i);
	}
      }
    }
    for (auto i = children.begin() ; i != children.end() ; ++i) {
      this->quadTreeRec(h, *i);
    }
  }
};

#endif /* PHYSICS_HPP */
