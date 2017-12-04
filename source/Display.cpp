#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include "Display.hpp"
#include "Bind.hpp"
#include "TextureHandler.hpp"

#include <cstring>
#include <cerrno>

inline RenderContext contextFromFiles(std::string name)
{
  std::stringstream vert;
  std::stringstream frag;
  std::ifstream vertInput("shaders/" + name + ".vert");
  std::ifstream fragInput("shaders/" + name + ".frag");

  if (!fragInput || !vertInput)
  {
	  std::cout << "shaders/" + name + ".vert" << std::endl;
	  std::cout << "shaders/" + name + ".frag" << std::endl;
	  throw std::runtime_error(strerror(errno));
  }
  vert << vertInput.rdbuf();
  frag << fragInput.rdbuf();
  return {Vao(), my_opengl::createProgram<2>({static_cast<unsigned int>(GL_VERTEX_SHADER), static_cast<unsigned int>(GL_FRAGMENT_SHADER)},
                                             {vert.str(), frag.str()})};
}

Display::GlfwContext::GlfwContext()
{
  glfwSetErrorCallback([](int, char const *str)
                       {
                         throw std::runtime_error(str);
                       });
  if (!glfwInit())
    throw std::runtime_error("opengl: failed to initialize glfw");

}

Display::GlfwContext::~GlfwContext()
{
  glfwTerminate();
}

// void Display::resetPlanet()
// {
//     glBindFramebuffer(GL_FRAMEBUFFER, planetRenderTexture.framebuffer);
//     glViewport(0, 0, 1024, 1024);
//     glClearColor(0.2, 0.2, 0.5, 0.2);
//     glClear(GL_COLOR_BUFFER_BIT);
//     glEnable(GL_BLEND);
//     {
//       Vect<2u, float> olddim(dim);

//       dim = {1.0, 1.0};
//       displayPlanet(planet, 2.0, {1.0, 0.0});
//       dim = olddim;
//     }
//     glDisable(GL_BLEND);
//     glBindFramebuffer(GL_FRAMEBUFFER, 0);
//     glViewport(0, 0, size[0], size[1]);
// }

Display::Display()
  : camera{}
  , window([this]{
      glfwWindowHint(GLFW_DEPTH_BITS, 1);
      std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> window(glfwCreateWindow(1920, 1080, "ultra-ninja VS falling zombies II", nullptr, nullptr), &glfwDestroyWindow);

      if (!window)
        throw std::runtime_error("opengl: failed to open window");
      glfwMakeContextCurrent(window.get());
      glfwSwapInterval(1);
      if (gl3wInit())
        throw std::runtime_error("opengl: failed to initialize 3.0 bindings");
      if (!gl3wIsSupported(3, 0))
        throw std::runtime_error("opengl: Opengl 3.0 not supported");
      return window;
    }())
  , fontHandler("./resources/ObelixPro-Broken-cyr.ttf")
  , textureContext(contextFromFiles("texture"))
  , textContext(contextFromFiles("text"))
  , bloodSpray{my_opengl::loadTexture("resources/BloodSpray.bmp"), my_opengl::loadTexture("resources/BloodSpray2.bmp"), my_opengl::loadTexture("resources/BloodSpray3.bmp")}
  , mobSpray{my_opengl::loadTexture("resources/MobSpray.bmp"), my_opengl::loadTexture("resources/MobSpray2.bmp"), my_opengl::loadTexture("resources/MobSpray3.bmp")}
  , planetRenderTexture({1024u, 1024u})
  , size{0.0f, 0.0f}
  , dim{0.0f, 0.0f}
{
  static auto setFrameBuffer =
    [this] (int width, int height)
    {
      glViewport(0, 0, width, height);
      size = {static_cast<float>(width), static_cast<float>(height)};
      dim = {static_cast<float>(height) / static_cast<float>(width), 1.0f};
    };

  glfwSetFramebufferSizeCallback(window.get(), [] (GLFWwindow *, int width, int height) {
      setFrameBuffer(width, height);
    });
  setFrameBuffer(1920, 1080);

  {
    Bind<RenderContext> bind(textureContext);

    glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 5 * sizeof(float), nullptr);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 5 * sizeof(float), reinterpret_cast<void *>(2u * sizeof(float)));
    glVertexAttribPointer(2, 1, GL_FLOAT, false, 5 * sizeof(float), reinterpret_cast<void *>(4u * sizeof(float)));
  }
  {
    Bind<RenderContext> bind(rectContext);

    glBindBuffer(GL_ARRAY_BUFFER, rectBuffer);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(float), nullptr);
  }
  {
    Bind<RenderContext> bind(textContext);

    glBindBuffer(GL_ARRAY_BUFFER, textBuffer);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 4 * sizeof(float), nullptr);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 4 * sizeof(float), reinterpret_cast<void *>(2u * sizeof(float)));
  }
}

