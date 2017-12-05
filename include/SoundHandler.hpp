#ifndef SOUNDHANDLER_HPP_
# define SOUNDHANDLER_HPP_

# include <map>
# include <array>
# include <memory>
# include <SFML/Audio.hpp>

class SoundHandler
{
public:

  enum SoundList
    {
      DASH,
      CIRCLE_ATTACK,
      EXPLOSION,
      SHURIKEN,
    };

  static void initSoundHandler();
  static SoundHandler& getInstance();
  static void destroySoundHandler();

  void playMainMusic();
  void playSound(SoundList, float = 100.0f);
  void deleteSounds();
  void addSoundBuffer(SoundList, std::string const&);
  sf::SoundBuffer* getSoundBuffer(SoundList) const;

private:

  SoundHandler();

  static std::unique_ptr<SoundHandler> _instance;

  sf::Music mainMusic;
  std::map<SoundList, sf::SoundBuffer*> _sound;
  std::vector<sf::Sound *> _soundsPlaying;
};

#endif /* !SOUNDHANDLER_HPP_ */
