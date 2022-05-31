#include "utils.hh"

uintptr_t utils::get_module_base(const wchar_t* mod_name)
{
	const auto p_peb = reinterpret_cast<PPEB64>(__readgsqword(0x60));

	for (auto p_list_entry = reinterpret_cast<PLIST_ENTRY64>(p_peb->Ldr->InLoadOrderModuleList.Flink);
		p_list_entry != &p_peb->Ldr->InMemoryOrderModuleList;
		p_list_entry = reinterpret_cast<PLIST_ENTRY64>(p_list_entry->Flink))
	{
		const auto p_entry = CONTAINING_RECORD(p_list_entry, LDR_DATA_TABLE_ENTRY64, InLoadOrderLinks);

		if (!_wcsicmp(mod_name, p_entry->BaseDllName.Buffer))
			return p_entry->DllBase;
	}

	return 0;
}

