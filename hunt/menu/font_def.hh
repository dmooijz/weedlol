#pragma once
#include "../gui/imgui.h"
#include "../utils/XorStr.h"

class font_init
{
public:
	ImFont* basic_font;
public:
	void basic() { ImGuiIO& io = ImGui::GetIO(); basic_font = io.Fonts->AddFontFromFileTTF(_("C:\\WINDOWS\\FONTS\\verdana.ttf"), 16, nullptr, io.Fonts->GetGlyphRangesCyrillic()); }
};

inline auto custom_font = new font_init;