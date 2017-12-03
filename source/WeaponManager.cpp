#include "WeaponManager.hpp"

WeaponManager::WeaponManager()
{
}

void WeaponManager::update()
{
  static constexpr auto lifetimeCheck = [](auto container)
    {
      container.erase(container.begin(), std::remove_if(container.begin(), container.end(),
							[](auto const &elem)
							{
							  return elem.lifetime > 0;
							}));
    };
  lifetimeCheck(slashes);
  lifetimeCheck(explosions);
  for (auto it = bombs.begin(); it != bombs.end(); ++it)
    {
      if (it->explodes || it->lifetime <= 0)
	{
	  explosions.emplace_back(it->entity.fixture.pos, 0.5, 1);
	  explosions.emplace_back(it->entity.fixture.pos, 0.25, 2);
	  it = bombs.erase(it);
	}
    }
  for (auto it = shurikens.begin(); it != shurikens.end(); ++it)
    if (it->touched || it->lifetime <= 0)
      it = shurikens.erase(it);
}
