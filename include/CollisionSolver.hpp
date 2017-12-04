#ifndef COLLISIONSOLVER_HPP
# define COLLISIONSOLVER_HPP

struct	CollisionSolver
{
  template <class T, class U>
  void	operator()(T&, U&) {}
};


#endif /* COLLISIONSOLVER_HPP */
