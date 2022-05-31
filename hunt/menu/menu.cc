#include "menu.hh"

auto page = 5;

menu::menu() = default;

void menu::render() {
	ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_FirstUseEver);
	ImGui::GetStyle().WindowRounding = 0.0f;
	static float		window_size = 0.f;
	constexpr ImGuiWindowFlags menu_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar;
	constexpr ImGuiColorEditFlags col_edit_flags = ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_Uint8;
	if (is_opened)
	{
		ImGui::Begin(_("HYPERBONE"), &is_opened, menu_flags);
		ImGui::BeginChild(_("child"), ImVec2(386 * window_size, 378 * window_size), false, menu_flags);
		ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.65f);
		ImGui::PushItemWidth(140);
		const auto window_pos = ImGui::GetWindowPos();
		const auto draw = ImGui::GetWindowDrawList();
		draw->AddRectFilled(window_pos, ImVec2(window_pos.x + 570, window_pos.y + 380), IM_COL32(1, 1, 1, 220), 12); //right background frame
		draw->AddRectFilledMultiColor(ImVec2(window_pos.x + 182, window_pos.y + 0), ImVec2(window_pos.x + 8, window_pos.y + 370),
			IM_COL32(1, 1, 1, 255), IM_COL32(1, 1, 1, 255),
			IM_COL32(1, 1, 1, 255), IM_COL32(1, 1, 1, 255));
		draw->AddRectFilled(window_pos, ImVec2(window_pos.x + 180, window_pos.y + 380), IM_COL32(1, 1, 1, 255));
		if (ImGui::Button(_("aimbot"), ImVec2(70, 70)))
		{
			page = 0;
		}
		if (ImGui::Button(_("visual"), ImVec2(70, 70)))
		{
			page = 1;
		}
		if (ImGui::Button(_("misc"), ImVec2(70, 70)))
		{
			page = 2;
		}
		if (ImGui::Button(_("colors"), ImVec2(70, 70)))
		{
			page = 3;
		}
		ImGui::EndChild();



		switch (page)
		{
		case 0:
			ImGui::SetCursorPos(ImVec2(130, 85));
			ImGui::BeginChild(_("child2"), ImVec2(250, 300), false);
			ImGui::EndChild();
			break;
		case 1:
			ImGui::SetCursorPos(ImVec2(130, 85));
			ImGui::BeginChild(_("child3"), ImVec2(250, 300), false);
			ImGui::Checkbox(_("Zombie esp"), &zombie);
			ImGui::Checkbox(_("Player esp"), &player);
			ImGui::Checkbox(_("Dog esp"), &dog);
			ImGui::Checkbox(_("Immolator esp"), &immolator);
			ImGui::EndChild();
			break;
		case 2:
			ImGui::SetCursorPos(ImVec2(130, 85));
			ImGui::BeginChild(_("child4"), ImVec2(250, 300), false);
			ImGui::EndChild();
			break;
		case 3:
			ImGui::SetCursorPos(ImVec2(130, 85));
			ImGui::BeginChild(_("child5"), ImVec2(250, 300), false);
			ImGui::SetColorEditOptions(col_edit_flags);
			ImGui::ColorEdit4(_("Zombie Color"), zombie_color);
			ImGui::ColorEdit4(_("Player Color"), player_color);
			ImGui::ColorEdit4(_("Dog Color"), dog_color);
			ImGui::ColorEdit4(_("Immolator Color"), immolator_color);
			ImGui::EndChild();
			break;
		}
		ImGui::End();
	}
}