#pragma once

struct Camera
{
  Vect<2u, double> offset{0.0, 0.0};
  Vect<2u, float> zoom{1.0f, 1.0f};

  template<class T>
  constexpr Vect<2u, float> apply(Vect<2u, T> pos) const
  {
    return static_cast<Vect<2u, float>>(pos + offset) * zoom;
  }

  template<class T>
  constexpr Vect<2u, double> unapply(Vect<2u, T> pos) const
  {
    return  static_cast<Vect<2u, double>>(pos / zoom) - offset;
  }
};
