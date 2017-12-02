# include <iostream>
# include "Display.hpp"
# include "Logic.hpp"
# include "TextureHandler.hpp"
# include "SoundHandler.hpp"
# include "Input.hpp"
# include <random>

int main()
{
  std::srand(static_cast<unsigned int>(time(NULL)));
  try { 
    Display display;
   
    struct SoundHandlerInit
    {
      SoundHandlerInit()
      {
        SoundHandler::initSoundHandler();
      }

      ~SoundHandlerInit()
      {
        SoundHandler::destroySoundHandler();
      }
    } SoundHandlerIniter;

    struct TextureHandlerInit
    {
      TextureHandlerInit()
      {
        TextureHandler::initTextureHandler();
      }

      ~TextureHandlerInit()
      {
        TextureHandler::destroyTextureHandler();
      }
    } textureHandlerIniter;
    Logic logic;
    Input::setWindow(display.getWindow());

    SoundHandler::getInstance().playMainMusic();
    while (display.isRunning())
      {
        // handle events
        for (Event ev = Input::pollEvent(); ev; ev = Input::pollEvent())
          logic.handleEvent(display, ev);
        logic.checkEvents(display);

        // update logic
        logic.tick();

        // render
        display.render(logic);
      }

  } catch (std::runtime_error const &e) {
    std::cerr << "program encoutered runtime error:" << std::endl
              << e.what() << std::endl;
    return -1;
  }
}
