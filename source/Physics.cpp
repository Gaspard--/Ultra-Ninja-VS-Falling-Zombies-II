# include "Physics.hpp"
# include "Entity.hpp"

Physics::HPosition Physics::getHRelativePosition(Vect<2, double> const& middle, Fixture const& f) const
{
  double diff = f.pos[0] - middle[0];
  if ((diff < 0 ? -1 * diff : diff) <= f.radius)
    return (Physics::HMIDDLE);
  if (diff > 0)
    return (Physics::TOP);
  return (Physics::BOTTOM);
}

Physics::VPosition Physics::getVRelativePosition(Vect<2, double> const& middle, Fixture const& f) const
{
  double diff = f.pos[1] - middle[1];

  if ((diff < 0 ? -1 * diff : diff) <= f.radius)
    return (Physics::VMIDDLE);
  if (diff > 0)
    return (Physics::RIGHT);
  return (Physics::LEFT);
}

bool Physics::haveCollision(const Fixture& a, const Fixture& b) const
{
  return (a.pos - b.pos).length2() < CAR(a.radius + b.radius);
}

bool Physics::haveCollision(Vect<2, double> const& a, Fixture const& b) const
{
  return (a - b.pos).length2() < CAR(b.radius);
}

void Physics::fixMapCollision(Fixture& a, std::array<std::array<CityBlock, MAP_SIZE>, MAP_SIZE> const& cityMap) const
{
  Vect<2, int> tilePos(static_cast<int>(a.pos[0]), static_cast<int>(a.pos[1]));
  static auto getCorner = [] (double pos) {
    return pos > 0.5;
  };
  Vect<2, int> corner(getCorner(a.pos[0] - tilePos[0]), getCorner(a.pos[1] - tilePos[1]));
  Vect<2, double> points[3] = {tilePos + corner,
			       {static_cast<double>(corner[0] + tilePos[0]), a.pos[1]},
			       {a.pos[0], static_cast<double>(corner[1] + tilePos[1])}};
  Vect<2, int> cornerNeg(corner * 2 - Vect<2u, int>{1, 1});
  Vect<2, int> sides[3] = {tilePos + cornerNeg,
			   {tilePos[0] + cornerNeg[0], tilePos[1]},
			   {tilePos[0], tilePos[1] + cornerNeg[1]}};

  auto handleCollision = [&] (int i) {
    if (cityMap[sides[i][1]][sides[i][0]].type != BlockType::NONE &&
	cityMap[sides[i][1]][sides[i][0]].type != BlockType::ROAD &&
	haveCollision(points[i], a))
      {
	a.pos = (a.pos - points[i]).normalized() * a.radius + points[i];
	return true;
      }
    return false;
  };
  handleCollision(1) || handleCollision(2) || handleCollision(0);
}

void Physics::move(Fixture& fixture) const
{
  fixture.pos += fixture.speed;
  fixture.speed *= 0.96;
}
