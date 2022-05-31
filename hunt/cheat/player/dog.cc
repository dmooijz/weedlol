#include <iostream>
#include <string>

#include "base.hh"
#include "../../sdk/dependencies/depend.hh"
#include "../../utils/XorStr.h"
#include "../../gui/imgui.h"
#include "../../sdk/i_game_framework.hh"
#include "../../sdk/i_entity_system.hh"
#include "../../sdk/dependencies/depend.hh"
#include "../../menu/menu.hh"

void cheat::dogs() {
    math::vec3_t screen;
    i_game_framwork* p_game_framwork = i_game_framwork::get_i_game_framwork();
    if (!p_game_framwork) return;
    i_entity* p_local_entity = p_game_framwork->GetClientEntity();
    if (!p_local_entity) return;
    i_entity_system* p_system = i_entity_system::get_i_entity_system();
    if (!p_system) return;
    i_entity_it* p_entity_iterator;
    p_system->get_entity_iterator(&p_entity_iterator);
    if (!p_entity_iterator) return;
    p_entity_iterator->MoveFirst();
    i_entity* p_entity = nullptr;
    while (!p_entity_iterator->IsEnd())
    {
        p_entity = p_entity_iterator->Next();
        if (p_entity == p_local_entity) continue;

        i_entity_class* p_entity_class = p_entity->get_class();
        if (!p_entity_class) continue;

        const auto get_name = p_entity_class->get_name();
        if (!get_name) continue;;
        if (strstr(get_name, _("dog_base")))
        {
            const float* b_color = menu::dog_color;

            if (auto root_bone = deps::get_bone_name(p_entity, _("root")); deps::world_to_screen(root_bone, screen))
            {
                const ImVec2 calc_size = ImGui::CalcTextSize(_("Dog"), nullptr, false);
                ImGui::GetOverlayDrawList()->AddText(ImVec2(screen.x - calc_size.x / 2 - 1, screen.y), ImColor{ b_color[0], b_color[1], b_color[2], b_color[3] }, _("Dog"));

                int distance = player::dist_to(p_entity->get_pos(), p_local_entity->get_pos());

                char buffer[120];
                sprintf_s(buffer, _("[%d m]"), distance);

                const ImVec2 calc_size_distance = ImGui::CalcTextSize(buffer, nullptr, false);
                ImGui::GetOverlayDrawList()->AddText(ImVec2(screen.x - calc_size_distance.x / 2 - 1, screen.y + 15), ImColor{ b_color[0], b_color[1], b_color[2], b_color[3] }, buffer);
            }
        }
    }
}