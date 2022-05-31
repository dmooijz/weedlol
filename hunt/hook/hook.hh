#pragma once
#include "../gui/imgui.h"
#include "../gui/imgui_impl_dx11.h"
#include "../gui/imgui_internal.h"
#include "../utils/Vec2.hh"
#include "../cheat/addresses/addr.hh"
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")


class hook {
public:
	static void setup();
	static void init(long long address, long long function, long long* original);
	static HRESULT hook_present(IDXGISwapChain* sc, uint32_t sync, uint32_t flags);
	static LRESULT WINAPI wnd_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static ImGuiWindow& begin_scene();
	static void end_sceen(ImGuiWindow& window);
};

class custom {
public:
	inline static int cursor_x, cursor_y = {};
	inline static bool pressed_key[256] = {};
	static c_vec get_cursor_pos() {
		return c_vec{cursor_x, cursor_y};
	}

	static bool custom_key(const int key) {
		return pressed_key[key] == 1 ? true : false &0x1;
	}
};

inline auto cstm = new custom;