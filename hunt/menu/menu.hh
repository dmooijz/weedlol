#pragma once
#include "font_def.hh"

class menu {
public:
	inline static bool is_opened = false;

	inline static bool zombie = false;
	inline static bool player = false;
	inline static bool dog = false;
	inline static bool immolator = false;

	inline static float name_color[4] = { 255, 255, 255, 255 };
	inline static float player_color[4] = { 255, 255, 255, 255 };
	inline static float zombie_color[4] = { 255, 255, 255, 255 };
	inline static float dog_color[4] = { 255, 255, 255, 255 };
	inline static float immolator_color[4] = { 255, 255, 255, 255 };
	inline static float npc_color[4] = { 255, 255, 255, 255 };
	inline static float npc_name_color[4] = { 255, 255, 255, 255 };

	menu();
	static void render();
};