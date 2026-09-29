
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00501B90
    void TileMapState::changeMapOrientation(int mapOrientation)
    {
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::saveFocusTileAndCenterPreview,
            DAT_ViewportRenderState::ptr)();
        this->mapOrientation = mapOrientation;
        MACRO_CALL_MEMBER(
            OpenSHC::Rendering::ViewportRenderState_Func::restoreFocusTile, DAT_ViewportRenderState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::forceFullTileMapRedraw, this)();
        MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::refreshAllBuildingTileDisplays, DAT_BuildingsState::ptr)();
        DAT_BuildingsState::instance.field4_0x10 = 5;
        switch (this->mapOrientation) {
        case 0:
            this->field84_0x5548a4 = 3;
            this->field88_0x5548b4 = 1;
            this->field85_0x5548a8 = 2;
            this->field86_0x5548ac = 4;
            this->field87_0x5548b0 = 5;
            return;
        case 2:
            this->field84_0x5548a4 = 5;
            this->field88_0x5548b4 = 1;
            this->field85_0x5548a8 = 4;
            this->field86_0x5548ac = 6;
            this->field87_0x5548b0 = 7;
            return;
        case 4:
            this->field84_0x5548a4 = 7;
            this->field85_0x5548a8 = 6;
            this->field86_0x5548ac = 0;
            this->field87_0x5548b0 = 1;
            this->field88_0x5548b4 = -1;
            return;
        case 6:
            this->field84_0x5548a4 = 1;
            this->field85_0x5548a8 = 0;
            this->field86_0x5548ac = 2;
            this->field87_0x5548b0 = 3;
            this->field88_0x5548b4 = -1;
        }
    }

}
}
