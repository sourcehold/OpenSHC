#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F6FD0
    void TileMapState::triggerLoweredView(int requestedView)
    {
        int view = 2;
        if (this->flatViewToggleValue2 == 0) {
            view = requestedView;
        }
        if (this->refreshCertainTileMap_old == view) {
            return;
        }
        this->refreshCertainTileMap = view;
        this->counter1 = 0;
        if (view != 3) {
            return;
        }
        if (DAT_GameCore::instance.gamePausedLogical != 0) {
            return;
        }

        for (int unitID = 1; unitID < (int)DAT_UnitsState::instance.maxUnitCount; unitID++) {
            if (DAT_UnitsState::instance.units[unitID].logicalState == OpenSHC::Map::Units::ULS_INVISIBLE) {
                continue;
            }
            if (DAT_UnitsState::instance.units[unitID].unitType != OpenSHC::Map::Units::UT_DRUNK
                && DAT_UnitsState::instance.units[unitID].unitType != OpenSHC::Map::Units::UT_RABBIT
                && DAT_UnitsState::instance.units[unitID].unitType != OpenSHC::Map::Units::UT_HUNTERDOG
                && DAT_UnitsState::instance.units[unitID].unitType != OpenSHC::Map::Units::UT_JESTER
                && DAT_UnitsState::instance.units[unitID].unitType != OpenSHC::Map::Units::UT_CHICKEN
                && DAT_UnitsState::instance.units[unitID].unitType != OpenSHC::Map::Units::UT_CHILD
                && DAT_UnitsState::instance.units[unitID].unitType != OpenSHC::Map::Units::UT_JUGGLER
                && DAT_UnitsState::instance.units[unitID].unitType != OpenSHC::Map::Units::UT_FIREEATER) {
                continue;
            }

            int height = (DAT_UnitsState::instance.units[unitID].buildingHeight
                             + DAT_UnitsState::instance.units[unitID].terrainOrClimbHeight)
                / 10;
            if (height > 14) {
                height = 14;
            }
            DAT_UnitsState::instance.units[unitID].heightDiv10 = height;
            DAT_UnitsState::instance.units[unitID].field_0x83 = 0;
        }
    }

}
}
