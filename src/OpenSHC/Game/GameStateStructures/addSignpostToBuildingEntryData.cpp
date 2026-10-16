#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00456EF0
    void GameStateStructures::addSignpostToBuildingEntryData(int buildingID)
    {
        int signpostSlot;
        for (signpostSlot = 0; signpostSlot < 8; signpostSlot++) {
            if ((this->mapAndTime.signpostIDs[signpostSlot] == 0)
                || (DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[signpostSlot]].buildingType
                    != OpenSHC::Map::Buildings::BT_SIGNPOST)) {
                this->mapAndTime.signpostIDs[signpostSlot] = buildingID;
                break;
            }
        }
        if (signpostSlot >= 8) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::deleteBuilding, DAT_BuildingsState::ptr)(
                this->mapAndTime.signpostIDs[7]);
            signpostSlot = 7;
            this->mapAndTime.signpostIDs[7] = buildingID;
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::determineBuildingEntranceFromKeepArea,
            DAT_BuildingsState::ptr)(buildingID, 1, FALSE);
        this->mapAndTime.signpostEntryData[signpostSlot].x
            = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryX;
        this->mapAndTime.signpostEntryData[signpostSlot].y
            = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryY;
        this->mapAndTime.signpostEntryData[signpostSlot].tile
            = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryX
            + DAT_ViewportRenderState::instance
                  .translationMatrix[DAT_BuildingsState::instance.buildings[buildingID].buildingEntryY]
                  .addXgetTile;
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findMapBorderEdgeTileAndStoreInSignpostData,
            DAT_PathFindingState::ptr)(signpostSlot, 80400,
            DAT_BuildingsState::instance.buildings[buildingID].buildingEntryX,
            DAT_BuildingsState::instance.buildings[buildingID].buildingEntryY);
    }

}
}
