#include <thread>
#include <mutex>

#include "Logic.hpp"
#include "Input.hpp"
#include "Display.hpp"
#include "SoundHandler.hpp"
#include "Shuriken.hpp"

Logic::Logic()
  : cityMap(*this),
    running(true),
    mousePos{0.0, 0.0},
    lastUpdate(Clock::now())
{
  time = 0;
  score = 0;
  restart = false;
  gameOver = false;
  tutoPage = true;
  combo = 0;
  multiplier = 0;
  entityManager.spawnPlayer({51.5, 49.5});
}

void Logic::update()
{
  if (!gameOver && !tutoPage)
    {
      ++time;
      entityManager.update(physics, *this, cityMap);
      entityManager.spawnZombies();
      cityMap.tick(*this);
      multiplier += (1.0 / 600.0);
      if (!(time % 60))
	score += entityManager.humans.size();
      gameOver = (entityManager.humans.size() == 0);
    }
}

void Logic::tick(std::mutex &lock)
{
  auto const now(Clock::now());

  if (now > lastUpdate + getTickTime() * 2)
    {
      lastUpdate = now;
      return ;
    }
  lastUpdate += getTickTime();
  if (now < lastUpdate)
    std::this_thread::sleep_for(lastUpdate - now);

  {
    std::lock_guard<std::mutex> scopedLock(lock);
    update();
  }
}

void Logic::addToScore(int add)
{
  score += static_cast<int>(combo * add * (multiplier == 0 ? 1 : multiplier));
}

void Logic::incCombo()
{
  combo++;
}

void Logic::resetCombo()
{
  combo = 0;
}

long unsigned int Logic::getScore(void) const
{
  return score;
}

std::string Logic::getCombo(void) const
{
  if (combo < 2)
    return "";
  return "x" + std::to_string(combo);
}

std::string Logic::getTime(void) const
{
  auto secondTime((time * getTickTime().count()) / 1000000);
  std::string   toReturn;

  if (secondTime / 60 >= 10)
    toReturn = std::to_string(secondTime / 60) + " m ";
  else if (secondTime / 60)
    toReturn = "0" + std::to_string(secondTime / 60) + " m ";
  if ((secondTime) % 60 >= 10)
    toReturn += std::to_string((secondTime) % 60) + " s";
  else
    toReturn += "0" + std::to_string((secondTime) % 60) + " s";
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
    case GLFW_KEY_SPACE:
      entityManager.getPlayer().canHighfive = (key.action == GLFW_PRESS);
      break;
    default:
      break;
    }
}

void Logic::checkEvents(Display const &display)
{
  Player& player = entityManager.getPlayer();
  if (display.isKeyPressed(GLFW_KEY_ENTER))
    {
      if (gameOver)
        restart = true;
      else if (tutoPage)
        tutoPage = false;
    }

  if (display.isKeyPressed(GLFW_KEY_D))
    player.accelerate({1, 0});
  if (display.isKeyPressed(GLFW_KEY_A))
    player.accelerate({-1, 0});
  if (display.isKeyPressed(GLFW_KEY_W))
    player.accelerate({0, 1});
  if (display.isKeyPressed(GLFW_KEY_S))
    player.accelerate({0, -1});
  if (display.isKeyPressed(GLFW_KEY_K))
    player.shuriken(entityManager.shurikens);
  if (display.isKeyPressed(GLFW_KEY_J))
    player.slash(entityManager.slashes);
  if (display.isKeyPressed(GLFW_KEY_I))
    player.circleAttack(entityManager.slashes);
  if (display.isKeyPressed(GLFW_KEY_L))
    player.bomb(entityManager.bombs);
}

void Logic::handleMouse(Display const &display, GLFWwindow *, Mouse mouse)
{
  Vect<2u, float> const size(display.getSize());

  mousePos = {mouse.x, mouse.y};
  mousePos -= Vect<2u, double>(size[0] - size[1], 0.0);
  mousePos /= Vect<2u, double>(size[1], -size[1]);
  mousePos += Vect<2u, double>(-1.0, 1.0);
}

Vect<2u, double> Logic::getMouse(Display const &display) const
{
  return display.getCamera().unapply(mousePos);
}

EntityManager const& Logic::getEntityManager() const
{
  return entityManager;
}

EntityManager &Logic::getEntityManager()
{
  return entityManager;
}

void Logic::handleButton(GLFWwindow *, Button button)
{
  if (button.button != GLFW_MOUSE_BUTTON_LEFT || button.action != GLFW_PRESS || gameOver)
    return ;
}

Vect<2, double> Logic::getPlayerPos(void) const
{
  return entityManager.getPlayer().entity.fixture.pos;
}


bool Logic::getRestart(void) const
{
  return restart;
}

bool Logic::getGameOver(void) const
{
  return gameOver;
}

bool Logic::getTutoPage(void) const
{
  return tutoPage;
}

CityMap const &Logic::getCityMap() const
{
  return cityMap;
}