Display::~Display()
{
}

GLFWwindow *Display::getWindow() const {
  return window.get();
}

static Vect<2u, float> rotate(Vect<2u, float> a, Vect<2u, float> b)
{
  return {a[0] * b[0] - a[1] * b[1], a[0] * b[1] + a[1] * b[0]};
}

void Display::displayText(std::string const &text, unsigned int fontSize, Vect<2u, float> step, Vect<2u, float> textPos, Vect<2u, float> rotation, Vect<3u, float> color)
{
  fontHandler.renderText(text, [this, textPos, rotation, color](Vect<2u, float> pen, Vect<2u, float> size, unsigned char *buffer, Vect<2u, int> fontDim)
                         {
                           Texture texture;
                           Bind<RenderContext> bind(textContext);

                           glActiveTexture(GL_TEXTURE0);
                           glBindTexture(GL_TEXTURE_2D, texture);
                           glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                           glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                           glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                           glTexImage2D(GL_TEXTURE_2D,
                                        0,
                                        GL_RED,
                                        fontDim[0],
                                        fontDim[1],
                                        0,
                                        GL_RED,
                                        GL_UNSIGNED_BYTE,
                                        static_cast<void *>(buffer));
                           float data[16];

                           for (unsigned int i(0); !(i & 4u); ++i)
                             {
                               Vect<2u, float> corner{static_cast<float>(i & 1u), static_cast<float>(i >> 1u)};
                               Vect<2u, float> destCorner(rotate(pen + textPos + corner * size, rotation));

                               data[i * 4 + 0] = corner[0];
                               data[i * 4 + 1] = 1.0f - corner[1];
                               data[i * 4 + 2] = destCorner[0];
                               data[i * 4 + 3] = destCorner[1];
                             }
                           glBindBuffer(GL_ARRAY_BUFFER, textBuffer);
                           glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
                           my_opengl::setUniform(dim, "dim", textContext.program);
                           my_opengl::setUniform(color, "textColor", textContext.program);
                           my_opengl::setUniform(0u, "tex", textContext.program);
                           glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
                         }, fontSize, step);
}

