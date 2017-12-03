#pragma once

struct Camera
{
  Vect<2u, double> offset{50.0, 50.0};
  Vect<2u, float> zoom{0.5f, 0.5f};

  template<class T>
  constexpr Vect<2u, float> apply(Vect<2u, T> pos) const
  {
    return Vect<2u, float>(pos + offset) * zoom;
  }

  template<class T>
  constexpr Vect<2u, double> unapply(Vect<2u, T> pos) const
  {
    return  static_cast<Vect<2u, double>>(pos / zoom) - offset;
  }
};
