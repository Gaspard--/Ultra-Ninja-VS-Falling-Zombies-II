#include "EntityAnimation.hpp"

EntityAnimation::EntityAnimation()
  : animationFrame(2), internalFrame(0)
{
}

float EntityAnimation::getAnimationFrame() const
{
  return static_cast<float>(animationFrame);
}

void EntityAnimation::setNewAnimationFrame(int stop, int move)
{
  if (animationFrame != stop && animationFrame != move)
    animationFrame = stop;
  else if (++internalFrame > maxFrame)
    {
      internalFrame = 0;
      animationFrame = animationFrame == move ? stop : move;
    }
}

void EntityAnimation::setNewAnimationFrame(int stop, int move, int move2)
{
  if (animationFrame != stop && animationFrame != move && animationFrame != move2)
    animationFrame = stop;
  else if (++internalFrame > maxFrame)
    {
      internalFrame = 0;
      if (animationFrame == move)
	animationFrame = move2;
      else
	animationFrame = move;
    }
}

void EntityAnimation::animate(Entity const& entity)
{
  if (entity.fixture.speed[0] <= 0.001 && entity.fixture.speed[0] >= -0.001 &&
      entity.fixture.speed[1] <= 0.001 && entity.fixture.speed[1] >= -0.001)
    {
        switch (animationFrame) {
	        case 0:
	        case 1:
	            animationFrame = 0;
	            break;
            case 2:
            case 3:
            case 4:
	            animationFrame = 2;
                break;
            case 5:
            case 6:
            case 7:
                animationFrame = 5;
                break;
            case 8:
            case 9:
                animationFrame = 8;
                break;
            default:
                return;
        }
        return;
    }

  // x axis animation
  if (abs(entity.fixture.speed[0]) > abs(entity.fixture.speed[1]))
    {
      // check right side animation
      if (entity.fixture.speed[0] > 0)
	setNewAnimationFrame(8, 9);
      else
	setNewAnimationFrame(0, 1);
    }
  // y axis animation
  else
    {
      // check up side animation
      if (entity.fixture.speed[1] > 0)
	setNewAnimationFrame(5, 6, 7);
      else
	setNewAnimationFrame(2, 3, 4);
    }
}
