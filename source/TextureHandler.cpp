#include "TextureHandler.hpp"

std::unique_ptr<TextureHandler> TextureHandler::_instance(nullptr);

TextureHandler::TextureHandler()
{
}

void TextureHandler::initTextureHandler()
{
  _instance.reset(new TextureHandler());
  _instance->addTexture(TextureList::BOYAUX, "resources/boyaux.bmp");
  // Already loaded in display.cpp
  // _instance->addTexture(PLANET, "resources/planet.bmp");
  _instance->addTexture(TextureList::SWORDRADIUS, "resources/swordRadius.bmp");
  _instance->addTexture(TextureList::BULLET, "resources/bite.bmp");
  _instance->addTexture(TextureList::ZOMBIE, "resources/ZombieSpriteSheet.bmp");
  _instance->addTexture(TextureList::PLAYER, "resources/PlayerSpriteSheet.bmp");
  _instance->addTexture(TextureList::HUMAN, "resources/PlayerSpriteSheet.bmp");
  _instance->addTexture(TextureList::HOUSE1, "resources/Shed.bmp");
  _instance->addTexture(TextureList::HOUSE2, "resources/House.bmp");
  _instance->addTexture(TextureList::HOUSE3, "resources/Mansion.bmp");
  _instance->addTexture(TextureList::TEST, "resources/test.bmp");
}

TextureHandler& TextureHandler::getInstance()
{
  return *_instance;
}

void TextureHandler::destroyTextureHandler()
{
  _instance.reset(nullptr);
}

void TextureHandler::addTexture(TextureList id, std::string const& path)
{
  _instance->_textures[id] = my_opengl::loadTexture(path);
}

Texture TextureHandler::getTexture(TextureList id) const
{
  return (_instance->_textures[id]);
}
