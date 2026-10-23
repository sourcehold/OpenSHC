#include "OpenSHC/Map/WildlifeState.func.hpp"
#include "OpenSHC/UI/MenuModals/DebugDataMapData.func.hpp"

#include "OpenSHC/Globals/DAT_WildlifeState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace DebugDataMapData {

            // FUNCTION: STRONGHOLDCRUSADER 0x004AAB20
            void MenuModalRenderFunction_DebugDataMapData(int x, int y, int width, int height)
            {
                MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::renderDebugDataMapData, DAT_WildlifeState::ptr)(
                    x, y, width, height);
            }

        }
    }
}
}
