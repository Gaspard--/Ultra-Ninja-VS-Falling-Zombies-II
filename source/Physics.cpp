# include "Physics.hpp"
# include "Entity.hpp"

bool Physics::haveCollision(const Fixture& a, const Fixture& b) const
{
  return (a.pos - b.pos).length2() < CAR(a.radius + b.radius);
}

bool Physics::haveCollision(Vect<2, int> const& a, Fixture const& b) const
{
  return (Vect<2, double>(static_cast<double>(a[0]), static_cast<double>(a[1])) - b.pos).length2() < CAR(b.radius);
}

void Physics::fixMapCollision(Fixture& a, std::array<std::array<int/*cityBlock*/, 100>, 100> const& cityMap)
{
  Vect<2, int> tilePos(static_cast<int>(a.pos[0]), static_cast<int>(a.pos[1]));
  static auto getCorner = [] (double pos) {
    return pos > 0.5;
  };
  Vect<2, int> corner(getCorner(a.pos[0] - tilePos[0]), getCorner(a.pos[1] - tilePos[1]));
  Vect<2, int> points[3] = {tilePos + corner,
			    {corner[0] + tilePos[0], static_cast<int>(a.pos[1])},
			    {static_cast<int>(a.pos[0]), corner[1] + tilePos[1]}};
  Vect<2, int> cornerNeg(corner[0] == 1 ? 1 : -1, corner[1] == 1 ? 1 : -1);
  Vect<2, int> sides[3] = {tilePos + cornerNeg,
			   {tilePos[0] + cornerNeg[0], tilePos[1]},
			   {tilePos[0], tilePos[1] + cornerNeg[1]}};

  auto handleCollision = [&] (int i, auto func) {
    if (cityMap[sides[i][1]][sides[i][0]] == 1/* TODO switch 1 to enum wall */ &&
	haveCollision(points[i], a))
      {
	func();
      }
  };

  handleCollision(0, [&] () {
      a.pos -= a.speed;
    });

  handleCollision(1, [&] () {
      a.pos[0] = points[1][0] - a.radius * cornerNeg[0];
    });

  handleCollision(2, [&] () {
      a.pos[1] = points[1][1] - a.radius * cornerNeg[1];
    });
}

void Physics::move(Fixture& fixture) const
{
  fixture.pos += fixture.speed;
}
