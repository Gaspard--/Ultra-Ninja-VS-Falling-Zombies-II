# include "Physics.hpp"
# include "Entity.hpp"

const double Physics::_G = 6.67384 * pow(10.0, -11.0);

bool Physics::haveCollision(const Fixture& a, const Fixture& b) const
{
  return (a.pos - b.pos).length2() < CAR(a.radius + b.radius);
}

bool Physics::haveCollision(Vect<2, int> const& a, Fixture const& b) const
{
  return (Vect<2, double>(static_cast<double>(a[0]), static_cast<double>(a[1])) - b.pos).length2() < CAR(b.radius);
}

void Physics::fixMapCollision(Fixture& a, std::array<std::array<CityBlock, MAP_SIZE>, MAP_SIZE> const& cityMap) const
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
    if (cityMap[sides[i][1]][sides[i][0]].getType() != BlockType::NONE &&
	cityMap[sides[i][1]][sides[i][0]].getType() != BlockType::ROAD &&
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

bool Physics::move(Fixture& fixture) const
{
  double distance;
  Vect<2, double> vec(0.0, 0.0);

  fixture.pos += fixture.speed;
  distance = sqrt((fixture.pos - _planet.pos).length2());
  vec = (fixture.pos - _planet.pos) / distance;
  /* Is fixture touching the planet ?*/
  if (haveCollision(fixture, _planet))
    {
      /* fix the fixture to the planet ground */
      fixture.pos += vec * ((fixture.radius + _planet.radius) - distance);
      /* delete speed against planet */
      fixture.speed -= vec * (vec.scalar(fixture.speed)) * (1.0 + fixture.bounciness);
      /* friction */
      fixture.speed *= 0.95;
    }
  /* application of gravity */
  // fixture.speed -= vec * ((_G * fixture.mass * _planet.mass / CAR(distance)) * fixture.mass);
  fixture.speed -= vec * fixture.mass * 0.00002;
  fixture.speed *= 0.96;
  return (fixture.pos - _planet.pos).length2() < CAR(fixture.radius + _planet.radius) + 0.001;
}

double Physics::getPlanetRadius(void) const
{
  return (_planet.radius);
}
