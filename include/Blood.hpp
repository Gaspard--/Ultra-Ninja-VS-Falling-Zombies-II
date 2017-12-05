#pragma once

struct Blood
{
  
public:
  Vect<2u, double> pos;
  double intensity;
  double delay;
  int type;

  static void spawnBlood(std::vector<Blood> &bloods, Vect<2u, double> pos, Vect<2u, double> speed)
  {
    Vect<2u, float> randOffset(Vect<2u, float>(static_cast<float>(rand() & 255), static_cast<float>(rand() & 255)) - Vect<2u, float>(128.0f, 128.0f));
    Vect<2u, float> offset(speed * (static_cast<double>(rand() & 16) + 4.0) + randOffset * 0.3 / 256.0);

    bloods.push_back({pos + offset, 1.0, std::sqrt(offset.length2()) * 1.0, rand() % 3});
  }

};
