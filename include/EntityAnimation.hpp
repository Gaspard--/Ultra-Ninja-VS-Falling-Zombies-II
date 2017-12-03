#ifndef ENTITYANIMATION_HPP_
# define ENTITYANIMATION_HPP_

# include "Entity.hpp"

class EntityAnimation {
public:
  EntityAnimation();
  ~EntityAnimation() = default;

  void animate(Entity const& entity);
  float getAnimationFrame() const;

private:
  int animationFrame;
  int internalFrame;
  int maxFrame = 20;

  void setNewAnimationFrame(int stop, int move);
  void setNewAnimationFrame(int stop, int move, int move2);
};

#endif /* !ENTITYANIMATION_HPP_ */
