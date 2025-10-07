#include "Monster.h"

#include "entities/weapons/Bullet.h"


Monster::Monster(const EntityInit& Einit)
	: LivingEntity{Einit}
{
}

Monster::Monster(SharedEntityInit Einit)
	: LivingEntity{Einit}
{
}


void Monster::setTarget(const Vec2f& target)
{
	targetPosition = target;
}



float Monster::getDamageDealt(float otherDmg, LivingEntity& targetEntity) noexcept
{
	return otherDmg * targetEntity.get(Traits::Damage, Specifier::Current);
}




void Monster::damageOnHit(LivingEntity& targetEntity, Vector<Bullet>& bullets)
{
	if (targetEntity.getNumberWeapons() && bullets.size() > 0)
	{
		for (auto& bullet : bullets)
		{
			if(contains(bullet.current))
			{
				sub(Traits::Life, Specifier::Current, getDamageDealt(bullet.damage, targetEntity));
				bullet.reachedTarget = true;
			}
		}
	}
}












void Monster::update(const Time& dt)
{
	if (dead)
		return;

	
	Vec2f offset{};

	/*if (updateOffset)*/
	offset = applySpeedDT(normalizedDirection(), dt);

	currentPosition += offset;
	sprite.setPosition(currentPosition);
}

void Monster::updateHiting(LivingEntity& targetEntity, Vector<Bullet>& bullets)
{
	updateHitBullet(targetEntity, bullets);

	lifebar.update(get(Traits::Life, Specifier::Current), get(Traits::Life, Specifier::Max), currentPosition, Util::vec2_cast<float>(getCurrentTexture().getSize()));
}

void Monster::updateHitBullet(LivingEntity& targetEntity, Vector<Bullet>& bullets)
{
	damageOnHit(targetEntity, bullets);
		
	if (get(Traits::Life, Specifier::Current) <= 0)
		die();
}

void Monster::updateHitEntity(LivingEntity& targetEntity)
{
}



void Monster::draw(RenderTarget& target, RenderStates states) const
{
	MoveableEntity::draw(target, states);

	target.draw(lifebar);
}