void Display::displayRect(Rect const &rect)
{
  Bind<RenderContext> bind(rectContext);
  float buffer[4u * 4u];

  for (unsigned int j(0u); j != 4u; ++j)
    {
      Vect<2u, float> const corner(static_cast<float>(j & 1u), static_cast<float>(j >> 1u));
      Vect<2u, float> const destCorner(corner * rect.size + rect.pos);

      std::copy(&corner[0u], &corner[2u], &buffer[j * 4u]);
      std::copy(&destCorner[0u], &destCorner[2u], &buffer[j * 4u + 2u]);
    }
  glActiveTexture(GL_TEXTURE0);
  glBindBuffer(GL_ARRAY_BUFFER, rectBuffer);
  my_opengl::setUniform(dim, "dim", rectContext.program);
  my_opengl::setUniform(rect.color, "rect_color", rectContext.program);
  glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Display::displayRenderableAsHUD(Renderable const& renderable, GLuint texture)
{
  Bind<RenderContext> bind(textureContext);
  float buffer[5u * 4u];
  Vect<2u, float> const up(renderable.destPos.normalized());

  for (unsigned int j(0u); j != 4u; ++j)
    {
      Vect<2u, float> const corner(static_cast<float>(j & 1u), static_cast<float>(j >> 1u));
      Vect<2u, float> const sourceCorner(renderable.sourcePos + corner * renderable.sourceSize);
      Vect<2u, float> const destCorner(renderable.destPos + (corner * renderable.destSize));

      std::copy(&sourceCorner[0u], &sourceCorner[2u], &buffer[j * 5u]);
      std::copy(&destCorner[0u], &destCorner[2u], &buffer[j * 5u + 2u]);
      buffer[j * 5u + 4u] = renderable.depth;
    }
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);
  glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
  my_opengl::setUniform(dim, "dim", textureContext.program);
  my_opengl::setUniform(0u, "tex", textureContext.program);
  glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Display::render(Logic const &logic)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glClearColor(0.3f, 0.5f, 0.2f, 0.0f);
  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glDepthFunc(GL_LESS);
  for (auto const &renderables : displayInfo.renderables) {
	  displayRenderables(renderables.second.begin(), static_cast<GLuint>(renderables.second.size()), renderables.first);
  }
  glDisable(GL_DEPTH_TEST);
  displayInterface(logic);
  glDisable(GL_BLEND);
  glfwSwapBuffers(window.get());
  glfwPollEvents();
}

