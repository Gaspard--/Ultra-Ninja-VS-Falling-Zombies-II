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
#include "Bind.hpp"

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

  void displayRenderableAsHUD(Renderable const& renderable, GLuint texture);

  Vect<2u, float> getDim() const;

  Vect<2u, float> getSize() const;

  Camera const &getCamera() const;

  void render();
  bool isRunning() const;
  bool isKeyPressed(int key) const;

  void copyRenderData(Logic const &);

  template<class IT>
  void displayRenderables(IT begin, GLuint count, GLuint texture)
  {
    Bind<RenderContext> bind(textureContext);
    GLuint bufferSize(count * 5u * 6u);
    std::unique_ptr<float[]> buffer(new float[bufferSize]);

    for (std::size_t i(0u); i != count; ++i)
      {
	auto renderable(*begin);

	for (unsigned int j(0u); j != 6u; ++j)
	  {
	    constexpr std::array<Vect<2u, float>, 6u> const corners
	    {
	      Vect<2u, float>{0.0f, 0.0f},
	      Vect<2u, float>{1.0f, 0.0f},
	      Vect<2u, float>{0.0f, 1.0f},
	      Vect<2u, float>{0.0f, 1.0f},
	      Vect<2u, float>{1.0f, 0.0f},
	      Vect<2u, float>{1.0f, 1.0f}
	    };
	    Vect<2u, float> const corner(corners[j]);
	    Vect<2u, float> const sourceCorner(renderable.sourcePos + corner * renderable.sourceSize);
	    Vect<2u, float> const destCorner(renderable.destPos + ((corner - Vect<2u, float>{0.5f, 0.0f}) * renderable.destSize));

	    std::copy(&sourceCorner[0u], &sourceCorner[2u], &buffer[(j + i * 6u) * 5u]);
	    std::copy(&destCorner[0u], &destCorner[2u], &buffer[(j + i * 6u) * 5u + 2u]);
	    buffer[(j + i * 6u) * 5u + 4u] = renderable.depth;
	  }
	++begin;
      }
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
    my_opengl::setUniform(dim, "dim", textureContext.program);
    my_opengl::setUniform(0u, "tex", textureContext.program);
    glBufferData(GL_ARRAY_BUFFER, bufferSize * sizeof(float), buffer.get(), GL_STATIC_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, 6 * count);
  }

};
