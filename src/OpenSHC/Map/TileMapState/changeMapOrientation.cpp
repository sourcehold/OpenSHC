#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Map/Enums/CardinalDirection.hpp"

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
            this->screenSouthEastDirection = OpenSHC::Map::Enums::CD_SOUTHEAST;
            this->orientedRowStep = 1;
            this->screenEastDirection = OpenSHC::Map::Enums::CD_EAST;
            this->screenSouthDirection = OpenSHC::Map::Enums::CD_SOUTH;
            this->screenSouthWestDirection = OpenSHC::Map::Enums::CD_SOUTHWEST;
            return;
        case OpenSHC::Map::Enums::MO_EAST:
            this->screenSouthEastDirection = OpenSHC::Map::Enums::CD_SOUTHWEST;
            this->orientedRowStep = 1;
            this->screenEastDirection = OpenSHC::Map::Enums::CD_SOUTH;
            this->screenSouthDirection = OpenSHC::Map::Enums::CD_WEST;
            this->screenSouthWestDirection = OpenSHC::Map::Enums::CD_NORTHWEST;
            return;
        case OpenSHC::Map::Enums::MO_SOUTH:
            this->screenSouthEastDirection = OpenSHC::Map::Enums::CD_NORTHWEST;
            this->screenEastDirection = OpenSHC::Map::Enums::CD_WEST;
            this->screenSouthDirection = OpenSHC::Map::Enums::CD_NORTH;
            this->screenSouthWestDirection = OpenSHC::Map::Enums::CD_NORTHEAST;
            this->orientedRowStep = -1;
            return;
        case OpenSHC::Map::Enums::MO_WEST:
            this->screenSouthEastDirection = OpenSHC::Map::Enums::CD_NORTHEAST;
            this->screenEastDirection = OpenSHC::Map::Enums::CD_NORTH;
            this->screenSouthDirection = OpenSHC::Map::Enums::CD_EAST;
            this->screenSouthWestDirection = OpenSHC::Map::Enums::CD_SOUTHEAST;
            this->orientedRowStep = -1;
        }
    }

}
}
