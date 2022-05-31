#include "hook/hook.hh"


bool __stdcall DllMain(HMODULE module, DWORD r, LPVOID res)
{
	if(r == 1)
	{
		hook::setup();
	}
}