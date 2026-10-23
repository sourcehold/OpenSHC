
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
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
        DAT_TileMapState::instance.mapOrientation = mapOrientation;
        MACRO_CALL_MEMBER(
            OpenSHC::Rendering::ViewportRenderState_Func::restoreFocusTile, DAT_ViewportRenderState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::forceFullTileMapRedraw, this)();
        MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::refreshAllBuildingTileDisplays, DAT_BuildingsState::ptr)();
        DAT_BuildingsState::instance.field4_0x10 = 5;
        switch (this->mapOrientation) {
        case 0:
            this->screenSouthEastDirection = 3;
            this->orientedRowStep = 1;
            this->screenEastDirection = 2;
            this->screenSouthDirection = 4;
            this->screenSouthWestDirection = 5;
            return;
        case 2:
            this->screenSouthEastDirection = 5;
            this->orientedRowStep = 1;
            this->screenEastDirection = 4;
            this->screenSouthDirection = 6;
            this->screenSouthWestDirection = 7;
            return;
        case 4:
            this->screenSouthEastDirection = 7;
            this->screenEastDirection = 6;
            this->screenSouthDirection = 0;
            this->screenSouthWestDirection = 1;
            this->orientedRowStep = -1;
            return;
        case 6:
            this->screenSouthEastDirection = 1;
            this->screenEastDirection = 0;
            this->screenSouthDirection = 2;
            this->screenSouthWestDirection = 3;
            this->orientedRowStep = -1;
        }
    }

}
}
