#include "pch.h"
#include "Tank.h"
#include "Globals.h"
#include "Game.h"
#include "Bullet.h"
#include "Bug.h"

IMPLEMENT_RTTI(Tank);

void Tank::OnUpdate(float dt)
{
}

BugBase* Tank::GetBugToShoot() const
{
	for (auto obj : g_Game->objects)
		if (auto bug = dynamic_cast<Bug*>(obj))
			return bug;

	return nullptr;
}

Point Tank::CalcShootDirection(Point target_pos, Point target_dir, float target_vel, float bullet_vel) const
{
	target_pos = { target_pos.x - position.x, target_pos.y - position.y };
	float discriminant4 = bullet_vel * bullet_vel * (target_pos.x * target_pos.x + target_pos.y * target_pos.y) -
		(target_pos.x * target_dir.y - target_pos.y * target_dir.x) * (target_pos.x * target_dir.y - target_pos.y *
			target_dir.x) * target_vel * target_vel;
	float t = (target_pos.x * target_pos.x + target_pos.y * target_pos.y) / (sqrt(discriminant4) -
		(target_pos.x * target_dir.x + target_pos.y * target_dir.y) * target_vel);
	return target_pos / bullet_vel / t + target_dir * target_vel / bullet_vel;

}
