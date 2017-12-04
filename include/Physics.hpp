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
public:
  Physics() = default;

  void move(Fixture&) const;
  bool haveCollision(Fixture const& a, Fixture const& b) const;
  bool haveCollision(Vect<2, double> const& a, Fixture const& b) const;
  bool haveCollision(Fixture& a, std::array<std::array<CityBlock, MAP_SIZE>, MAP_SIZE> const& cityMap) const;

  void fixMapCollision(Fixture&, std::array<std::array<CityBlock, MAP_SIZE>, MAP_SIZE> const& cityMap) const;

  template <class H, class... Types>
  void quadTree(H &h, std::vector<Types> &... entities) const
  {
    constexpr int const maxDepth{32};
    using expander = int[];

    std::tuple<std::vector<Types *>...> e;

    auto addElems([](auto &entities, auto &e)
		  {
		    using T = std::remove_reference_t<decltype(entities[0])>;

		    for (auto i = entities.begin() ; i != entities.end() ; ++i)
		      std::get<std::vector<T *>>(e).push_back(&(*i));
		  });
    (void)expander{(addElems(entities, e), 0)...};
    this->quadTreeRec(h, maxDepth, std::move(std::get<std::vector<Types *>>(e))...);
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
  void classicComparaison(H &h, std::vector<Types*> &&... entities) const
  {
    using expander = int[];

    auto checkAll([this, &h](auto &entityGroupe, auto &... entities)
		  {
		    auto everyPair([this, &h](auto &a, auto &b)
				   {
				     for (auto &aEntity : a)
				       for (auto &bEntity : b)
					 if (this->haveCollision(aEntity->entity.fixture, bEntity->entity.fixture))
					   h(*aEntity, *bEntity);
				   });
		    (void)expander{(everyPair(entities, entityGroupe), 0)...};
		  });
    (void)expander{(checkAll(entities, entities...), 0)...};
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
  void quadTreeRec(H &h, int depth, std::vector<Types*> &&... entities) const
  {
    using expander = int[];

    if (Vect<sizeof...(Types), bool>(!entities.size()...).all())
      return ;
    if (!depth || Vect<sizeof...(Types), std::size_t>(entities.size()...).sum() <= endCond) {
      this->classicComparaison(h, std::move(entities)...);
      return ;
    }
    Vect<2u, double> lowCorner(100.0, 100.0);
    Vect<2u, double> highCorner(0.0, 0.0);

    auto getCorners([&lowCorner, &highCorner](auto &entities)
		    {
		      for (auto const &entity : entities)
			{
			  Vect<2, double> currentPos(entity->entity.fixture.pos);

			  for (int j = 0 ; j < 2 ; ++j) {
			    if (currentPos[j] > highCorner[j])
			      highCorner[j] = currentPos[j];
			    else if (currentPos[j] < lowCorner[j])
			      lowCorner[j] = currentPos[j];
			  }
			}
		    });
    (void)expander{(getCorners(entities), 0)...};

    Vect<2, double> middle((lowCorner + highCorner) * 0.5);

    std::array<std::tuple<std::vector<Types *>...>, 4> children;
    auto op([this, middle](auto &entities, auto &children)
	    {
	      for (auto &entity : entities) {
		using T = std::remove_reference_t<decltype(entity)>;
		VPosition vertical = getVRelativePosition(middle, entity->entity.fixture);
		HPosition horizontal = getHRelativePosition(middle, entity->entity.fixture);

		if (vertical != RIGHT) {
		  if (horizontal != BOTTOM) {
		    std::get<std::vector<T>>(children[0]).push_back(entity);
		  }
		  if (horizontal != TOP) {
		    std::get<std::vector<T>>(children[1]).push_back(entity);
		  }
		}
		if (vertical != LEFT) {
		  if (horizontal != BOTTOM) {
		    std::get<std::vector<T>>(children[2]).push_back(entity);
		  }
		  if (horizontal != TOP) {
		    std::get<std::vector<T>>(children[3]).push_back(entity);
		  }
		}
	      }
	    });
    (void)expander{(op(entities, children), 0)...};
    for (auto &child : children) {
      this->quadTreeRec(h, depth - 1, std::move(std::get<std::vector<Types *>>(child))...);
    }
  }
  };

#endif /* PHYSICS_HPP */
