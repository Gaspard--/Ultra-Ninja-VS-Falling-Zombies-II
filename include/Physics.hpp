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

template<class T>
struct VectorItPair : public std::pair<typename std::vector<T>::iterator, typename std::vector<T>::iterator>
{
  using this_type = std::pair<typename std::vector<T>::iterator, typename std::vector<T>::iterator>;
  using this_type::pair;

  VectorItPair(std::vector<T> &vector)
    : this_type(vector.begin(), vector.end())
  {
  }
    
  auto begin()
  {
    return this_type::first;
  }

  auto end()
  {
    return this_type::second;
  }

  auto size()
  {
    return begin() - end();
  }
};


class Physics
{
public:
  Physics() = default;

  void move(Fixture&) const;
  static bool haveCollision(const Fixture& a, const Fixture& b)
  {
    return (a.pos - b.pos).length2() < CAR(a.radius + b.radius);
  }

  static bool haveCollision(Vect<2, double> const& a, Fixture const& b)
  {
    return (a - b.pos).length2() < CAR(b.radius);
  }

  bool haveCollision(Fixture& a, std::array<std::array<CityBlock, MAP_SIZE>, MAP_SIZE> const& cityMap) const;

  void fixMapCollision(Fixture&, std::array<std::array<CityBlock, MAP_SIZE>, MAP_SIZE> const& cityMap) const;  
  template <class H, class... Types>
  void quadTree(H &h, std::vector<Types> &... entities) const
  {
    constexpr int const maxDepth{16};
    using expander = int[];

    std::tuple<std::vector<Types *>...> e;

    auto addElems([](auto &entities, auto &e)
		  {
		    using T = std::remove_reference_t<decltype(entities[0])>;

		    for (auto i = entities.begin() ; i != entities.end() ; ++i)
		      std::get<std::vector<T *>>(e).push_back(&(*i));
		  });
    (void)expander{(addElems(entities, e), 0)...};
    this->quadTreeRec(h, maxDepth, VectorItPair(std::get<std::vector<Types *>>(e))...);
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
  void classicComparaison(H &h, VectorItPair<Types*>... entities) const
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

  static int getHRelativePosition(Vect<2, double> const& middle, Fixture const& f)
  {
    double diff = f.pos[0] - middle[0];

    return (std::abs(diff) > f.radius) * ((diff > 0) * 2 - 1);
  }

  static int getVRelativePosition(Vect<2, double> const& middle, Fixture const& f)
  {
    double diff = f.pos[1] - middle[1];

    return (std::abs(diff) > f.radius) * ((diff > 0) * 2 - 1);
  }


  template <class H, class... Types>
  void quadTreeRec(H &h, int depth, VectorItPair<Types*>... entities) const
  {
    using expander = int[];
    
    if (Vect<sizeof...(Types), bool>((!entities.size())...).all())
      return ;
    if (!depth || Vect<sizeof...(Types), std::size_t>((entities.second - entities.first)...).sum() <= endCond) {
      this->classicComparaison(h, entities...);
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
	      using T = std::remove_reference_t<decltype(*entities.first)>;

	      for (auto &child : children)
		std::get<std::vector<T>>(child).reserve(entities.size());
	      for (auto &entity : entities) {
		int vertical = getVRelativePosition(middle, entity->entity.fixture);
		int horizontal = getHRelativePosition(middle, entity->entity.fixture);

		if (vertical >= 0) {
		  if (horizontal <= 0) {
		    std::get<std::vector<T>>(children[0]).push_back(entity);
		  }
		  if (horizontal >= 0) {
		    std::get<std::vector<T>>(children[1]).push_back(entity);
		  }
		}
		if (vertical <= 0) {
		  if (horizontal <= 0) {
		    std::get<std::vector<T>>(children[2]).push_back(entity);
		  }
		  if (horizontal >= 0) {
		    std::get<std::vector<T>>(children[3]).push_back(entity);
		  }
		}
	      }
	    });
    (void)expander{(op(entities, children), 0)...};
    for (auto &child : children) {
      this->quadTreeRec(h, depth - 1, VectorItPair<Types *>(std::get<std::vector<Types *>>(child))...);
    }
  }
  };

#endif /* PHYSICS_HPP */
