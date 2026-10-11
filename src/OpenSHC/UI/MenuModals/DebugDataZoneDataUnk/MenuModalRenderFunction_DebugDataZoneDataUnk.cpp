#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/UI/MenuModals/DebugDataZoneDataUnk.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace DebugDataZoneDataUnk {

            // FUNCTION: STRONGHOLDCRUSADER 0x004AAAA0
            void MenuModalRenderFunction_DebugDataZoneDataUnk(int x, int y, int width, int height)
            {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::renderAttackInfoDebugOverlay,
                    DAT_TroopValueState::ptr)(x, y, width, height);
            }

        }
    }
}
}
