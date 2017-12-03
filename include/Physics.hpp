#ifndef PHYSICS_HPP
# define PHYSICS_HPP

# include "Vect.hpp"
# include "Fixture.hpp"
# include "CityMap.hpp"
# include <array>
# include <cmath>
# include <vector>
# include <tuple>

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

  template <class H, class... Types>
  void quadTree(H const &h, std::vector<Types> &... entities) const
  {
    std::tuple<std::vector<Types *>...> e;

    auto addElems([](auto &entities, auto &e)
		  {
		    for (auto i = entities.begin() ; i != entities.end() ; ++i)
		      e.push_back(&(*i));
		  });
    (addElems(entities, std::get<std::vector<Types *>>(e)) , ...);
    this->quadTreeRec(h, std::get<std::vector<Types *>>(e)...);
  }

  template <class T>
  void updateFixtures(T begin, T end)
  {
    for (T i = begin ; i != end ; ++i)
      this->move((*i)->fixture);
  }

private:

  static constexpr int const endCond{20};

  template <class H, class... Types>
  void classicComparaison(H const &h, std::vector<Types*> &... entities) const
  {
    auto checkAll([this, &h](auto &entityGroupe, auto &... entities)
		  {
		    auto everyPair([this, &h](auto &a, auto &b)
				   {
				     for (auto &aEntity : a)
				       for (auto &bEntity : b)
					 if (this->haveCollision(aEntity->entity.fixture, bEntity->entity.fixture))
					   h(*aEntity, *bEntity);
				   });
		    (everyPair(entities, entityGroupe) , ...);
		  });
    (checkAll(entities, entities...) , ...);
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

  HPosition	getHRelativePosition(Vect<2, double> const& middle, Fixture const& f) const;
  VPosition	getVRelativePosition(Vect<2, double> const& middle, Fixture const& f) const;

  template <class H, class... Types>
  void quadTreeRec(H const &h, std::vector<Types*> &... entities) const
  {
    if (((!entities.size()) & ...))
      return ;
    if ((entities.size() + ...) <= endCond) {
      this->classicComparaison(h, entities...);
      return ;
    }
    std::array<std::tuple<std::vector<Types *>...>, 4> children;
    auto op([this](auto &entities,  auto &children)
	    {
	      Vect<2, double> lowCorner((*entities.begin())->entity.fixture.pos);
	      Vect<2, double> highCorner((*entities.begin())->entity.fixture.pos);

	      for (auto i = entities.begin() + 1; i != entities.end() ; ++i) {
		Vect<2, double> currentPos = (*i)->entity.fixture.pos;

		for (int j = 0 ; j < 2 ; ++j) {
		  if (currentPos[j] > highCorner[j])
		    highCorner[j] = currentPos[j];
		  else if (currentPos[j] < lowCorner[j])
		    lowCorner[j] = currentPos[j];
		}
	      }
	      Vect<2, double> middle((lowCorner + highCorner) * 0.5);

	      for (auto i = entities.begin() + 1; i != entities.end() ; ++i) {
		using T = std::remove_reference_t<decltype(*i)>;
		VPosition vertical = getVRelativePosition(middle, (*i)->entity.fixture);
		HPosition horizontal = getHRelativePosition(middle, (*i)->entity.fixture);

		if (vertical != RIGHT) {
		  if (horizontal != BOTTOM) {
		    std::get<std::vector<T>>(children[0]).push_back(*i);
		  }
		  if (horizontal != TOP) {
		    std::get<std::vector<T>>(children[1]).push_back(*i);
		  }
		}
		if (vertical != LEFT) {
		  if (horizontal != BOTTOM) {
		    std::get<std::vector<T>>(children[2]).push_back(*i);
		  }
		  if (horizontal != TOP) {
		    std::get<std::vector<T>>(children[3]).push_back(*i);
		  }
		}
	      }
	    });
    (op(entities, children) , ...);
    for (auto i = children.begin() ; i != children.end() ; ++i) {
      this->quadTreeRec(h, std::get<std::vector<Types *>>(*i)...);
    }
  }
};

#endif /* PHYSICS_HPP */
