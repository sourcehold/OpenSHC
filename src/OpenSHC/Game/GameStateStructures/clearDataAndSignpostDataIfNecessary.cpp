#include "../GameStateStructures.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Game {

    using Map::Buildings::BuildingType;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00456C50
    void GameStateStructures::clearDataAndSignpostDataIfNecessary()
    {
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            sizeof(this->mapAndTime.signpostEntryData), '\0', this->mapAndTime.signpostEntryData);
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            sizeof(this->mapAndTime.signpostsMapEdge), '\0', this->mapAndTime.signpostsMapEdge);
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            sizeof(this->mapAndTime.unitMoveDestinationXYPairs), '\0', this->mapAndTime.unitMoveDestinationXYPairs);
        for (int slot = 0; slot < 8; ++slot) {
            if (this->mapAndTime.signpostIDs[slot] == 0
                || DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[slot]].buildingType
                    != Map::Buildings::BT_SIGNPOST) {
                this->mapAndTime.signpostIDs[slot] = 0;
                this->mapAndTime.signpostEntryData[slot].x = 0;
                this->mapAndTime.signpostEntryData[slot].y = 0;
                this->mapAndTime.signpostEntryData[slot].tile = 0;
            }
        }
        // close the holes by bubbling the remaining signposts to the front
        BOOLEnum signpostMoved = TRUE;
        while (signpostMoved) {
            signpostMoved = FALSE;
            for (int slot = 0; slot < 7; ++slot) {
                if (this->mapAndTime.signpostIDs[slot] == 0 && this->mapAndTime.signpostIDs[slot + 1] != 0) {
                    this->mapAndTime.signpostIDs[slot] = this->mapAndTime.signpostIDs[slot + 1];
                    this->mapAndTime.signpostIDs[slot + 1] = 0;
                    signpostMoved = TRUE;
                }
            }
        }
        for (int signpostSlot = 0; signpostSlot < 8; ++signpostSlot) {
            int const buildingID = this->mapAndTime.signpostIDs[signpostSlot];
            if (buildingID == 0) {
                continue;
            }
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::determineBuildingEntranceFromKeepArea,
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
            MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findMapBorderEdgeTileAndStoreInSignpostData,
                DAT_PathFindingState::ptr)(signpostSlot, 0x13a10,
                DAT_BuildingsState::instance.buildings[buildingID].buildingEntryX,
                DAT_BuildingsState::instance.buildings[buildingID].buildingEntryY);
        }
    }

}
}
