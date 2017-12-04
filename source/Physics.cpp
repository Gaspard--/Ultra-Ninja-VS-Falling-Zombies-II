# include "Physics.hpp"
# include "Entity.hpp"

bool Physics::haveCollision(Fixture& a, std::array<std::array<CityBlock, MAP_SIZE>, MAP_SIZE> const& cityMap) const
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
    return cityMap[sides[i][1]][sides[i][0]].type != BlockType::NONE &&
    cityMap[sides[i][1]][sides[i][0]].type != BlockType::ROAD &&
    haveCollision(points[i], a);
  };

  return handleCollision(0) || handleCollision(1) || handleCollision(2);
}

void Physics::fixMapCollision(Fixture& a, std::array<std::array<CityBlock, MAP_SIZE>, MAP_SIZE> const& cityMap) const
{
  bool ret(false);

  if (a.pos[0] < a.radius)
    {
      a.pos[0] = a.radius;
      ret = true;
    }
  if (a.pos[0] > MAP_SIZE - a.radius)
    {
      a.pos[0] = MAP_SIZE - a.radius;
      ret = true;
    }
  if (a.pos[1] < a.radius)
    {
      a.pos[1] = a.radius;
      ret = true;
    }
  if (a.pos[1] > MAP_SIZE - a.radius)
    {
      a.pos[1] = MAP_SIZE - a.radius;
      ret = true;
    }
  if (ret)
    return ;
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
  (handleCollision(1) | handleCollision(2)) || handleCollision(0);
}

void Physics::move(Fixture& fixture) const
{
  // uncomment this if things move too fast.
  // if (fixture.speed.length2() > fixture.radius * fixture.radius * 0.25)
  //   fixture.speed = fixture.speed.normalized() * fixture.radius * 0.5;
  fixture.pos += fixture.speed;
  fixture.speed *= 0.96;
}
