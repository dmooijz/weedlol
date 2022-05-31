#include "addr.hh"

uintptr_t addr::base = utils::get_module_base(L"HuntGame.exe");
uintptr_t addr::i_renderer = base + 0x2BA3570;
uintptr_t addr::i_game_framework = base + 0x2BA3510;
uintptr_t addr::i_entity_system = base + 0x2BA3520;