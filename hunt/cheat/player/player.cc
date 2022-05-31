#include "base.hh"

float player::dist_to(math::vec3_t first, math::vec3_t second)
{
	math::vec3_t delta;
	delta.x = first.x - second.x;
	delta.y = first.y - second.y;
	delta.z = first.z - second.z;

	return sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
}
