#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/UI/BuildingMenus.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace UI {
    namespace BuildingMenus {

        // FUNCTION: STRONGHOLDCRUSADER 0x0043A8D0
        void RenderBuildingMenu_RecruitingBuilding()
        {
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::createEntityForAssemblyPointsForActiveTabType,
                DAT_BuildingsState::ptr)();
        }

    }
}
}
