#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00501B90
    void TileMapState::changeMapOrientation(MapOrientation mapOrientation)
    {
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::saveFocusTileAndCenterPreview,
            DAT_ViewportRenderState::ptr)();
        DAT_TileMapState::instance.mapOrientation = mapOrientation;
        MACRO_CALL_MEMBER(
            OpenSHC::Rendering::ViewportRenderState_Func::restoreFocusTile, DAT_ViewportRenderState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::forceFullTileMapRedraw, this)();
        MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::refreshAllBuildingTileDisplays, DAT_BuildingsState::ptr)();
        DAT_BuildingsState::instance.field_0x10 = 5;
        switch (this->mapOrientation) {
        case OpenSHC::Map::Enums::MO_NORTH:
            this->screenSouthEastDirection = 3;
            this->orientedRowStep = 1;
            this->screenEastDirection = 2;
            this->screenSouthDirection = 4;
            this->screenSouthWestDirection = 5;
            return;
        case OpenSHC::Map::Enums::MO_EAST:
            this->screenSouthEastDirection = 5;
            this->orientedRowStep = 1;
            this->screenEastDirection = 4;
            this->screenSouthDirection = 6;
            this->screenSouthWestDirection = 7;
            return;
        case OpenSHC::Map::Enums::MO_SOUTH:
            this->screenSouthEastDirection = 7;
            this->screenEastDirection = 6;
            this->screenSouthDirection = 0;
            this->screenSouthWestDirection = 1;
            this->orientedRowStep = -1;
            return;
        case OpenSHC::Map::Enums::MO_WEST:
            this->screenSouthEastDirection = 1;
            this->screenEastDirection = 0;
            this->screenSouthDirection = 2;
            this->screenSouthWestDirection = 3;
            this->orientedRowStep = -1;
        }
    }

}
}
