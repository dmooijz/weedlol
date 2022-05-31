#pragma once
#include "../i_renderer.hh"
#include "../i_skeleton_pose.hh"
#include "../../utils/matrix.hh"
#include "../i_entity.hh"
#include "../../gui/imgui.h"
#include "../../utils/XorStr.h"
class deps
{
public:
	static bool world_to_screen(const math::vec3_t& origin, math::vec3_t& screen)
	{
		float x, y, z;
		i_renderer* get_render = i_renderer::get_i_renderer();
		if (!get_render) return false;
		get_render->project_to_screen(origin.x, origin.y, origin.z, &x, &y, &z);
		screen.x = x * (get_render->get_width() / 100.0f);
		screen.y = y * (get_render->get_height() / 100.0f);
		screen.z = z * 1.0f;

		return ((screen.z < 1.0f));
	}

	static math::vec3_t get_bone(math::matrix3x4_t m_world, i_skeleton_pos* m_skeleton, __int16 bone_id)
	{
		return m_world * m_skeleton->get_abs_joint_by_id(bone_id).t;
	}

	static math::vec3_t get_bone_name(i_entity* p_entity, const char* bone_name)
	{
		if (!p_entity) return {};

		if (bone_name == nullptr) return {};

		if (!bone_name) return {};

		i_character_instance* p_character_instance = p_entity->GetCharacter(0);
		if (!p_character_instance) return {};

		i_skeleton_pos* p_skeleton_pos = p_character_instance->get_i_skeleton_pose();
		if (!p_skeleton_pos) return {};

		i_default_skeleton& p_default_skeleton = p_character_instance->get_i_defualt_skeleton();
		const __int16 bone_id = p_default_skeleton.get_joint_id_by_name(bone_name);

		return p_entity->get_world_tm() * p_skeleton_pos->get_abs_joint_by_id(bone_id).t;
	}

	static void __fastcall bone_line(const char* bone_1, const char* bone_2, i_entity* p_entity, ImColor color)
	{
		const math::vec3_t start_bone = get_bone_name(p_entity, bone_1);
		const math::vec3_t end_bone = get_bone_name(p_entity, bone_2);
		math::vec3_t start_bone_out = {};
		math::vec3_t end_bone_out = {};
		if (!world_to_screen(start_bone, start_bone_out) || !world_to_screen(end_bone, end_bone_out)) return;
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(start_bone_out.x, start_bone_out.y), ImVec2(end_bone_out.x, end_bone_out.y), color, 2);
	}
};

class skeleton
{
public:
	static void __fastcall draw_left_arm(i_entity* p_entity, ImColor color)
	{
		deps::bone_line(_("neck"), _("L_upperarm"), p_entity, color);
		deps::bone_line(_("L_upperarm"), _("L_upperarm_twist"), p_entity, color);
		deps::bone_line(_("L_upperarm_twist"), _("L_forearm"), p_entity, color);
		deps::bone_line(_("L_forearm"), _("L_forearm_twist"), p_entity, color);
		deps::bone_line(_("L_forearm_twist"), _("L_hand"), p_entity, color);
	}

	static void __fastcall draw_right_arm(i_entity* p_entity, ImColor color)
	{
		deps::bone_line(_("neck"), _("R_upperarm"), p_entity, color);
		deps::bone_line(_("R_upperarm"), _("R_upperarm_twist"), p_entity, color);
		deps::bone_line(_("R_upperarm_twist"), _("R_forearm"), p_entity, color);
		deps::bone_line(_("R_forearm"), _("R_forearm_twist"), p_entity, color);
		deps::bone_line(_("R_forearm_twist"), _("R_hand"), p_entity, color);
	}

	static void __fastcall draw_left_leg(i_entity* p_entity, ImColor color)
	{
		deps::bone_line(_("pelvis"), _("L_thigh"), p_entity, color);
		deps::bone_line(_("L_thigh"), _("L_thigh_twist"), p_entity, color);
		deps::bone_line(_("L_thigh_twist"), _("L_Calf"), p_entity, color);
		deps::bone_line(_("L_Calf"), _("L_foot"), p_entity, color);
	}

	static void __fastcall draw_right_leg(i_entity* p_entity, ImColor color)
	{
		deps::bone_line(_("pelvis"), _("R_thigh"), p_entity, color);
		deps::bone_line(_("R_thigh"), _("R_thigh_twist"), p_entity, color);
		deps::bone_line(_("R_thigh_twist"), _("R_Calf"), p_entity, color);
		deps::bone_line(_("R_Calf"), _("R_foot"), p_entity, color);
	}

	static void __fastcall draw_head(i_entity* p_entity, ImColor color)
	{
		deps::bone_line(_("pelvis"), _("spine01"), p_entity, color);
		deps::bone_line(_("spine01"), _("spine02"), p_entity, color);
		deps::bone_line(_("spine02"), _("spine03"), p_entity, color);
		deps::bone_line(_("spine03"), _("spine04"), p_entity, color);
		deps::bone_line(_("spine04"), _("neck"), p_entity, color);
		deps::bone_line(_("neck"), _("head"), p_entity, color);
	}

	static void __fastcall draw_skeleton(i_entity* p_entity, ImColor color) {
		draw_left_leg(p_entity, color);
		draw_right_leg(p_entity, color);
		draw_left_arm(p_entity, color);
		draw_right_arm(p_entity, color);
		draw_head(p_entity, color);
	}
};