#include "Zombie.hpp"

Zombie::Zombie(Entity const &entity)
  : Mob(entity, 2),
    lead(false),
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

void Zombie::updateTarget(Entity& newTarget)
{
  if (!target || (newTarget.fixture.pos - entity.fixture.pos).length2() < (*target - entity.fixture.pos).length2()) {
    target = newTarget.fixture.pos;
  }
}

void Zombie::update(std::vector<ZombieDetectionRange> &detectionRanges)
{
  anim.animate(entity);
  if (!--detectionCooldown) {
    if (detectionRanges.size() > 4)
      ++detectionCooldown;
    else
      {
	detectionCooldown = detectionTickBetween();
	detectionRanges.emplace_back(*this);
	target.reset();
      }
  }
  if (target && (*target - entity.fixture.pos).length2() > 0.1)
    entity.fixture.speed += (*target - entity.fixture.pos).normalized() * 0.001;
}

float Zombie::getAnimationFrame() const
{
  return anim.getAnimationFrame();
}
