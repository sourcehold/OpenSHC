#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_DisableMercPostPortraits.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x00466E10
void UI::DisableMercPostPortraits() { DAT_DisableMercPostPortraits::instance = 1; }

}
