#pragma once
#include "../../utils/Vec3.hh"

class cheat {
public:
	static void zombie_bone();
	static void player_bone();
	static void dogs();
	static void immolator();
};

class player
{
public:
	static float dist_to(math::vec3_t first, math::vec3_t second);
};