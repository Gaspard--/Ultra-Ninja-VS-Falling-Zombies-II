#include <iostream>
#include <algorithm>
#include <memory>
#include "SoundHandler.hpp"

std::unique_ptr<SoundHandler> SoundHandler::_instance(nullptr);

SoundHandler::SoundHandler()
{
}

void SoundHandler::initSoundHandler()
{
  _instance.reset(new SoundHandler());
  if (!_instance->mainMusic.openFromFile("resources/Ken_new_Hope_(loop).wav"))
    throw ("Music not charged");
  _instance->addSoundBuffer(SLASH, "resources/dash.wav");
  _instance->addSoundBuffer(CIRCLE_ATTACK, "resources/circle_attack.wav");
  _instance->addSoundBuffer(SHURIKEN, "resources/shuriken.wav");
  _instance->addSoundBuffer(EXPLOSION, "resources/explosion.wav");
  _instance->addSoundBuffer(FESSES, "resources/fesses.wav");
}

SoundHandler& SoundHandler::getInstance()
{
  return *_instance;
}

void SoundHandler::destroySoundHandler()
{
  _instance.reset(nullptr);
}

void SoundHandler::playMainMusic()
{
  mainMusic.setLoop(true);
  mainMusic.setVolume(30);
  mainMusic.play();
}

void SoundHandler::playSound(SoundList id, float volume)
{
  auto sound = std::make_unique<sf::Sound>();
  sound->setBuffer(*_instance->getSoundBuffer(id));
  sound->setLoop(false);
  sound->setVolume(volume);
  sound->play();
  _instance->_soundsPlaying.push_back(std::move(sound));
}

void SoundHandler::deleteSounds()
{
  _soundsPlaying.erase(std::remove_if(_soundsPlaying.begin(), _soundsPlaying.end(),
			      [](auto const &elem)
			      {
				return elem->getStatus() != sf::SoundSource::Status::Playing;
			      }),
	       _soundsPlaying.end());
}

void SoundHandler::addSoundBuffer(SoundList id, std::string const& path)
{
  _instance->_sound[id] = new sf::SoundBuffer();
  _instance->_sound[id]->loadFromFile(path);
}

sf::SoundBuffer* SoundHandler::getSoundBuffer(SoundList id) const
{
  return (_instance->_sound[id]);
}
