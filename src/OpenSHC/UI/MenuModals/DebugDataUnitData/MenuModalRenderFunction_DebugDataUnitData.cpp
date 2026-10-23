#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/UI/MenuModals/DebugDataUnitData.func.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace DebugDataUnitData {

            // FUNCTION: STRONGHOLDCRUSADER 0x004AAA80
            void MenuModalRenderFunction_DebugDataUnitData(int x, int y, int width, int height)
            {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::renderDebugDataUnitData, DAT_UnitsState::ptr)(
                    x, y, width, height);
            }

        }
    }
}
}
