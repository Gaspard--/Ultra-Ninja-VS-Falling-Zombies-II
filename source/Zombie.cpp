#include "Zombie.hpp"

Zombie::Zombie(Entity const &entity)
  : Mob(entity, 2),
    lead(false),
    hasTarget(false),
    target(),
    detectionCooldown(detectionTickBetween())
{
}

Zombie::Zombie(Human const &villager)
  : Zombie(villager.entity)
{
}

Zombie::~Zombie()
{
}

void Zombie::setLead(bool lead)
{
  this->lead = lead;
}

bool const& Zombie::getLead() const
{
  return lead;
}

void Zombie::infectHuman(Human &villager) const
{
  villager.setInfected(true);
}

bool Zombie::updateTarget(Entity const& newTarget, CityMap const &cityMap)
{
  if (!hasTarget)
    if ((newTarget.fixture.pos - entity.fixture.pos).length2() <
	(target - entity.fixture.pos).length2())
      {
	target = findPath(newTarget, cityMap);
	hasTarget = true;
	return (true);
      }
  return (false);
}

void Zombie::update(std::vector<ZombieDetectionRange> &detectionRanges)
{
  anim.animate(entity);
  if (!--detectionCooldown) {
    if (detectionRanges.size() >= 16)
      detectionCooldown += 1 + (rand() & 7);
    else
      {
	detectionCooldown = detectionTickBetween();
	detectionRanges.emplace_back(*this);
	hasTarget = false;
      }
  }
  if (hasTarget && (target - entity.fixture.pos).length2() > 0.1)
    entity.fixture.speed += (target - entity.fixture.pos).normalized() * 0.0003;
}

float Zombie::getAnimationFrame() const
{
  return anim.getAnimationFrame();
}