void Display::displayInterface(Logic const &logic)
{
  // displayText("Current Population",
  //             256, {0.05f, 0.05f}, {-0.017f * 18, -0.315f}, {sqrt(camera.length2()), 0}, {1.0f, 1.0f, 1.0f});
  // displayText("Combo   " + displayInfo.combo, 256, {0.1f, 0.1f}, {-0.95f / dim[0], -0.60f}, {1.0f, 0.0f}, {1.0f, 1.0f, 1.0f});
  auto const &manager(logic.getEntityManager());
  for (auto &player : manager.players)
    {
      auto pos(camera.apply(player.entity.fixture.pos));
      double halfWidth = 1.0 / dim[0];
      double halfHeight = 1.0 / dim[1];
      for (auto &zombie : manager.zombies)
	{
	  auto zombiePos(camera.apply(zombie.entity.fixture.pos));
	  if ((zombiePos[0] > -halfWidth && zombiePos[0] < halfWidth && zombiePos[1] > -halfHeight && zombiePos[1] < halfHeight) || !(pos[1] - zombiePos[1]))
	    continue;
	  Vect<2, double> finalSize = camera.zoom * Vect<2u, float>{0.2f, 0.3f};
	  Vect<2, double> arrowPos({100.0, 100.0});
	  Vect<2, double> initialPos({0.0, 0.0});
	  Vect<2, double> initialSize({0.0, 0.0});
	  double droiteCoef = (pos[0] - zombiePos[0]) / (pos[1] - zombiePos[1]);
	  double droiteOrd = pos[1] - pos[0] * droiteCoef;
	  if (zombiePos[0] < -halfWidth && droiteCoef) {
	    Vect<2, double> newPos = Vect<2, double>(-halfWidth, (-halfWidth - droiteOrd) / droiteCoef);
	    if ((newPos - pos).length2() < (arrowPos - pos).length2()) {
	      arrowPos = newPos;
	      initialSize = {-0.5f, 1.0f};
	      initialPos = {1.0f, 0.0f};
	    }
	  }
	  else if (zombiePos[0] > halfWidth && droiteCoef) {
	    Vect<2, double> newPos = Vect<2, double>(halfWidth, (halfWidth - droiteOrd) / droiteCoef) - finalSize[0];
	    if ((newPos - pos).length2() < (arrowPos - pos).length2()) {
	      arrowPos = newPos;
	      initialSize = {0.5f, 1.0f};
	      initialPos = {0.5f, 0.0f};
	    }
	  }
	  if (zombiePos[1] < -halfHeight) {
	    Vect<2, double> newPos = Vect<2, double>(-droiteCoef * halfHeight + droiteOrd, -halfHeight);
	    if ((newPos - pos).length2() < (arrowPos - pos).length2()) {
	      arrowPos = newPos;
	      initialSize = {0.5f, -1.0f};
	      initialPos = {0.0f, 1.0f};
	    }
	  }
	  else if (zombiePos[1] > halfHeight) {
	    Vect<2, double> newPos = Vect<2, double>(droiteCoef * halfHeight + droiteOrd, halfHeight) - finalSize[1];
	    if ((newPos - pos).length2() < (arrowPos - pos).length2()) {
	      arrowPos = newPos;
	      initialSize = {0.5f, 1.0f};
	      initialPos = {0.0f, 0.0f};
	    }
	  }
	  displayRenderableAsHUD(Renderable{
	      initialPos,
		initialSize,
		  arrowPos,
		    finalSize}, TextureHandler::getInstance().getTexture(TextureHandler::TextureList::ARROW));
	}
    }
  displayText("Score   " + std::to_string(displayInfo.score), 256, {0.1f, 0.1f}, {-0.95f / dim[0], -0.80f}, {1.0f, 0.0f}, {1.0f, 1.0f, 1.0f});
  displayText("Time   " + displayInfo.time, 256, {0.1f, 0.1f}, {-0.95f / dim[0], -1.00f}, {1.0f, 0.0f}, {1.0f, 1.0f, 1.0f});
  displayRenderableAsHUD(Renderable{
    {0.0f, 0.0f},
	{1.0f, 1.0f},
	{1.0f / dim[0] - 0.73f, -1.0f / dim[1] + 0.05f},
	{0.7f, 0.08f}
  }, TextureHandler::getInstance().getTexture(TextureHandler::TextureList::BARBACK));
  displayRenderableAsHUD(Renderable{
    {0.0f, 0.0f},
	{1.0f, 1.0f},
	{1.0f / dim[0] - 0.71f, -1.0f / dim[1] + 0.055f},
	{0.0066f * static_cast<float>(displayInfo.ulti), 0.07f}
  }, TextureHandler::getInstance().getTexture(TextureHandler::TextureList::BARFRONT));
  displayRenderableAsHUD(Renderable{
    {0.0f, 0.0f},
	{1.0f, 1.0f},
	{1.0f / dim[0] - 0.82f, -1.0f / dim[1] + 0.054f},
	{0.072f, 0.072f}
  }, TextureHandler::getInstance().getTexture((displayInfo.ulti == 100) ? TextureHandler::TextureList::SPIN : TextureHandler::TextureList::SPINHOLLOW));
  for (unsigned int i = 0; i < 5; i++)
    {
      displayRenderableAsHUD(Renderable{
	    {0.0f, 0.0f},
	    {1.0f, 1.0f},
	    {1.0f / dim[0] - (static_cast<float>(i + 1) * 0.07f + 0.05f), -1.0f / dim[1] + 0.15f},
		{0.09f, 0.09f}
	}, TextureHandler::getInstance().getTexture((i >= 5 - displayInfo.bomb) ? TextureHandler::TextureList::BOMB : TextureHandler::TextureList::BOMBHOLLOW));
    }
  if (displayInfo.gameOver)
    {
      displayText("Game Over", 256, {0.2f, 0.2f}, {-0.65f, 0.42f}, {1.0f, 0.0f}, {1.0f, 0.25f, 0.0f});
      displayText("Press enter to retry", 256, {0.1f, 0.1f}, {-0.65f, -0.82f}, {1.0f, 0.0f}, {1.0f, 0.25f, 0.0f});
    }
}

