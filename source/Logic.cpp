#include "Logic.hpp"
#include "Input.hpp"
#include "Display.hpp"
#include "SoundHandler.hpp"

Logic::Logic()
  : mousePos{0, 0}
{
  time = 0;
  score = 0;
  gameOver = false;
  combo = 0;
  multiplier = 0;
}

void Logic::tick(void)
{
  if (!gameOver)
    {
      ++time;
    }
  multiplier += (1.0 / 600.0);
}

void    Logic::addToScore(int add)
{
  score += static_cast<int>(combo * add * (multiplier == 0 ? 1 : multiplier));
}

void    Logic::incCombo()
{
  combo++;
}

void    Logic::resetCombo()
{
  combo = 0;
}

unsigned int  Logic::getScore(void) const
{
  return (score);
}

std::string     Logic::getCombo(void) const
{
  if (combo < 2)
    return ("");
  return ("x" + std::to_string(combo));
}

std::string     Logic::getTime(void) const
{
  std::string   toReturn;

  if (time / 3600 >= 10)
    toReturn = std::to_string(time / 3600) + " m ";
  else if (time / 3600)
    toReturn = "0" + std::to_string(time / 3600) + " m ";
  if ((time / 60) % 60 >= 10)
    toReturn += std::to_string((time / 60) % 60) + " s";
  else
    toReturn += "0" + std::to_string((time / 60) % 60) + " s";
  return (toReturn);
}

void Logic::handleEvent(Display const &display, Event const& event)
{
  if (event)
    {
      switch (event.type)
        {
        case Event::KEY:
          handleKey(event.window, event.val.key);
          break;
        case Event::MOUSE:
          handleMouse(display, event.window, event.val.mouse);
          break;
        case Event::BUTTON:
          handleButton(event.window, event.val.button);
          break;
	default:
	  break;
        }
    }
}

void Logic::handleKey(GLFWwindow *window, Key key)
{
  switch (key.key)
    {
    case GLFW_KEY_ESCAPE:
      glfwSetWindowShouldClose(window, true);
      break;
    default:
      break;
    }
}

void Logic::checkEvents(Display const &display)
{
  if (display.isKeyPressed(GLFW_KEY_ENTER) && gameOver)
    {
      // TODO: restart
    }
}

void Logic::handleMouse(Display const &display, GLFWwindow *, Mouse mouse)
{
  Vect<2u, float> const size(display.getSize());

  mousePos = {mouse.x, mouse.y};
  mousePos -= Vect<2u, double>(size[0] - size[1], 0);
  mousePos /= Vect<2u, double>(size[1], -size[1]);
  mousePos += Vect<2u, double>(-1.0, 1.0);
}

Vect<2u, double> Logic::getMouse(Display const &display) const
{
  std::cout << display.getCamera().unapply(mousePos) << std::endl;
  return display.getCamera().unapply(mousePos);
}

void Logic::handleButton(GLFWwindow *, Button button)
{
  if (button.button != GLFW_MOUSE_BUTTON_LEFT || button.action != GLFW_PRESS || gameOver)
    return ;
}

Vect<2, double> Logic::getPlayerPos(void) const
{
  return {0.0, 0.0}; // TODO: return player's pos
}

bool Logic::getGameOver(void) const
{
  return gameOver;
}
