#ifndef TEXTUREHANDLER_HPP_
# define TEXTUREHANDLER_HPP_

# include <map>
# include <memory>
# include "my_opengl.hpp"

class TextureHandler
{
public :

  enum class TextureList : std::size_t
    {
      BOYAUX,
      PLANET,
      SWORDRADIUS,
      BULLET,
      ZOMBIE,
      HUMAN,
      PLAYER,
      TEST,
      NONE,
      HOUSE1,
      HOUSE2,
      HOUSE3,
      BOMB,
      BOMBHOLLOW,
      ROAD,
      BORDER,
      SLASH,
      BARFRONT,
      BARBACK,
      SPIN,
      SPINHOLLOW
    };

  static void initTextureHandler();
  static TextureHandler& getInstance();
  static void destroyTextureHandler();

  void addTexture(TextureList, std::string const&);
  Texture getTexture(TextureList) const;

private:

  TextureHandler();
  static std::unique_ptr<TextureHandler> _instance;
  std::map<TextureList, Texture> _textures;
};

#endif /* !TEXTUREHANDLER_HPP_ */
