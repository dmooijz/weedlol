#include "hook.hh"

#include <iostream>

#include "../menu/menu.hh"
#include "../cheat/player/base.hh"
#include "../sdk/i_game_framework.hh"


typedef HRESULT(WINAPI* orig_present)(IDXGISwapChain* sc, uint32_t sync, uint32_t flags);
orig_present present_t;

ID3D11RenderTargetView* rtv = nullptr;
ID3D11DeviceContext* device_context = nullptr;
ID3D11Device* device = nullptr;

inline WNDPROC orig_wnd;
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
constexpr int menu_key = VK_HOME;

void input() {
	if (cstm->custom_key(menu_key)&0x1) {
		menu::is_opened = !(menu::is_opened);
	}
	if (menu::zombie_color) {
		cheat::zombie_bone();
	}
	if(menu::player)
	{
		cheat::player_bone();
	}
	if(menu::dog)
	{
		cheat::dogs();
	}
	if(menu::immolator)
	{
		cheat::immolator();
	}
}



HRESULT hook::hook_present(IDXGISwapChain* sc, uint32_t sync, uint32_t flags) {
	if (!device) {
		static HWND h_wnd = nullptr;
		static float height = 0;
		static float width = 0;
		sc->GetDevice(__uuidof(device), reinterpret_cast<PVOID*>(&device));
		device->GetImmediateContext(&device_context);

		ID3D11Texture2D* render_target = nullptr;
		sc->GetBuffer(0, __uuidof(render_target), reinterpret_cast<PVOID*>(&render_target));
		device->CreateRenderTargetView(render_target, nullptr, &rtv);
		render_target->Release();
		ID3D11Texture2D* back_buffer = 0;
		sc->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<PVOID*>(&back_buffer));
		D3D11_TEXTURE2D_DESC back_buffer_desc = { 0 };
		back_buffer->GetDesc(&back_buffer_desc);

		if (!h_wnd)
		{
			h_wnd = FindWindowW(_(L"CryEngine"), _(L"Hunt: Showdown"));
			if (!h_wnd)
				h_wnd = GetForegroundWindow();
		}
		if (!width) {
			orig_wnd = reinterpret_cast<WNDPROC>(SetWindowLongPtr(h_wnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(wnd_proc)));
		}

		width = static_cast<float>(back_buffer_desc.Width);
		height = static_cast<float>(back_buffer_desc.Height);
		back_buffer->Release();

		custom_font->basic();

		ImGui_ImplDX11_Init(h_wnd, device, device_context);
		ImGui_ImplDX11_CreateDeviceObjects();
	}
	device_context->OMSetRenderTargets(1, &rtv, nullptr);
	auto& window = begin_scene();
	menu::render();
	input();
	end_sceen(window);
	return present_t(sc, sync, flags);
}

void hook::setup()
{
	std::cout << _("[+] Hooking\n");

	if (!utils::get_module_base(_(L"GameOverlayRenderer64.dll")))
	{
		return;
	}
	const uintptr_t base_addr = utils::get_module_base(_(L"GameOverlayRenderer64.dll"));
	uintptr_t pr = base_addr + 0x89100;
	if (pr)
		init(pr, reinterpret_cast<long long>(hook_present), reinterpret_cast<long long*>(&present_t));

	std::cout << _("[+] Hooked\n");
}

void hook::init(long long address, long long function, long long* original)
{
	static uintptr_t hk_addr;
	if (!hk_addr)
	{
		const uintptr_t base_addr = utils::get_module_base(_(L"GameOverlayRenderer64.dll"));
		hk_addr = base_addr + 0x82E80;
	}

	const auto hk = ((__int64(__fastcall*)(__int64 address, __int64 function, __int64* original, __int64 last_arg))(
		hk_addr));

	hk(static_cast<long long>(address), static_cast<long long>(function), original, static_cast<long long>(1));
}

ImGuiWindow& hook::begin_scene()
{
	ImGui_ImplDX11_NewFrame();
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));
	ImGui::Begin((_("##scene")), nullptr, ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar);
	auto& io = ImGui::GetIO();
	ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	ImGui::SetWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), ImGuiCond_Always);
	return *ImGui::GetCurrentWindow();
}

void hook::end_sceen(ImGuiWindow& window)
{
	window.DrawList->PushClipRectFullScreen();
	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar(2);
	ImGui::Render();
}

LRESULT hook::wnd_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
	case WM_MOUSEMOVE:
		custom::cursor_x = static_cast<short>(lParam);
		custom::cursor_y = static_cast<short>(lParam >> 16);
		break;
	case WM_LBUTTONDOWN:
		custom::pressed_key[VK_LBUTTON] = true;
		break;
	case WM_LBUTTONUP:
		custom::pressed_key[VK_LBUTTON] = false;
		break;
	case WM_RBUTTONDOWN:
		custom::pressed_key[VK_RBUTTON] = true;
		break;
	case WM_RBUTTONUP:
		custom::pressed_key[VK_RBUTTON] = false;
		break;
	case WM_MBUTTONDOWN:
		custom::pressed_key[VK_MBUTTON] = true;
		break;
	case WM_MBUTTONUP:
		custom::pressed_key[VK_MBUTTON] = false;
		break;
	case WM_XBUTTONDOWN:
	{
		const UINT button = GET_XBUTTON_WPARAM(wParam);
		if (button == XBUTTON1)
		{
			custom::pressed_key[VK_XBUTTON1] = true;
		}
		else if (button == XBUTTON2)
		{
			custom::pressed_key[VK_XBUTTON2] = true;
		}
		break;
	}
	case WM_XBUTTONUP:
	{
		const UINT button = GET_XBUTTON_WPARAM(wParam);
		if (button == XBUTTON1)
		{
			custom::pressed_key[VK_XBUTTON1] = false;
		}
		else if (button == XBUTTON2)
		{
			custom::pressed_key[VK_XBUTTON2] = false;
		}
		break;
	}
	case WM_KEYDOWN:
		custom::pressed_key[wParam] = true;
		break;
	case WM_KEYUP:
		custom::pressed_key[wParam] = false;
		break;
	default: break;
	}
	if (menu::is_opened && ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
		return true;

	return CallWindowProc(orig_wnd, hwnd, msg, wParam, lParam);
}