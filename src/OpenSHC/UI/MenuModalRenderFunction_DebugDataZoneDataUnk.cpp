#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x004AAAA0
void UI::MenuModalRenderFunction_DebugDataZoneDataUnk(int x, int y, int width, int height)
{
    MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::renderAttackInfoDebugOverlay,
        DAT_TroopValueState::ptr)(x, y, width, height);
}

}
