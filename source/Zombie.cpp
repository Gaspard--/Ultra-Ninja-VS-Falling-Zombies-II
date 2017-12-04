#include "Zombie.hpp"

Zombie::Zombie(Entity const &entity)
  : Mob(entity, 2),
    lead(false),
    hasTarget(false),
    target(),
    detectionCooldown(detectionTickBetween()),
    landingSpeed(0.005)
{
  offsetY = 1.0;
}

Zombie::Zombie(Human const &villager)
  : Zombie(villager.entity)
{
  landingSpeed = 0.0;
  offsetY = 0.0;
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

void Zombie::updateTarget(Entity const& newTarget)
{
  if (!hasTarget || (newTarget.fixture.pos - entity.fixture.pos).length2() < (target - entity.fixture.pos).length2()) {
    target = newTarget.fixture.pos;
    hasTarget = true;
  }
}

void Zombie::handleFall()
{
  if (landingSpeed < 0.01)
    landingSpeed += 0.0005;
  offsetY -= landingSpeed;
}

void Zombie::update(std::vector<ZombieDetectionRange> &detectionRanges)
{
  if (offsetY > 0.0)
    return handleFall();
  else
    offsetY = 0.0;
  anim.animate(entity);
  if (!--detectionCooldown)
    {
      if (detectionRanges.size() > 4)
	++detectionCooldown;
      else
	{
	  detectionCooldown = detectionTickBetween();
	  detectionRanges.emplace_back(*this);
	  hasTarget = false;
	}
    }
  if (hasTarget && (target - entity.fixture.pos).length2() > 0.1)
    entity.fixture.speed += (target - entity.fixture.pos).normalized() * 0.001;
}

float Zombie::getAnimationFrame() const
{
  return anim.getAnimationFrame();
}
