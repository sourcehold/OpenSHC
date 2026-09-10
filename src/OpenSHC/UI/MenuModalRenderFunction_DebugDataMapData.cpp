#include "OpenSHC/Map/WildlifeState.func.hpp"
#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_WildlifeState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x004AAB20
void UI::MenuModalRenderFunction_DebugDataMapData(int x, int y, int width, int height)
{
    MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::renderDebugDataMapData, DAT_WildlifeState::ptr)(
        x, y, width, height);
}

}