void Display::copyRenderData(Logic const &logic)
{
  auto const offset(Vect<2u, float>{// (dim[0] - dim[1]) * 0.25f
      0.0f, 0.0f});

  camera.offset = (camera.offset + offset) * 0.5f - logic.getPlayerPos() * 0.5f - offset;
  displayInfo.time = logic.getTime();
  displayInfo.score = logic.getScore();
  displayInfo.gameOver = logic.getGameOver();
  displayInfo.combo = logic.getCombo();
  displayInfo.bomb = logic.getEntityManager().players[0].getNbBombs();
  displayInfo.ulti = logic.getEntityManager().players[0].getUlti();

  displayInfo.renderables.clear();
  auto const &manager(logic.getEntityManager());

  for (auto &zombie : manager.zombies)
    {
      auto pos(camera.apply(zombie.entity.fixture.pos));

      displayInfo.renderables[TextureHandler::getInstance().getTexture(TextureHandler::TextureList::ZOMBIE)].emplace_back(Renderable{
	  {0.1f * zombie.getAnimationFrame(), 0.0f},
	    {0.1f, 1.0f},
	      Vect<2, double>(pos[0], pos[1] + zombie.getOffset()),
		camera.zoom * static_cast<float>(zombie.entity.fixture.radius * 2.0) * Vect<2u, float>{1.0f, 1.5f},
		(pos[1] + 1.1f) * 0.4f
		});
    }
  for (auto &human : manager.humans)
    {
      auto pos(camera.apply(human.entity.fixture.pos));

      displayInfo.renderables[TextureHandler::getInstance().getTexture(TextureHandler::TextureList::HUMAN)].push_back(Renderable{
	  {0.1f * human.getAnimationFrame(), 0.0f},
	    {0.1f, 1.0f},
	      Vect<2, double>(pos[0], pos[1] + human.getOffset()),
		camera.zoom * static_cast<float>(human.entity.fixture.radius * 2.0) * Vect<2u, float>{1.0f, 1.5f},
		(pos[1] + 1.1f) * 0.4f
		});
    }
  for (auto &player : manager.players)
    {
      auto pos(camera.apply(player.entity.fixture.pos));

      displayInfo.renderables[TextureHandler::getInstance().getTexture(TextureHandler::TextureList::PLAYER)].push_back(Renderable{
	    {0.1f * player.getAnimationFrame(), 0.0f},
	    {0.1f, 1.0f},
	      Vect<2, double>(pos[0], pos[1] + player.getOffset()),
		camera.zoom * static_cast<float>(player.entity.fixture.radius * 2.0f) * Vect<2u, float>{1.0f, 1.5f},
		(pos[1] + 1.1f) * 0.4f
		});
    }
  for (auto &slash : manager.slashes)
    {
      auto pos(camera.apply(slash.entity.fixture.pos));
      TextureHandler::TextureList texture;
      float x_in = 0.2f;
      float y_in = 1.0f;
      float offset = 0;

      if (slash.isHorizontal())
	{
	  texture = TextureHandler::TextureList::SLASH;
	  if (slash.isReversed())
	    x_in = 0.2f;
	  else
	    {
	      x_in = -0.2f;
	      offset = 0.2f;
	    }
	}
      else
	{
	  texture = TextureHandler::TextureList::SLASH2;
	  y_in = slash.isReversed() ? 1.0f : -1.0f;
	}
      displayInfo.renderables[TextureHandler::getInstance().getTexture(texture)].push_back(Renderable{
	  {0.2f * slash.getAnimationFrame() + offset, 0.0f},
	    {x_in, y_in},
	      pos - Vect<2, double>{0.0, 0.02},
		camera.zoom * static_cast<float>(slash.entity.fixture.radius * 2.0f) * Vect<2u, float>{1.0f, 1.5f},
		(pos[1] + 1.1f) * 0.4f
		});
    }
  for (auto &shuriken : manager.shurikens)
    {
      auto pos(camera.apply(shuriken.entity.fixture.pos));

      displayInfo.renderables[TextureHandler::getInstance().getTexture(TextureHandler::TextureList::SHURIKEN)].push_back(Renderable{
	    {0.5f * shuriken.getAnimationFrame(), 0.0f},
	    {0.5f, 1.0f},
	      pos,
		camera.zoom * static_cast<float>(shuriken.entity.fixture.radius * 2.0f) * Vect<2u, float>{1.0f, 1.5f},
		(pos[1] + 1.1f) * 0.4f
		 });
    }
  for (auto &bomb : manager.bombs)
    {
      auto pos(camera.apply(bomb.entity.fixture.pos));

      displayInfo.renderables[TextureHandler::getInstance().getTexture(TextureHandler::TextureList::BOMB_SPRITE)].push_back(Renderable{
	    {0.2f * bomb.getAnimationFrame(), 0.0f},
	    {0.2f, 1.0f},
	      pos,
		camera.zoom * static_cast<float>(bomb.entity.fixture.radius * 2.0f) * Vect<2u, float>{1.0f, 1.5f},
		(pos[1] + 1.1f) * 0.4f
		});
    }
  for (auto &explosion : manager.explosions)
    {
      auto pos(camera.apply(explosion.entity.fixture.pos));

      displayInfo.renderables[TextureHandler::getInstance().getTexture(TextureHandler::TextureList::EXPLOSION)].push_back(Renderable{
	    {0.25f * explosion.getAnimationFrame(), 0.0f},
	    {0.25f, 1.0f},
	    pos - Vect<2, double>{0.0, explosion.entity.fixture.radius / 2},
		camera.zoom * static_cast<float>(explosion.entity.fixture.radius * 2.0f) * Vect<2u, float>{1.0f, 1.5f},
		(pos[1] + 1.1f) * 0.4f
		});
    }
  auto cityMap(logic.getCityMap().getCityMap());
  for (std::size_t i(0); i != 100ul; ++i)
    for (std::size_t j(0); j != 100ul; ++j)
      {
  	auto const &house(cityMap[i][j]);
	auto pos(camera.apply(Vect<2u, double>{static_cast<double>(j), static_cast<double>(i)} + Vect<2u, float>{0.5f, 0.0f}));

	if (!(house.type == BlockType::NONE || house.type == BlockType::ROAD))
	  displayInfo.renderables[TextureHandler::getInstance().getTexture((house.type == BlockType::SHED) ? TextureHandler::TextureList::HOUSE1 :
									   (house.type == BlockType::HOUSE) ? TextureHandler::TextureList::HOUSE2 :
									   (house.type == BlockType::MANSION) ? TextureHandler::TextureList::HOUSE3 :
									   (house.type == BlockType::NONE) ? TextureHandler::TextureList::NONE :
									   (house.type == BlockType::ROAD) ? TextureHandler::TextureList::ROAD :
									   TextureHandler::TextureList::BORDER)].push_back(Renderable{
									       {0.0f, 0.0f},
										 {1.0f, 0.99f},
										   pos,
										     camera.zoom * Vect<2u, float>{1.0f,
										       (house.type == BlockType::SHED) ? 1.1f :
										       (house.type == BlockType::HOUSE) ? 1.24f :
										       (house.type == BlockType::MANSION) ? 1.55f :
										       (house.type == BlockType::NONE) ? 1.0f :
										       (house.type == BlockType::ROAD) ? 1.0f :
										       1.0f},
										       (pos[1] + 1.1f) * 0.4f});
      }
}

bool Display::isRunning() const
{
  return (!glfwWindowShouldClose(window.get()));
}

bool Display::isKeyPressed(int key) const
{
  return glfwGetKey(window.get(), key);
}

Camera const &Display::getCamera() const
{
  return camera;
}

Vect<2u, float> Display::getDim() const
{
  return dim;
}

Vect<2u, float> Display::getSize() const
{
  return size;
}
