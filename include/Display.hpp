#pragma once

#include <memory>
#include "Vect.hpp"
#include "RenderContext.hpp"
#include "my_opengl.hpp"
#include "FreeTypeLib.hpp"
#include "Entity.hpp"
#include "Rect.hpp"
#include "Logic.hpp"
#include "RenderTexture.hpp"
#include "Camera.hpp"
#include "DisplayInfo.hpp"

class Display
{
private:
  struct GlfwContext
  {
    GlfwContext();
    ~GlfwContext();
  } glfwContext;

  Camera camera;

  std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> window;
  FreeTypeLib fontHandler;
  RenderContext textureContext;
  glBuffer textureBuffer;
  RenderContext rectContext;
  glBuffer rectBuffer;
  RenderContext textContext;
  glBuffer textBuffer;
  Texture planet;
  Texture planetBackground;
  Texture background;
  Texture bloodSpray[3];
  Texture mobSpray[3];
  RenderTexture planetRenderTexture; 
  Vect<2u, float> size;
  Vect<2u, float> dim;

  DisplayInfo displayInfo;

public:
  Display();
  ~Display();

  GLFWwindow *getWindow() const;

  void displayText(std::string const &txt, unsigned int fontSize, Vect<2u, float> step, Vect<2u, float> textPos,  Vect<2u, float> rotation, Vect<3u, float> color);

  void displayRect(Rect const &);

  void displayInterface();

  /**
   * Displays a renderable in the world.
   * Optional rotation argument rotates the renderable around 0, 0
   * (for most world elements this should be the position of the player * {1, -1})
   * See Renderable for details on how renderables are rendered
   * This function is not suitable to render GUI
   */
  void displayRenderable(Renderable const& renderable);

  void displayRenderableAsHUD(Renderable const& renderable);

  Vect<2u, float> getDim() const;

  Vect<2u, float> getSize() const;

  Camera const &getCamera() const;

  void render();
  bool isRunning() const;
  bool isKeyPressed(int key) const;

  void copyRenderData(Logic const &);
};
