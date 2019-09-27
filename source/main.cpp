# include <iostream>
# include "Display.hpp"
# include "Logic.hpp"
# include "TextureHandler.hpp"
# include "SoundHandler.hpp"
# include "Input.hpp"
# include <random>
# include <thread>
# include <mutex>

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

    std::mutex lock;
    SoundHandler::getInstance().playMainMusic();
    std::thread thread([&logic, &display, &lock]()
		       {
			 try {
			   while (true)
			     {
			       if (!logic.isRunning())
				 break;
			       logic.tick(lock, display.getCamera());
			     }
			 } catch (std::runtime_error const &e) {
			   std::cerr << "Logic thread encoutered runtime error:" << std::endl
				     << e.what() << std::endl;
			 }
		       });
    try {
      while (display.isRunning())
	{
	  {
	    std::lock_guard<std::mutex> scopedLock(lock);

	    // handle events
	    for (Event ev = Input::pollEvent(); ev; ev = Input::pollEvent())
	      logic.handleEvent(display, ev);
	    logic.checkEvents(display);
	    display.copyRenderData(logic);
	  }
	  display.render();
	  if (logic.getRestart())
	    {
	      logic = Logic(false);
	      SoundHandler::getInstance().playMainMusic();
	    }
	}
    } catch (std::runtime_error const &e) {
      std::cerr << "Display thread encoutered runtime error:" << std::endl
		<< e.what() << std::endl;
    }
    {
      std::lock_guard<std::mutex> scopedLock(lock);
      logic.isRunning() = false;
    }
    thread.join();
  } catch (std::runtime_error const &e) {
    std::cerr << "program encoutered runtime error:" << std::endl
	      << e.what() << std::endl;
    return -1;
  }
}
