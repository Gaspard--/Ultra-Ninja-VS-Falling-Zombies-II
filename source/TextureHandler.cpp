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
  _instance->addTexture(TextureList::HUMAN, "resources/CitizenSpriteSheet.bmp");
  _instance->addTexture(TextureList::GRASS, "resources/grass.bmp");
  _instance->addTexture(TextureList::NONE, "resources/grass.bmp");
  _instance->addTexture(TextureList::HOUSE1, "resources/Shed.bmp");
  _instance->addTexture(TextureList::HOUSE2, "resources/House.bmp");
  _instance->addTexture(TextureList::HOUSE3, "resources/Mansion.bmp");
  _instance->addTexture(TextureList::BORDER, "resources/Border.bmp");
  _instance->addTexture(TextureList::TEST, "resources/test.bmp");
  _instance->addTexture(TextureList::BOMB, "resources/Bomb.bmp");
  _instance->addTexture(TextureList::BOMBHOLLOW, "resources/BombHollow.bmp");
  _instance->addTexture(TextureList::SLASH, "resources/SlashSpriteSheet.bmp");
  _instance->addTexture(TextureList::SLASH2, "resources/Slash2SpriteSheet.bmp");
  _instance->addTexture(TextureList::SHURIKEN, "resources/ShurikenSpriteSheet.bmp");
  _instance->addTexture(TextureList::BARFRONT, "resources/BarFront.bmp");
  _instance->addTexture(TextureList::BARBACK, "resources/BarBack.bmp");
  _instance->addTexture(TextureList::SPIN, "resources/Spin.bmp");
  _instance->addTexture(TextureList::SPINHOLLOW, "resources/SpinHollow.bmp");
  _instance->addTexture(TextureList::BOMB_SPRITE, "resources/BombSpriteSheet.bmp");
  _instance->addTexture(TextureList::EXPLOSION, "resources/ExplosionSpriteSheet.bmp");
  _instance->addTexture(TextureList::ARROW, "resources/arrow.bmp");
  _instance->addTexture(TextureList::BLOOD, "resources/BloodSplaterSpriteSheet.bmp");
  _instance->addTexture(TextureList::TUTO, "resources/Tuto.bmp");
  _instance->addTexture(TextureList::FLESH_SPRITE, "resources/GutsSpriteSheet.bmp");
  _instance->addTexture(TextureList::ZOMBIEHEAD, "resources/ZombieHead.bmp");
  _instance->addTexture(TextureList::HUMANHEAD, "resources/CitizenHead.bmp");
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
  return (_instance->_textures.at(id));
}
